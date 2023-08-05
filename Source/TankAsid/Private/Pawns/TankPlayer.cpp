// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATankPlayer::ATankPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(TankMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);

	// create ally
	TeamId = FGenericTeamId(2);
}

// Called when the game starts or when spawned
void ATankPlayer::BeginPlay()
{
	// نخودی
	Super::BeginPlay();
	
}

// Called every frame
void ATankPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// check can fly
	if (bIsFlyings) {
		Flyings();
	}
}

// Called to bind functionality to input
void ATankPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// input movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ATankPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATankPlayer::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &ATankPlayer::TurnRight);
	PlayerInputComponent->BindAxis("TurnUP", this, &ATankPlayer::TurnUP);
	PlayerInputComponent->BindAxis("GOUP", this, &ATankPlayer::GoUp);
	
	// input action
	PlayerInputComponent->BindAction("FireRocket", IE_Pressed, this, &ABasePawn::FireRocket);
	PlayerInputComponent->BindAction("IsFlying", IE_Pressed, this, &ATankPlayer::IsFlyings);


}

FGenericTeamId ATankPlayer::GetGenericTeamId() const
{
	return TeamId;
}


// func`s of movement
void ATankPlayer::MoveForward(float Value) {
	this->AddMovementInput(GetActorForwardVector(), Value);
}

void ATankPlayer::MoveRight(float Value) {
	TankMesh->AddRelativeRotation(FRotator(0, Value * 70 * GetWorld()->GetDeltaSeconds(), 0));
}


void ATankPlayer::TurnRight(float Value) {
	if (bIsFlyings == false) {
		TurretMesh->AddRelativeRotation(FRotator(0, Value * 70 * GetWorld()->GetDeltaSeconds(), 0));
		SpringArm->AddRelativeRotation(FRotator(0, Value * 70 * GetWorld()->GetDeltaSeconds(), 0));
	}
}

void ATankPlayer::TurnUP(float Value) {

	if (Value > 0 && BarrelMesh->GetRelativeRotation().Pitch >= 17)
		return;
	if (Value < 0 && BarrelMesh->GetRelativeRotation().Pitch <= -23)
		return;
	BarrelMesh->AddRelativeRotation(FRotator(Value * 100 * GetWorld()->GetDeltaSeconds(), 0, 0));
}


// flipflop for True and false fly
void ATankPlayer::IsFlyings() {

	if (bIsFlyings == false){
		bIsFlyings = true;
		SpringArm->SetWorldRotation(FRotator(TankMesh->GetRelativeRotation().Pitch, TankMesh->GetRelativeRotation().Yaw, TankMesh->GetRelativeRotation().Roll));
	}
	else {
		bIsFlyings = false;
		TurretMesh->SetWorldRotation(FRotator(TankMesh->GetRelativeRotation().Pitch, TankMesh->GetRelativeRotation().Yaw, TankMesh->GetRelativeRotation().Roll));
		if (TankMesh->GetRelativeLocation().Z != 56.119827) {
			// TODO Dynamic fall
			TankMesh->SetWorldLocation(FVector(TankMesh->GetRelativeLocation().X, TankMesh->GetRelativeLocation().Y, 56.119827));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("i am %d"), bIsFlyings)
}

// flying func
void ATankPlayer::Flyings() {
	TurretMesh->AddRelativeRotation(FRotator(0, 1 * 6000 * GetWorld()->GetDeltaSeconds(), 0));
}

// 
void ATankPlayer::GoUp(float Value) {
	if (bIsFlyings) {
		if (Value > 0 && TankMesh->GetRelativeLocation().Z >= 3000)
			return;
		if (Value < 0 && TankMesh->GetRelativeLocation().Z <= 56.119827)
			return;
		TankMesh->AddRelativeLocation(FVector(0, 0, 200 * Value * GetWorld()->GetDeltaSeconds()));
	}
}