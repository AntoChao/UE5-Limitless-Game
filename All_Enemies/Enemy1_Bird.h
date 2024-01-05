// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Enemy1_Bird.generated.h"

UCLASS()
class LIMITLESS_API AEnemy1_Bird : public AEnemyClass
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy1_Bird();

protected:
	//Basic Stats
	FHitResult EnemyHit;
	
	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;

	
	// Basic Attack -> Dash attack
	virtual FVector GetAttackFinishedPosition() override;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	// declare overlap end function
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	
	// Ability 1 -> WindSlash
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Wind_Slash_Socket_1 = FName("Socket_WindSlash1");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Wind_Slash_Socket_2 = FName("Socket_WindSlash2");

	UPROPERTY(EditAnywhere, Category = "Ability")
		TSubclassOf<class AEnemy1_Bird_WindSlash> WindSlashClass;

	UPROPERTY(EditAnywhere, Category = "Ability")
		class AEnemy1_Bird_WindSlash* WindSlash1;

	UPROPERTY(EditAnywhere, Category = "Ability")
		class AEnemy1_Bird_WindSlash* WindSlash2;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Receive Damage
	//virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void BasicAttack() override;
	virtual void Ability1() override;

	void BasicAttackFinished() override;

};
