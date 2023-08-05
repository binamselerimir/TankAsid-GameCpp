// Fill out your copyright notice in the Description page of Project Settings.

#include "AIs/NPCController_TypeFour.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Pawns/EnemyTank_Type4.h"
#include "Engine/TargetPoint.h"


ANPCController_TypeFour::ANPCController_TypeFour() {

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerception"));
	SightPerception = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight"));

	SightPerception->SightRadius = 10000;
	SightPerception->LoseSightRadius = 10000;
	SightPerception->PeripheralVisionAngleDegrees = 360;

	Perception->ConfigureSense(*SightPerception);

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/Enemys/AIs/BT_EnemyTypeFour"));

	if (BehaviorTreeObject.Succeeded()) {
		BehaviorTree = BehaviorTreeObject.Object;
	}

	SetGenericTeamId(FGenericTeamId(1));
}

void ANPCController_TypeFour::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	EnemyBlackBoard = GetBlackboardComponent();

	if (AEnemyTank_Type4* Tank = Cast<AEnemyTank_Type4>(GetPawn())) {
		TargetPointClass = Tank->TargetPoint;
		UE_LOG(LogTemp, Warning, TEXT("Hmm... Is True"))
	}

	EnemyBlackBoard->SetValueAsObject(FName("TargetPointOne"), TargetPointClass);


	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCController_TypeFour::OnPlayerSeen);


}

void ANPCController_TypeFour::OnPlayerSeen(AActor* Actor, FAIStimulus Stimulus) {
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

