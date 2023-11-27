// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy11_Robot_Executor.generated.h"

UCLASS()
class TRUEPROJECT2_API AEnemy11_Robot_Executor : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy11_Robot_Executor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Basic Stats

	UPROPERTY(EditAnywhere, Category = "Enemies")
		TSubclassOf<class AMain> MainClass;

	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	
	// Ability 1 -> DashingAttack
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	// declare overlap end function
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Receive Damage
	//virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Ability1() override;
	virtual void Ability2() override;
	virtual bool IsAbleToUseAbility1() override;
	virtual bool IsAbleToUseAbility2() override;

};
