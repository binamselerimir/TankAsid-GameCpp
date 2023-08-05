// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/Tasks/BTTask_Focus.h"
/* #include "BehaviorTree/BlackboardComponent.h"
#include "kismet/GameplayStatics.h"


EBTNodeResult::Type UBTTask_Focus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Target = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector TargetLocation = Target->GetActorLocation();
	FVector TurretLocation = TurretMesh->GetComponentLocation();
	FVector TargetFixedLocation = FVector(TargetLocation.X, TargetLocation.Y, TurretLocation.Z);

	FRotator NewTurretLocation = FVector(TargetLocation - TurretLocation).Rotation();

	FRotator SmoothRotation = FMath::Lerp(TurretMesh->GetComponentRotation(), NewTurretLocation, 10 * GetWorld()->GetDeltaSeconds());

	TurretMesh->SetWorldRotation(SmoothRotation);
	return EBTNodeResult::Succeeded;
}*/
