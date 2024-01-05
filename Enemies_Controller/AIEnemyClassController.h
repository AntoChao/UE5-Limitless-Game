// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "TimerManager.h"

#include "AIEnemyClassController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class AMain;

UCLASS()
class LIMITLESS_API AAIEnemyClassController : public AAIController
{
	GENERATED_BODY()
	
private:
	AAIEnemyClassController();	

protected:
	// Normal behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPawnSensingComponent* PawnSensing;

	UFUNCTION(BlueprintCallable)
		void OnSeePawn(APawn* PlayerPawn);

	UFUNCTION(BlueprintCallable)
		void SetCanSeePlayer(bool SeePlayer, class UObject* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SenseMain;

	bool GotSpecialStatus;

public:
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		bool GetIsSensingPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTree* BehaviorTree;

	FTimerHandle RetriggerableTimerHandle;
	FTimerDelegate FunctionDelegate;
	void RunRetriggerableTimer();

	UFUNCTION(BlueprintCallable)
		void IsTooCloseToMain(bool bClose);

	/*
	* Set Special Status should have all necesaries parametes for all type of parameters and
	* store them in to variables for BB to use
	*/
	UFUNCTION(BlueprintCallable)
		void SetSpecialStatus(bool SpcialStatus);

	// Special behavior (affected by any status from main abilities)
	UFUNCTION(BlueprintCallable)
		void SetStatusCharm(bool GotCharm, class UObject* Player);

};
