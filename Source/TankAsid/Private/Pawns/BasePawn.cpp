// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BasePawn.h"
#include "Actors/Projectile.h"
#include "Actors/Bullet.h"
#include "kismet/GameplayStatics.h"
#include "Pawns/TankPlayer.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// components
	TankMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TankMesh"));
	RootComponent = TankMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TurretMesh"));
	TurretMesh->SetupAttachment(TankMesh);

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BarrelMesh"));
	BarrelMesh->SetupAttachment(TurretMesh);

	Scene = CreateDefaultSubobject<USceneComponent>(FName("Scene"));
	Scene->SetupAttachment(BarrelMesh);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	// set health
	Health = MaxHealth;
	CurrentBullet = MaxBullet;
	CurrentRocket = MaxRocket;

}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// fire bullet and timer
	if (bIsFireBullet) {
		if (Timer >= 0.2) {
			FireBullet();
			Timer = 0;
		}
	}
	Timer += DeltaTime;

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// input movement
	PlayerInputComponent->BindAction("FireBullet", IE_Pressed, this, &ABasePawn::FireingBullet);
	PlayerInputComponent->BindAction("StopFireBullet", IE_Released, this, &ABasePawn::StopFireingBullet);

}


// func fire rocket base
void ABasePawn::Fire() {
	AProjectile* ProjectileSpawn = GetWorld()->SpawnActor<AProjectile>(AProjectileClass, Scene->GetComponentTransform());
	ProjectileSpawn->SetOwner(this);
	UGameplayStatics::SpawnSoundAtLocation(this, RocketSound, ProjectileSpawn->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("True Fire Rocket"))
}


// func fire bullet base
void ABasePawn::Bullet() {
	ABullet* BulletSpawn = GetWorld()->SpawnActor<ABullet>(BulletClass, Scene->GetComponentTransform());
	BulletSpawn->SetOwner(this);
	UGameplayStatics::SpawnSoundAtLocation(this, BulletSound, BulletSpawn->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("True Fire Bullet"))

}

// fire rocket player
void ABasePawn::FireRocket() {
	if (CurrentRocket > 0) {
		Fire();
		CurrentRocket--;
		// UE_LOG(LogTemp, Warning, TEXT("%i"), CurrentRocket);
	}
}

// fire bulet player
void ABasePawn::FireBullet() {
	if (CurrentBullet > 0) {
		ABullet* BulletSpawn = GetWorld()->SpawnActor<ABullet>(BulletClass, Scene->GetComponentTransform());
		BulletSpawn->SetOwner(this);
		CurrentBullet--;
	}
}


// take damage
float ABasePawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= FMath::Min(Health, Damage);

	// check death
	if (Health == 0) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplotionParticle, GetActorTransform());
		bIsDead = true;
		DetachFromControllerPendingDestroy();
		Destroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("True %f"), Health)

	return Damage;
}


float ABasePawn::ReturnHealth() {
	return Health / 100;
}

int ABasePawn::ReturnCurrentRocket() {
	return CurrentRocket;
}

int ABasePawn::ReturnCurrentBullet() {
	return CurrentBullet;
}

void ABasePawn::FireingBullet() {
	bIsFireBullet = true;
}

void ABasePawn::StopFireingBullet() {
	bIsFireBullet = false;
}
