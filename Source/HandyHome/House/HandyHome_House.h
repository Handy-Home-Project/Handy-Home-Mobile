// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandyHome_HouseData.h"
#include "HandyHome_House.generated.h"

UCLASS()
class HANDYHOME_API AHandyHome_House : public AActor
{
	GENERATED_BODY()
	
	friend class UHandyHome_HouseBuilder;

private:
	FHouseData HouseData;



public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UStaticMesh> CubeMesh;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UMaterial> WallMaterial;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<class AStaticMeshActor>> WallArray;


public:	
	// Sets default values for this actor's properties
	AHandyHome_House();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	void Build();

};
