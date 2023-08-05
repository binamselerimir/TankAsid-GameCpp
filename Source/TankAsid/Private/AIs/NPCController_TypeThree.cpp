// Fill out your copyright notice in the Description page of Project Settings.


#include "AIs/NPCController_TypeThree.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Pawns/EnemyTank_Type3.h"
#include "Engine/TargetPoint.h"


ANPCController_TypeThree::ANPCController_TypeThree() {

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerception"));
	SightPerception = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight"));

	SightPerception->SightRadius = 2000;
	SightPerception->LoseSightRadius = 2000;
	SightPerception->PeripheralVisionAngleDegrees = 180;

	Perception->ConfigureSense(*SightPerception);

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/Enemys/AIs/BT_EnemyTypeThree"));

	if (BehaviorTreeObject.Succeeded()) {
		BehaviorTree = BehaviorTreeObject.Object;
	}

	SetGenericTeamId(FGenericTeamId(1));
}

void ANPCController_TypeThree::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	EnemyBlackBoard = GetBlackboardComponent();

	if (AEnemyTank_Type3* Tank = Cast<AEnemyTank_Type3>(GetPawn())) {
		TargetPointClass = Tank->TargetPoint;
		UE_LOG(LogTemp, Warning , TEXT("Hmm... Is True"))
	}

	EnemyBlackBoard->SetValueAsObject(FName("TargetPointOne"), TargetPointClass);


	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCController_TypeThree::OnPlayerSeen);


}

void ANPCController_TypeThree::OnPlayerSeen(AActor* Actor, FAIStimulus Stimulus) {
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
