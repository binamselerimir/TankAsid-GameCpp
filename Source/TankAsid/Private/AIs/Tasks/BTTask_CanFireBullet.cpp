// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/Tasks/BTTask_CanFireBullet.h"


EBTNodeResult::Type UBTTask_CanFireBullet::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (NumberRocketFire >= TotalBulletLimit) {
		UE_LOG(LogTemp, Warning, TEXT("%f"), NumberRocketFire)
		NumberRocketFire = 0;
		return EBTNodeResult::Succeeded;
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), NumberRocketFire)

	NumberRocketFire += 1;
	return EBTNodeResult::Failed;
}