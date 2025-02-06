// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HandyHome_CameramanController.generated.h"

/**
 * 
 */
UCLASS()
class HANDYHOME_API AHandyHome_CameramanController : public APlayerController
{
	GENERATED_BODY()
	


public:
	AHandyHome_CameramanController();



protected:
	void BeginPlay() override;



};
