// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "GenericTeamAgentInterface.h"
#include "TankPlayer.generated.h"

UCLASS()
class TANKASID_API ATankPlayer : public ABasePawn, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPlayer();
	bool bIsFlyings = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FGenericTeamId GetGenericTeamId() const override;


private:

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnRight(float Value);
	void TurnUP(float Value);

	FGenericTeamId TeamId;

	void Flyings();
	void IsFlyings();

	void GoUp(float Value);
};
