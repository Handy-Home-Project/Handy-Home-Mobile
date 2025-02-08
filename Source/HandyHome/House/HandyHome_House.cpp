// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHome_House.h"
#include "HandyHome_HouseData.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"

// Sets default values
AHandyHome_House::AHandyHome_House()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshFinder(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	verify(CubeMeshFinder.Succeeded());
	CubeMesh = CubeMeshFinder.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	verify(MaterialFinder.Succeeded());
	WallMaterial = MaterialFinder.Object;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
	RootComponent->SetRelativeLocation(FVector::ZeroVector);
	RootComponent->SetWorldScale3D(FVector(0.01, 0.01, 0.01));
	RootComponent->Mobility = EComponentMobility::Static;
}

// Called when the game starts or when spawned
void AHandyHome_House::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHandyHome_House::Build()
{
	WallArray.Reserve(HouseData.WallCount);

	for (auto MapIt = HouseData.RoomDataMap.CreateConstIterator(); MapIt; ++MapIt)
	{
		TArray<FWallData> WallDataArray = MapIt->Value.WallDataArray;
		const FString RoomName = MapIt->Key.ToString();
		const int32 WallDataArraySize = WallDataArray.Num();
		for (int32 i = 0; i < WallDataArraySize; i++)
		{
			FActorSpawnParameters WallSpawnParameters;
			WallSpawnParameters.Name = FName(RoomName + FString::Printf(TEXT("_%d"), i));
			WallSpawnParameters.Owner = this;
			WallSpawnParameters.bNoFail = true;
			WallSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			WallSpawnParameters.bHideFromSceneOutliner = false;

			TObjectPtr<AStaticMeshActor> NewWall = GetWorld()->SpawnActor<AStaticMeshActor>(
				AStaticMeshActor::StaticClass(),
				FVector(WallDataArray[i].WallLocation.X, WallDataArray[i].WallLocation.Y, 0),
				FRotator::ZeroRotator,
				WallSpawnParameters
			);

#if WITH_EDITOR
			NewWall->SetActorLabel(WallSpawnParameters.Name.ToString());
#endif //WITH_EDITOR

			NewWall->GetStaticMeshComponent()->SetStaticMesh(CubeMesh);

			TObjectPtr<UMaterialInstanceDynamic> WallMaterialInstance = UMaterialInstanceDynamic::Create(WallMaterial, this, TEXT("WallMaterialInstance"));
			WallMaterialInstance->SetVectorParameterValue(TEXT("Color"), FLinearColor::Green);
			NewWall->GetStaticMeshComponent()->GetStaticMesh()->SetMaterial(0, WallMaterialInstance);

			NewWall->GetStaticMeshComponent()->SetMobility(EComponentMobility::Static);

			FVector2D WallScaleVector = FVector2D(
				(FWallData::WallThickness < WallDataArray[i].WallSize.X 
					? WallDataArray[i].WallSize.X : FWallData::WallThickness),
				(FWallData::WallThickness < WallDataArray[i].WallSize.Y
					? WallDataArray[i].WallSize.Y : FWallData::WallThickness)
			);
			NewWall->GetStaticMeshComponent()->SetRelativeScale3D(
				FVector(WallScaleVector.X * 0.01, WallScaleVector.Y * 0.01, FWallData::WallHeight * 0.01)
			);

			WallArray.Add(NewWall);
		}
	}

	
}

