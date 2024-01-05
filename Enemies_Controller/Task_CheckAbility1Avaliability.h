// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_CheckAbility1Avaliability.generated.h"

/**
 * 
 */
UCLASS()
class LIMITLESS_API UTask_CheckAbility1Avaliability : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	class AAIController* OwnerAIController;

	class AAIEnemyClassController* EnemyController;

	// try to access the parent class, otherwise have to do the cast to each type of enemy
	class AEnemyClass* Enemy;
	//class ABasicEnemy* Enemy;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) override;
};
