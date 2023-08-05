// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerTank.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/PlayerHUD.h"


APlayerControllerTank::APlayerControllerTank() {

	// get player hud bluprint widget
	ConstructorHelpers::FClassFinder<UPlayerHUD> PlayerHUDWidget(TEXT("/Game/Widgets/WBP_PlayerHUD"));
	if (PlayerHUDWidget.Class) {
		PlayerHUDClass = PlayerHUDWidget.Class;
	}
}

void APlayerControllerTank::BeginPlay() {
	Super::BeginPlay();

	// add player hud to viewport
	UPlayerHUD* PlayerHUD = CreateWidget<UPlayerHUD>(this, PlayerHUDClass);
	PlayerHUD->AddToViewport();
}
