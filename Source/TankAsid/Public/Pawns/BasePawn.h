// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TANKASID_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Component Mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TankMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BarrelMesh;
	UPROPERTY(EditAnywhere)
		USceneComponent* Scene;

	void Fire();
	void Bullet();
	void FireRocket();
	void FireBullet();
	// int MaxBullet = 0, int CurrentBullet = 0, int MaxRocket, int CurrentRocket
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	bool bIsDead;
	
	float ReturnHealth();

	int ReturnCurrentRocket();
	int ReturnCurrentBullet();

	bool bIsFireBullet;


	UPROPERTY(EditAnywhere)
	USoundBase* RocketSound = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase* BulletSound = nullptr;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplotionParticle = nullptr;
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> AProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;
	UPROPERTY(EditAnywhere)
	float Health;
	

	int MaxRocket = 20;
	int CurrentRocket;

	int MaxBullet = 100;
	int CurrentBullet;


	void FireingBullet();
	void StopFireingBullet();



	float Timer = 0;
};
