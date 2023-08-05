// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/Tasks/BTTask_BulletFire.h"
#include "Pawns/BasePawn.h"
#include "AIController.h"


EBTNodeResult::Type UBTTask_BulletFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

		AAIController* Controller = OwnerComp.GetAIOwner();
		if (Controller == nullptr) return EBTNodeResult::Failed;

		APawn* Pawn = Controller->GetPawn();
		if (Pawn == nullptr) return EBTNodeResult::Failed;

		ABasePawn* BasePawn = Cast<ABasePawn>(Pawn);
		if (BasePawn == nullptr) return EBTNodeResult::Failed;

		BasePawn->Bullet();

		NumberBullet += 1;
		UE_LOG(LogTemp, Warning, TEXT("ff"))

		return EBTNodeResult::Succeeded;	
}


