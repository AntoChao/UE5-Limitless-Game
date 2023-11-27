// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_FindRandomLocationUlt.h"

#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "AIEnemyClassController.h"
#include "../All_Enemies/EnemyClass.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_FindRandomLocationUlt::
ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerAIController = OwnerComp.GetAIOwner();
	EnemyController = Cast<AAIEnemyClassController>(OwnerAIController);
	Enemy = Cast<AEnemyClass>(EnemyController->GetPawn());
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

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
	if (!IsValid(Player))
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()
		->SetValueAsVector(FName("Random Location"), Enemy->EnemyGetRandMainLocation());

	return EBTNodeResult::Succeeded;

}