// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHome_HouseData.h"

const double FWallData::WallHeight = 230.0;
const double FWallData::WallThickness = 5.0;
	  
const double FRoomData::FloorThickness = 1.0;

FWallData::FWallData(
	const FName WallName /*= TEXT("Unnamed")*/,
	const FVector2D WallSize /*= FVector2f(4444.0, 4444.0)*/,
	const FVector2D WallLocation /*= FVector2f(4444.0, 4444.0)*/
) : WallName(this->WallName),
	WallSize(this->WallSize),
	WallLocation(this->WallLocation)
{
}