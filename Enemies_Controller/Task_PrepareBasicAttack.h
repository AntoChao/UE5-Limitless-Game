// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_PrepareBasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class TRUEPROJECT2_API UTask_PrepareBasicAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	
	class AAIController* OwnerAIController;

	class AAIEnemyClassController* EnemyController;

	// try to access the parent class, otherwise have to do the cast to each type of enemy
	class AEnemyClass* Enemy;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;
};
