// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AllCharactersClass.h"
// killfeddback container
#include "DataContainer/data_killfeedbackinfo.h"

// Artifacts
#include "Artifacts/GeneralArtifact.h"
#include "Artifacts/GeneralPickUpArtifact.h"
#include "Artifacts/GeneralAttackArtifact.h"
#include "Artifacts/GeneralDefenseArtifact.h"
#include "Artifacts/GeneralCostArtifact.h"
#include "Artifacts/GeneralKillFeedBackArtifact.h"
#include "Artifacts/GeneralDiedArtifact.h"

#include "Main.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TRUEPROJECT2_API AMain : public AAllCharactersClass
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

protected:

	// Character Composition
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ResetCharacterStats() override;

	// Get and Set GameInstance Stats
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
		void ProcessGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostGame Stats")
		float TotalDamage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostGame Stats")
		int TotalEnemiesKilled = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostGame Stats")
		float TotalDamageTaken = 0.0f;


	// MainBody
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* BodyComponent;

	// Detection Radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection Component")
		bool bDetection = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection Component")
		float DefaultDetectionAreaRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection Component")
		float NewDetectionAreaRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection Component")
		class USphereComponent* DetectionArea;

	// Main Controller
	UPROPERTY(EditAnywhere)
		class AMainController* MainController;

	// UI/ Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Main")
		TSubclassOf<class UPlayerStatsUMG> PlayerHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Main")
		class UPlayerStatsUMG* PlayerHUD;

	//Basic Stats for main
	// Frenzy Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		class UFrenzyComponent* Frenzy;
	// Calm Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		class UCalmComponent* Calm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float CalmGrowRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FTimerHandle CalmGrownTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float CalmGrownCooldown = 1.0f;
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void PermaGrowCalm();
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void CalmToPowerConverter(float calmAmount);

	// The converter power by calm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float BaseCalmPower = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float CalmPowerMultiplier = 1.0f;
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void ResetCalmMultiplier();

	// Ability Select
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		class AAbilitySystem* AbilitySystem;

	// AbilityRequiredInfo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		class UData_AbilityRequiredInfo* AbilityRequiredContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability"	)
		class UData_AbilityFeedBackInfo* FeedBackContainer;

	// Animation and Bones control
	// Player sockets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Body Control")
		FName Front_Socket = FName("Socket_Front");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Body Control")
		FName Left_Hand_Socket = FName("Socket_LeftHand");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Body Control")
		FName Left_Hand_Socket_Throw = FName("Socket_LeftHand_Throw");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Body Control")
		FName Right_Hand_Socket = FName("Socket_RightHand");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Body Control")
		FVector Front_Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Body Control")
		FVector Left_Hand_Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Body Control")
		FVector Right_Hand_Position;

	// General Weapon position
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		FRotator WeaponRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
		FRotator FireRotation;
	
	// Specific Weapon position
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Body Control")
		FName Weapon_Left_Hand_Socket = FName("Socket_Left_Hand");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Body Control")
		FName Weapon_Right_Hand_Socket = FName("Socket_Right_Hand");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Body Control")
		FName Weapon_Fire_Point_Socket = FName("Socket_Fire");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Body Control")
		FVector Weapon_Left_Hand_Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Body Control")
		FVector Weapon_Right_Hand_Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Body Control")
		FVector Weapon_Fire_Point_Position;

	// Weapons Meshes and classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Pistol> PistolClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_Pistol* Weapon_Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Shotgun> ShotgunClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_Shotgun* Weapon_Shotgun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_SniperRifle> SniperRifleClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_SniperRifle* Weapon_SniperRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_Blade> BladeClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_Blade* Weapon_Blade;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class AWeapon_BlackHoleBomb> BlackHoleBombClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AWeapon_BlackHoleBomb* Weapon_BlackHoleBomb;

	// Animation
	UFUNCTION(BlueprintCallable)
		void PlaySelectedMontage(UAnimMontage* ChosenMontage, float PlayRate);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		bool IsDoingAnAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		EAbilityCode LastAbilityUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* PistolFire_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* ShotgunFire_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* SniperRifleFire_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* SwordAttack_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* ThrowBlackHoleBomb_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* AlienGunFire_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* ThrowBaiterBomb_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* WallBreaker_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* PlaceWireTrap_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* InvokeShadowSolder_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* ShadowTravel_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* ReverseProjectiles_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* Teleport_PutMark_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* Teleport_TP_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* SwitchDimention_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* StartBulletTime_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* StartFForward_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* ParalysisEnemies_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* OpenCommand_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* SumEagle_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* SumBigFoot_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* SumRabbit_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* OpenItemBox_Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montage")
		UAnimMontage* GetAttacked_Montage;
	
	// Default AbilityChosen
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		EAbilityCode DefaultAbilityChosen;
	// Weapons In Hand
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		EAbilityCode CurrentAbilityInHand;

	// Abilities
	// Abilities codes corresponde -> just like enum but enum does not work
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		EAbilityCode PassiveChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		EAbilityCode BasicAttackChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		EAbilityCode AbilityOneChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		EAbilityCode AbilityTwoChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		EAbilityCode AbilityThreeChosen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		EAbilityCode AbilityFourChosen;

	// An array of abilities that need 2бу further input or change input system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		TSet<EAbilityCode> AbilitiesChangeInput;

	// Create required info container
	void CreateRequirementContainer(EAbilityCode abilityCode);

	// All artifacts arrays
	// There is the total artifact list to show in HUD
	// and there is the separate artifact list by type which help the performance
	UPROPERTY(EditAnywhere, Category = "Artifact")
		TArray<AGeneralArtifact*> AllArtifactList = {};
	UPROPERTY(EditAnywhere, Category = "Artifact")
		TArray<AGeneralPickUpArtifact*> AllPickUpArtifactList = {};
	UPROPERTY(EditAnywhere, Category = "Artifact")
		TArray<AGeneralAttackArtifact*> AllAttackArtifactList = {};
	UPROPERTY(EditAnywhere, Category = "Artifact")
		TArray<AGeneralDefenseArtifact*> AllDefenseArtifactList = {};
	UPROPERTY(EditAnywhere, Category = "Artifact")
		TArray<AGeneralCostArtifact*> AllAbilityCostArtifactList = {};
	UPROPERTY(EditAnywhere, Category = "Artifact")
		TArray<AGeneralDiedArtifact*> AllDiedArtifactList = {};
	UPROPERTY(EditAnywhere, Category = "Artifact")
		TArray<AGeneralKillFeedBackArtifact*> AllKillFeedBackArtifactList = {};

	// Further protected variables and function for abilities uses
	// Ability Reverse Projectiles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		TSubclassOf<class AWeapon_ReverseProjectile> AWeapon_ReverseProjectile_Class;

	// Ability TP Mark
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		TSubclassOf<class AWeapon_TeleportMark> AWeapon_TeleportMark_Class;
	
	// Ability BulletTime
	// A Bool to disable respawn the niagara
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		bool bBulletTimeNiagaraSpawned = false;

	// Ability FForward
	// A Bool to disable respawn the niagara
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		bool bFForwardNiagaraSpawned = false;

	// Ability Mom Foot Mark
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		TSubclassOf<class AWeapon_MomFoot> AWeapon_MomFoot_Class;

public:	
	// Game Instance
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
		void SetStatsToGameInstance();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Game Instance stuff
	UFUNCTION(BlueprintCallable, Category = "Detection Component")
		void UpdateTotalDamage(float damage);
	// at default +1
	UFUNCTION(BlueprintCallable, Category = "Detection Component")
		void UpdateTotalEnemiesKilled();
	UFUNCTION(BlueprintCallable, Category = "Detection Component")
		void UpdateTotalDamageTaken(float damageTaken);

	// Body Part
	float GetMainHalfHeight();

	// Detection around player
	// Normally, should scale the radius -> get actors -> reset scale
	UFUNCTION(BlueprintCallable, Category = "Detection Component")
		void SetNewDetectionAreaRadius(float NewScale);
	UFUNCTION(BlueprintCallable, Category = "Detection Component")
		float GetNewDetectionAreaRadius();
	UFUNCTION(BlueprintCallable, Category = "Detection Component")
		void ResetDetectionAreaRadius();
	UFUNCTION(BlueprintCallable, Category = "Detection Component")
		TArray<AActor*> GetAllDetectedActors();
	UFUNCTION(BlueprintCallable, Category = "Detection Component")
		bool isMainDetecting();

	// UI
	UFUNCTION(BlueprintCallable, Category = "Main UI")
		UPlayerStatsUMG* GetPlayerUIWidget();

	UFUNCTION(BlueprintCallable, Category = "Main UI")
		void UpdateDisplayVariables();

	// Controller
	UFUNCTION(BlueprintCallable, Category = "Main Controller")
		void InitializeMainController();
	UFUNCTION(BlueprintCallable, Category = "Main Controller")
		AMainController* GetMainController();

	UFUNCTION(BlueprintCallable, Category = "Ability")
		void UsePassive();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void UseBasicAttack();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void UseAbilityOne();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void UseAbilityTwo();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void UseAbilityThree();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void UseAbilityFour();

	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SpendAllCalm();

	// Stats
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void UpdateCalmGrowRate(float modifier);

	// ABILITIES CONTROL -> DEFAULT + CURRENT + LAST USED
	UFUNCTION(BlueprintCallable, Category = "Ability")
		EAbilityCode GetDefaultAbilityChosen();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void SetDefaultAbilityChosen(EAbilityCode NewAbilityChosen);
	UFUNCTION(BlueprintCallable, Category = "Ability")
		EAbilityCode GetCurrentAbilityInHand();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void SetCurrentAbilityInHand(EAbilityCode NewAbilityInHand);
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
		EAbilityCode GetLastAbilityUsed();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void SetLastAbilityUsed(EAbilityCode NewAbilityChosen);

	// Call its ability system to grand ability
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void SetAbility(int Slot, EAbilityCode AbilityCode);

	// Basic Attack Weapons Settings
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void GetWeaponSocketsInfo();
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void AttachWeaponSelected(EAbilityCode AbilityCode);

	// Animation
	UFUNCTION(BlueprintCallable)
		void PlayMontages(EAbilityCode abilityCode, float PlayRate);
	UFUNCTION(BlueprintCallable)
		void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION(BlueprintCallable)
		bool IsPlayerInAnimation();

	// process the feed back container
	UFUNCTION(BlueprintCallable)
		void ProcessAbilityFeedBacks();
	UFUNCTION(BlueprintCallable)
		void ProcessKillFeedBacks(UData_KillFeedBackInfo* KillFeedBack);

	// return Componenets values
	// is defined in allCharacter virtual float GiveHealthPercentage() override;
	UFUNCTION(BlueprintCallable)
		virtual float GiveFrenzyPercentage();
	UFUNCTION(BlueprintCallable)
		virtual float GiveCalmPercentage();

	UFUNCTION(BlueprintCallable)
		void ChangeMainFrenzy(float modifier);
	UFUNCTION(BlueprintCallable)
		void ChangeMainCalm(float modifier);

	// Take Damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Get/Add Artifact
	UFUNCTION(BlueprintCallable)
		void GetArtifact(AActor* AArtifact);

	// apply all artifact by type at once
	/*
	* Receive/ Add artifacts
	* PickUp -> never apply all together, should be apply one by one (When player
							receive a artifact, if it is pickup, then execute it)
	* Attack -> apply together when calculate damage (hard, because there are 
									so many way to execute attack, may differ)
	* Defense -> apply all together when the player got damaged
	* KillFeedBack -> Every Enemy ackownledge main character, when they die, apply all artifacts
	* Died -> EveryTime when player died -> need to delegate to died logic
	*/
	UFUNCTION(BlueprintCallable)
		void EliminateAllPickUpArtifactsEffect(AMain* PlayerMain);
	UFUNCTION(BlueprintCallable)
		float ApplyAllAttackArtifacts(float deltaDamage, FHitResult EnemyHit, AMain* PlayerMain);
	UFUNCTION(BlueprintCallable)
		float ApplyAllDefenseArtifacts(float alphaDamage, AMain* PlayerMain);
	UFUNCTION(BlueprintCallable)
		float ApplyAllFrenzyCostArtifacts(float frenzyCost, AMain* PlayerMain);
	UFUNCTION(BlueprintCallable)
		float ApplyAllCalmCostArtifacts(float CalmCost, AMain* PlayerMain);
	UFUNCTION(BlueprintCallable)
		UData_KillFeedBackInfo* ApplyAllKillerFeedBackArtifacts(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy);
	UFUNCTION(BlueprintCallable)
		bool ApplyAllDiedArtifacts(AMain* PlayerMain);

	// Functions for abilities extension
	// Get Hands Transform
	UFUNCTION(BlueprintCallable)
		FTransform GetMainRightHandTrans();
	UFUNCTION(BlueprintCallable)
		FTransform GetMainLeftHandTrans();
	UFUNCTION(BlueprintCallable)
		FTransform GetMainLeftHandThrowTrans();

	// Ability Bomb
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Bomb Throw")
		float ThrowForceMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Bomb Throw")
		float ThrowForceVertical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Bomb Throw")
		FVector BombDestination;
	UFUNCTION(BlueprintCallable, Category = "Ability Bomb Throw")
		void SpawnAndAttachBHBomb();
	UFUNCTION(BlueprintCallable, Category = "Ability Bomb Throw")
		void ReleaseBHBomb();

	// Ability Reverse Projectiles
	UFUNCTION(BlueprintCallable)
		TSubclassOf<class AWeapon_ReverseProjectile> GetReverseProjectilesClass();

	// Ability TP Mark
	UFUNCTION(BlueprintCallable)
		TSubclassOf<class AWeapon_TeleportMark> GetTPMarkClass();

	// Ability Mom foot
	UFUNCTION(BlueprintCallable)
		TSubclassOf<class AWeapon_MomFoot> GetMomFootClass();

	// Ability BulletTime
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void SetIsBulletTimeNiagaraSpawned(bool SpawnState);
	UFUNCTION(BlueprintCallable, Category = "Ability")
		bool GetIsBulletTimeNiagaraSpawned();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
		void AttachBulletTimeNiagara();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
		void DestroyBulletTimeNiagara();

	// Ability FForward
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void SetIsFForwardNiagaraSpawned(bool SpawnState);
	UFUNCTION(BlueprintCallable, Category = "Ability")
		bool GetIsFForwardNiagaraSpawned();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
		void AttachFForwardNiagara();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Ability")
		void DestroyFForwardNiagara();
};
