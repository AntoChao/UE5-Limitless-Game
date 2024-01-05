// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SceneComponent.h"

#include "../AllCharactersClass.h"
#include "../MainController.h"
#include "Components/WidgetComponent.h"
#include "../WidgetsBase/HitFloatingHealthUMG.h"
#include "../WidgetsBase/HealthBarUMG.h"
#include "../WidgetsBase/FloatingNumberActor.h"
#include "../WidgetsBase/HealthBarActor.h"
#include "../Decals/GeneralDecalActor.h"
#include "../Common_Enums.h"

// sound
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "EnemyClass.generated.h"

/* Types
0 -> human
1 -> robot 
2 -> animal
3 ->..
*/


UCLASS()
class LIMITLESS_API AEnemyClass : public AAllCharactersClass
{
	// Primate seccion
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void CustomTickFunction() override;

	/** Sphere collision component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyCollision")
		class UBoxComponent* CollisionComp;

	// MainBody
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class USkeletalMeshComponent* Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		USceneComponent* HealthBarRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main To Target")
		class AMain* MainPlayerTarget;

	// HealthBar
	virtual void BeDetected() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		TSubclassOf<class AHealthBarActor> HealthBarActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		class AHealthBarActor* HealthBar;

	UFUNCTION(BlueprintCallable, Category = "Health Bar")
		void SpawnAttachHealthBar();

	UFUNCTION(BlueprintCallable, Category = "Display")
		void UpdateHealthBarDisplay();

	UFUNCTION(BlueprintCallable, Category = "Display")
		void RemoveHealthBar();


	// Health Bar visibility
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Visibility")
		FTimerHandle HealthBarVisibleTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Visibility")
		float HealthBarVisibleDuration = 5.0f;

	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		EEnemyRarity ItsRarity = EEnemyRarity::EUnknown;

	/*
	Parameters: all parameters bools for blackboard should not be part of the enemyclass, should has a function that call activating for the aiEnemyClassController
	Tasks: Are individual tasks object that run in the blackboard, and if they do not fail, call enemy function. So each task should correspond at least one function
	*/

	// this is the ai controller that responde the enemy
	// enemy should call its parameters changes when something happend
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AAIEnemyClassController* EnemyController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FHitResult EnemyHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAIPerceptionStimuliSourceComponent* stimulus;
	
	void setup_stimulus();

	// Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float MaxEnemyBaseDamage = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float EnemyBaseDamage = 10.0f;

	UFUNCTION(BlueprintCallable, Category = "Enemy Damage")
		void SetEnemyDamage(float modifier);

	// Speed
	// Take damage
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void TakeDamageReaction(float Damage, AActor* DamageCauser);

	// Print the damage number
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		TSubclassOf<class AFloatingNumberActor> FloatingNumberActorClass;

	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void SpawnFloatingHealthWidget(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		FTransform AddFloatingHealthOffset(FTransform FloatNumTrnas);
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		FTransform AddFloatingHealthScale(float damage, FTransform FloatNumTrnas);

	/*
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		EDamageColor GetFloatHealthColor(float Damage);
		*/
	// save the damage amount
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void SaveTotalDamageAmount(float Damage);

	// select the closeast hit effect
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		FTransform SelectHitEffectTrans(FVector DamageDauserPosition);
	
	// spawn niagara takedamage effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		class UNiagaraSystem* HitEffectNiagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		TArray<FName> HitEffectSocketsNames = { FName("Socket_HitEffectOne") , FName("Socket_HitEffectTwo"),
										FName("Socket_HitEffectThree"), FName("Socket_HitEffectFour"),
										FName("Socket_HitEffectFive"), FName("Socket_HitEffectSix") };

	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void SpawnHitEffectNiagara(FTransform SpawnTrans);

	// spawn decal takedamage effect
	/* Spawn a few linetrace base on takedamage fhitresult, choose the closest one and spawn decal actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		TSubclassOf<class AGeneralDecalActor> HitEffectDecalClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		int TraceAmount = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Effect Control")
		int TraceAngle = 10.0f;
	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		FTransform GetHitEffectDecalTrans(FVector DamageDauserPosition);

	UFUNCTION(BlueprintCallable, Category = "Hit Effect Control")
		void SpawnHitEffectDecal(FTransform SpawnTrans);

	// rewards
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Reward To Set")
		class UData_KillFeedBackInfo* KillReward;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Reward To Set")
		float frenzyReward = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Reward To Set")
		float calmReward = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Reward To Set")
		float speedReward = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Reward To Set")
		float xpReward = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ArtifactToSpawn")
		TSubclassOf<class AMiniWorld> AMiniWorldArtifact;

	UPROPERTY(EditAnywhere, Category = "ArtifactToSpawn")
		class AMiniWorld* ArtifactLoot;

	// fvector to calculate the attack position
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MainPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector SelfPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttackDirection;
	
	// for random location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float GeneralDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float MinimalDistance = 500.0f;
	UFUNCTION(BlueprintCallable)
		void CalculateMinimalDistance();

	// Check if it is too close to enemy to change it behavior
	UFUNCTION(BlueprintCallable)
		void CheckMainTooClose();

	// the distance to determinate if it able to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float BasicAttackDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float AbilityOneDistance = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float AbilityTwoDistance = 1000.0f;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float AbilityThreeDistance = 1000.0f;;

	// Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		float PlayRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_BasicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_Ability1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_Ability2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		UAnimMontage* AnimMontage_Ability3;
	
	// All sounds
	// PROB USELESS
	// basic attack sound 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Sound")
		USoundCue* BasicAttackSoundCue;
	UFUNCTION(BlueprintCallable, Category = "Enemy Sound")
		void PlayBasicAttackSound();
	
	// ability sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Sound")
		USoundCue* AbilityOneSoundCue;
	UFUNCTION(BlueprintCallable, Category = "Enemy Sound")
		void PlayAbilityOneSound();
	
	// take hit reaction sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Sound")
		USoundCue* HitReactSoundCue;
	UFUNCTION(BlueprintCallable, Category = "Enemy Sound")
		void PlayHitReactSound();

public:	

	// Health Bar Visibility
	UFUNCTION(BlueprintCallable, Category = "Health Bar Visibility")
		void SetHealthBarVisible();

	UFUNCTION(BlueprintCallable, Category = "Health Bar Visibility")
		void SetHealthBarNotVisible();

	UFUNCTION(BlueprintCallable, Category = "Enemy Rarity")
		void SetRarity(EEnemyRarity ARarity);

	UFUNCTION(BlueprintCallable, Category = "Enemy Rarity")
		EEnemyRarity GetRarity();

	// Difficulty and day buff/ debuff
	UFUNCTION(BlueprintCallable, Category = "Enemy Buff")
		void GetDifficultBuff(float modifier);

	UFUNCTION(BlueprintCallable, Category = "Enemy Buff")
		void GetNightBuff(float modifier);
	UFUNCTION(BlueprintCallable, Category = "Enemy Buff")
		void GetMorningDebuff(float modifier);

	// Take damage
	UFUNCTION(BlueprintCallable, Category = "Enemy Buff")
		virtual void ExtraDiedAction();

	// ai controller stuff
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		float GetGeneralDistance();

	// AI Position Control
	// The Pre posicion in order to Attack
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		virtual FVector GetPreAttackPosition();

	// some enemies have dash, this calculate the dash position
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		virtual FVector GetAttackFinishedPosition();

	UFUNCTION(BlueprintCallable, Category = "AI Control")
		virtual FVector GetPostAttackReposition();

	// Random Location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		class UNavigationSystemV1* NavArea;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		FVector RandomLocation;

	// based on a point and distance, generate a random location around main player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		int MaxRandomTryTimes = 10; /*only try 100 times*/
	
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		FVector GetRandLocation(FVector InitLocation, FVector TargetLocation, 
			float Distance);
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		void GenerateRandomPoint(FVector InitLocation, FVector TargetPosition);
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool RandomLocationValid(FVector TargetLocation, float MaxDistance);

	// Some function to calculate specific location
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		FVector EnemyGetRandMainLocation(); /*An safe escape location in case of error*/

	UFUNCTION(BlueprintCallable, Category = "AI Control")
		FVector GetRetreatLocation(FVector InitLocation, FVector TargetLocation,
			float RetreatDistance);
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		FVector GetOppositeLocation(FVector InitLocation, FVector TargetLocation,
			float OppositeDistance);

	// a bool that mean the enemy is using ability
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetIsUsingAbility1();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetIsUsingAbility2();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetIsUsingAbility3();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetIsAttacking();

	// Tie Breaker between abilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats Need To Set")
		int AmountOfPerformance; /*2, 3 or 4, depends on how many abilities does enemies has*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		bool PerformBasicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		bool PerformAbilityOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		bool PerformAbilityTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Control")
		bool PerformAbilityThree;
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool IsPerformingAction();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetPerformBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetPerformAbilityOne();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetPerformAbilityTwo();
	UFUNCTION(BlueprintCallable, Category = "AI Control")
		bool GetPerformAbilityThree();

	UFUNCTION(BlueprintCallable, Category = "AI Control")
		void TieBreakAction();

	UFUNCTION(BlueprintCallable, Category = "AI BasicAttack")
		virtual bool IsAbleToUseBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "AI Ability One")
		virtual bool IsAbleToUseAbility1();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Two")
		virtual bool IsAbleToUseAbility2();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Three")
		virtual bool IsAbleToUseAbility3();

	// Basic Attack
	// The attack do not deal any damage, it is just a collision box a timer 
	// basic attack is just a animation which fire a notifier which call function 
	// to deal damage to overlapped actors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI BasicAttack")
		bool IsAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI BasicAttack")
		FTimerHandle BasicAttackTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI BasicAttack")
		float BasicAttackDuration = 3.0f; // the animation montage duration
	// Prepare -> show necesaries indicator for the action
	UFUNCTION(BlueprintCallable, Category = "AI BasicAttack")
		virtual void PrepareBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "AI BasicAttack")
		virtual void BasicAttack();
	UFUNCTION(BlueprintCallable, Category = "AI BasicAttack")
		virtual void BasicAttackFinished();
	

	// Ability 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability One")
		FTimerHandle Ability1UsageTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability One")
		bool IsUsingAbility1 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability One")
		float Ability1Duration = 1.0f;
	
	UFUNCTION(BlueprintCallable, Category = "AI Ability One")
		virtual void PrepareAbility1();
	UFUNCTION(BlueprintCallable, Category = "AI Ability One")
		virtual void Ability1();
	UFUNCTION(BlueprintCallable, Category = "AI Ability One")
		virtual void Ability1Finished();

	// Ability 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Two")
		FTimerHandle Ability2UsageTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Two")
		bool IsUsingAbility2 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Two")
		float Ability2Duration = 1.0f;
	
	UFUNCTION(BlueprintCallable, Category = "AI Ability Two")
		virtual void PrepareAbility2();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Two")
		virtual void Ability2();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Two")
		virtual void Ability2Finished();
	
	// Ability 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Three")
		FTimerHandle Ability3UsageTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Three")
		bool IsUsingAbility3 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Ability Three")
		float Ability3Duration = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "AI Ability Three")
		virtual void PrepareAbility3();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Three")
		virtual void Ability3();
	UFUNCTION(BlueprintCallable, Category = "AI Ability Three")
		virtual void Ability3Finished();

	// Deal Overlapped Damage Function
	UPROPERTY(EditAnywhere, Category = "Overlap")
		TSet<AActor*> OverlappedActors = {};

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void DealDamage2Overlapped();

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void ApplyDamageToMain(float damage);

	// main and enemy positions
	UFUNCTION(BlueprintCallable)
		void UpdatePositions();

	// Extra position function
	UFUNCTION(BlueprintCallable)
		FVector GetRandomNearbyLocationOfPlayer(float Distance);

	// Animation
	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void PlayAnimBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void PlayAnimAbilityOne();
	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void PlayAnimAbilityTwo();
	UFUNCTION(BlueprintCallable, Category = "Animation")
		virtual void PlayAnimAbilityThree();

	UFUNCTION(BlueprintCallable, Category = "Animation")
		void OnMontageBasicAttackEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION(BlueprintCallable, Category = "Animation")
		void OnMontageOneEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION(BlueprintCallable, Category = "Animation")
		void OnMontageTwoEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION(BlueprintCallable, Category = "Animation")
		void OnMontageThreeEnded(UAnimMontage* Montage, bool bInterrupted);

	// reward is directly to main
	UFUNCTION(BlueprintCallable, Category = "Reward")
		void RewardMainCharacter();
};
