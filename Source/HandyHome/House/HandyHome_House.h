// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandyHome_House.generated.h"

UCLASS()
class HANDYHOME_API AHandyHome_House : public AActor
{
	GENERATED_BODY()
	


public:	
	// Sets default values for this actor's properties
	AHandyHome_House();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
