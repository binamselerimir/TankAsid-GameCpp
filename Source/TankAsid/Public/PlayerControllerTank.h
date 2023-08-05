// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerTank.generated.h"

/**
 * 
 */
UCLASS()
class TANKASID_API APlayerControllerTank : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerControllerTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;
};
