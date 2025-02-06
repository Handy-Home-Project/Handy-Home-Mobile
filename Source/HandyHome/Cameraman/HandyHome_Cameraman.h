// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HandyHome_Cameraman.generated.h"

UCLASS()
class HANDYHOME_API AHandyHome_Cameraman: public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHandyHome_Cameraman();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
