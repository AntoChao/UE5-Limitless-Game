// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy15_Bat_1.generated.h"

UCLASS()
class LIMITLESS_API AEnemy15_Bat_1 : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy15_Bat_1();

protected:
	//Basic Stats

	UPROPERTY(EditAnywhere, Category = "Enemies")
		TSubclassOf<class AMain> MainClass;

	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;
	
	// BasicAttack (SIUCIDATION)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explotion")
		FTimerHandle ExplotionCountDownTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explotion")
		float ExplotionCountDownDuration = 3.0f;

	UFUNCTION(BlueprintCallable, Category = "Explotion")
		void SelfExplode();
	UFUNCTION(BlueprintCallable, Category = "Explotion")
		void DealExplotionDamage();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Explotion")
		void SpawmExplodeNiagara();


public:	

	// Receive Damage
	virtual void ExtraDiedAction() override;

	virtual void BasicAttack() override;
	virtual void BasicAttackFinished() override;
	virtual FVector GetPreAttackPosition() override;

};
