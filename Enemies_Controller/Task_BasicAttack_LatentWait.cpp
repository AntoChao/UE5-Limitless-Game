// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_BasicAttack_LatentWait.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AIEnemyClassController.h"
#include "../All_Enemies/EnemyClass.h"
//#include "BasicEnemy.h"

EBTNodeResult::Type UTask_BasicAttack_LatentWait::
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
	Enemy->BasicAttack();

	return EBTNodeResult::InProgress;
}

// latent wait is about is using ability and not cooldown
void UTask_BasicAttack_LatentWait::TickTask(UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory, float DeltaSeconds)
{
	if (!Enemy->GetIsAttacking())
	{
		// return EBTNodeResult::InProgress;
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}