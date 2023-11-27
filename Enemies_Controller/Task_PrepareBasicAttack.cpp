// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_PrepareBasicAttack.h"

#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "AIController.h"
#include "AIEnemyClassController.h"
#include "../All_Enemies/EnemyClass.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_PrepareBasicAttack::
ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerAIController = OwnerComp.GetAIOwner();
	EnemyController = Cast<AAIEnemyClassController>(OwnerAIController);
	Enemy = Cast<AEnemyClass>(EnemyController->GetPawn());

	bNotifyTick = 1;

	if (OwnerAIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	if (EnemyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	if (Enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	Enemy->PrepareBasicAttack();

	return EBTNodeResult::Succeeded;
}