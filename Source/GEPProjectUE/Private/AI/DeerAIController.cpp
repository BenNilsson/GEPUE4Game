// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DeerAIController.h"
#include "AI/DeerAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interfaces/GetBaseAI.h"
#include "Perception/AIPerceptionComponent.h"

ADeerAIController::ADeerAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

void ADeerAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ADeerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Get Base AI and run behavior tree
	if (InPawn->GetClass()->ImplementsInterface(UGetBaseAI::StaticClass()))
	{
		AAIBase* BaseAI = IGetBaseAI::Execute_GetAIBase(InPawn);

		if (BaseAI == nullptr)
			return;

		RunBehaviorTree(BaseAI->BehaviorTree);
		
	}
}
