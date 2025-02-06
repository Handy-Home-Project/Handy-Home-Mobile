// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HandyHome_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HANDYHOME_API AHandyHome_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	


private:
	AHandyHome_GameModeBase();



protected:
	void BeginPlay() override;
};
