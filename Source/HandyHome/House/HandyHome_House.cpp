// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHome_House.h"
#include "HandyHome_HouseData.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AHandyHome_House::AHandyHome_House()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorHiddenInGame(false);

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
		const int32 WallDataArraySize = WallDataArray.Num();
		for (int32 i = 0; i < WallDataArraySize; i++)
		{
			TObjectPtr<UStaticMeshComponent> NewWall = NewObject<UStaticMeshComponent>(this, WallDataArray[i].WallName);

			NewWall->SetStaticMesh(CubeMesh);
			TObjectPtr<UMaterialInstanceDynamic> WallMaterialInstance = UMaterialInstanceDynamic::Create(WallMaterial, this, TEXT("WallMaterialInstance"));
			WallMaterialInstance->SetVectorParameterValue(TEXT("Color"), FLinearColor::Green);
			NewWall->GetStaticMesh()->SetMaterial(0, WallMaterialInstance);

			NewWall->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			NewWall->Mobility = EComponentMobility::Static;

			NewWall->SetRelativeScale3D(
					FVector(WallDataArray[i].WallSize.X, WallDataArray[i].WallSize.Y, FWallData::WallHeight)
			);

			NewWall->SetWorldLocation(FVector(WallDataArray[i].WallLocation.X, WallDataArray[i].WallLocation.Y, 0));

			WallArray.Add(NewWall);

			int32 temp1 = 0;
		}
	}

	
}

