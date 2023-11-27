// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_BasicAttackFinish.generated.h"

/**
 * 
 */
UCLASS()
class TRUEPROJECT2_API UTask_BasicAttackFinish : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	class AAIController* OwnerAIController;

	class AAIEnemyClassController* EnemyController;

	class AEnemyClass* Enemy;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;

};
