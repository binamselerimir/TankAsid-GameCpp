// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/NPCController_TypeTwo.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Pawns/EnemyTank_Type2.h"


ANPCController_TypeTwo::ANPCController_TypeTwo() {

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerception"));
	SightPerception = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight"));

	SightPerception->SightRadius = 2000;
	SightPerception->LoseSightRadius = 2000;
	SightPerception->PeripheralVisionAngleDegrees = 180;

	Perception->ConfigureSense(*SightPerception);

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/Enemys/AIs/BT_EnemyTypeTwo"));
	if (BehaviorTreeObject.Succeeded()) {
		BehaviorTree = BehaviorTreeObject.Object;
	}

	SetGenericTeamId(FGenericTeamId(1));
}

void ANPCController_TypeTwo::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	EnemyBlackBoard = GetBlackboardComponent();

	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCController_TypeTwo::OnPlayerSeen);


}

void ANPCController_TypeTwo::OnPlayerSeen(AActor* Actor, FAIStimulus Stimulus) {
	if (Stimulus.WasSuccessfullySensed()) {
		if (Actor->GetActorLocation().Z <= 58) {
			EnemyBlackBoard->SetValueAsObject(FName("Player"), Actor);
		}
	}
	else
	{
		Blackboard->ClearValue(FName("Player"));
	}
}