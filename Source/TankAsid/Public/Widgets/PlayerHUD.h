// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class TANKASID_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintPure)
	float GetHealth();
	UFUNCTION(BlueprintPure)
	int GetRocket();

	UFUNCTION(BlueprintPure)
	int GetBullet();
private:


	APawn* Pawn;
	class ABasePawn* Player;

};
