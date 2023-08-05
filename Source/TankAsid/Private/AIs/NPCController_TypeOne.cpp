// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/NPCController_TypeOne.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Pawns/TankPlayer.h"


ANPCController_TypeOne::ANPCController_TypeOne() {

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerception"));
	SightPerception = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight"));

	SightPerception->SightRadius = 3000;
	SightPerception->LoseSightRadius = 4000;
	SightPerception->PeripheralVisionAngleDegrees = 180;

	Perception->ConfigureSense(*SightPerception);

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/Enemys/AIs/BT_EnemyTypeOne"));
	if (BehaviorTreeObject.Succeeded()) {
		BehaviorTree = BehaviorTreeObject.Object;
	}

	SetGenericTeamId(FGenericTeamId(1));

	// PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	// Player = Cast<ATankPlayer>(PlayerPawn);
}

void ANPCController_TypeOne::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);


	EnemyBlackBoard = GetBlackboardComponent();


	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCController_TypeOne::OnPlayerSeen);

}

/* void ANPCController_TypeOne::Tick(float DeltaTime) {
	if (Player->bIsFlyings == false) {
		Stimulus.WasSuccessfullySensed()
	}
}*/



void ANPCController_TypeOne::OnPlayerSeen(AActor* Actor, FAIStimulus Stimulus) {
	if (Stimulus.WasSuccessfullySensed()) {
		EnemyBlackBoard->SetValueAsObject(FName("Player"), Actor);
		SetFocus(Actor, EAIFocusPriority::Gameplay);
	}
	else
	{
		Blackboard->ClearValue(FName("Player"));
		ClearFocus(EAIFocusPriority::Gameplay);
	}
}


