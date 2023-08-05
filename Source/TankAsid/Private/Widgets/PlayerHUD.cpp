// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerHUD.h"
#include "kismet/GameplayStatics.h"
#include "Pawns/BasePawn.h"
#include "Components/TextBlock.h"


bool UPlayerHUD::Initialize() {
	Super::Initialize();
	// get player pawn
	Pawn = UGameplayStatics::GetPlayerPawn(this, 0);

	// check , if true cast to basepawn.cpp
	if (Pawn == nullptr) return 0;
	Player = Cast<ABasePawn>(Pawn);

	if (Player == nullptr) return 0;

	return true;
}

float UPlayerHUD::GetHealth() {
	return Player->ReturnHealth();
}

int UPlayerHUD::GetRocket() {
	return Player->ReturnCurrentRocket();
}

int UPlayerHUD::GetBullet() {
	return Player->ReturnCurrentBullet();
}