// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHome_GameModeBase.h"
#include "Cameraman/HandyHome_Cameraman.h"
#include "Cameraman/HandyHome_CameramanController.h"
#include "Engine/World.h"
#include "House/HandyHome_HouseBuilder.h"


AHandyHome_GameModeBase::AHandyHome_GameModeBase()
{
	DefaultPawnClass = AHandyHome_Cameraman::StaticClass();
	PlayerControllerClass = AHandyHome_CameramanController::StaticClass();
}

void AHandyHome_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance()->GetSubsystem<UHandyHome_HouseBuilder>()->BuildHouse();
}