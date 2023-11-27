// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_BasicAttackFinish.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AIEnemyClassController.h"
#include "../All_Enemies/EnemyClass.h"

EBTNodeResult::Type UTask_BasicAttackFinish::
ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerAIController = OwnerComp.GetAIOwner();
	EnemyController = Cast<AAIEnemyClassController>(OwnerAIController);
	Enemy = Cast<AEnemyClass>(EnemyController->GetPawn());

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

	Enemy->BasicAttackFinished();

	return EBTNodeResult::Succeeded;

}