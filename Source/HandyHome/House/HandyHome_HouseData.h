// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandyHome_HouseData.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FWallData
{
	GENERATED_BODY()

	static const double WallHeight;
	static const double WallThickness;

	UPROPERTY(BlueprintReadOnly)
	FName WallName;

	UPROPERTY(BlueprintReadOnly)
	FVector2D WallSize;

	UPROPERTY(BlueprintReadOnly)
	FVector2D WallLocation;



public:
	FWallData(
		const FName WallName = TEXT("Unnamed"),
		const FVector2D WallSize = FVector2D(4444.0, 4444.0),
		const FVector2D WallLocation = FVector2D(4444.0, 4444.0)
	);

};

USTRUCT(Atomic, BlueprintType)
struct FRoomData
{
	GENERATED_BODY()

	static const double FloorThickness;

	UPROPERTY(BlueprintReadOnly)
	TArray<FWallData> WallDataArray;
};

//USTRUCT(BlueprintType)
//struct FHouseData
//{
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadOnly)
//	FVector2f FloorData;
//
//
//
//};
