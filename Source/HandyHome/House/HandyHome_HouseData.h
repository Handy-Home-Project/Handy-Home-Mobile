// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HandyHome_HouseData.generated.h"

/**
 * 
 */
USTRUCT()
struct FWallData
{
	GENERATED_BODY()

	static const double WallHeight;
	static const double WallThickness;

	UPROPERTY()
	FName WallName;

	UPROPERTY()
	FVector2D WallSize;

	UPROPERTY()
	FVector2D WallLocation;



public:
	FWallData(
		const FName WallName = TEXT("Unnamed"),
		const FVector2D WallSize = FVector2D(4444.0, 4444.0),
		const FVector2D WallLocation = FVector2D(4444.0, 4444.0)
	);

};

USTRUCT()
struct FRoomData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FWallData> WallDataArray;
};

USTRUCT()
struct FHouseData
{
	GENERATED_BODY()

	static const double FloorThickness;

	UPROPERTY()
	TMap<FName, FRoomData> RoomDataMap;

	int32 WallCount = 0;


};
