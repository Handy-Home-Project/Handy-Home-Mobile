// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HandyHome_HouseBuilder.generated.h"

/**
 * 
 */
UCLASS()
class HANDYHOME_API UHandyHome_HouseBuilder : public UGameInstanceSubsystem
{
	GENERATED_BODY()



private:
	UHandyHome_HouseBuilder();



public:
	void BuildHouse();



};
