// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "EnemyTank_Type2.generated.h"

/**
 * 
 */
UCLASS()
class TANKASID_API AEnemyTank_Type2 : public ABasePawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AEnemyTank_Type2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void LookAtTarget(FVector TargetLocation);
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	float MaxDictance = 2000;
};
