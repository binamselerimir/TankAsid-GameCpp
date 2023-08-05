// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CanFireBullet.generated.h"

/**
 * 
 */
UCLASS()
class TANKASID_API UBTTask_CanFireBullet : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	float NumberRocketFire = 0;
	float TotalBulletLimit = 1;
};
