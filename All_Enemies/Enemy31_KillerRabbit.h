// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy31_KillerRabbit.generated.h"

UCLASS()
class LIMITLESS_API AEnemy31_KillerRabbit : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy31_KillerRabbit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CustomTickFunction() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		bool bFlyUp = false;

	//Basic Stats
	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	virtual FVector GetAttackFinishedPosition() override;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Receive Damage
	//virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
