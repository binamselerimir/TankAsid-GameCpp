// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"

// Sets default values
APlayerTank::APlayerTank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TankMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TankMesh"));
	RootComponent = TankMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TurretMesh"));
	TurretMesh->SetupAttachment(TankMesh);
	
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BarrelMesh"));
	BarrelMesh->SetupAttachment(TurretMesh);

}

// Called when the game starts or when spawned
void APlayerTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

