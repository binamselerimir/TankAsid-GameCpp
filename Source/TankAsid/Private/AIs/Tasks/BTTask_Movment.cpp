// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/Tasks/BTTask_Movment.h"
#include "AIController.h"
#include "kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_Movment::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	APawn* PawnController = UGameplayStatics::GetPlayerPawn(this, 0);

	return EBTNodeResult::Succeeded;
}