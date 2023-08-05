// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/EnemyTank_Type4.h"

#include "kismet/GameplayStatics.h"


AEnemyTank_Type4::AEnemyTank_Type4() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyTank_Type4::BeginPlay() {
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

}

void AEnemyTank_Type4::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector Target = PlayerPawn->GetActorLocation();
	LookAtTarget(Target);
}

void AEnemyTank_Type4::LookAtTarget(FVector TargetLocation) {
	FVector TurretLocation = TurretMesh->GetComponentLocation();
	FVector TargetFixedLocation = FVector(TargetLocation.X, TargetLocation.Y, TurretLocation.Z);

	FRotator NewTurretLocation = FVector(TargetLocation - TurretLocation).Rotation();

	FRotator SmoothRotation = FMath::Lerp(TurretMesh->GetComponentRotation(), NewTurretLocation, 40 * GetWorld()->GetDeltaSeconds());

	TurretMesh->SetWorldRotation(SmoothRotation);

}
