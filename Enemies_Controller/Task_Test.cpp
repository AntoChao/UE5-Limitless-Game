// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Test.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AIEnemyClassController.h"
#include "../All_Enemies/EnemyClass.h"
//#include "BasicEnemy.h"

EBTNodeResult::Type UTask_Test::
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
	Enemy->testing();

	/* the node should not be play animation, it should be attack, the animation is part of the attack
	* which form by enemies
	UAnimInstance* AnimInstance = AAIEnemyClassController->GetPawn()->GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// Play the animation montage
	AnimInstance->Montage_Play(MyAnimationMontage);
	*/
	return EBTNodeResult::Succeeded;
}