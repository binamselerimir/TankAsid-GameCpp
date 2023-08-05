// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPCController_TypeThree.generated.h"

/**
 * 
 */
UCLASS()
class TANKASID_API ANPCController_TypeThree : public AAIController
{
	GENERATED_BODY()
private:
	ANPCController_TypeThree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere)
		UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
		class UAIPerceptionComponent* Perception;
	UPROPERTY(EditAnywhere)
		class UAISenseConfig_Sight* SightPerception;

	class UBlackboardComponent* EnemyBlackBoard;

	UFUNCTION()
	void OnPlayerSeen(AActor* Actor, FAIStimulus Stimulus);

	AActor* TargetPointClass;

};

