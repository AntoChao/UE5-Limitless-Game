// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "meshes/Weapon_GeneralClass.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveVector.h"

#include "TrueProject2GameModeBase.h"
#include "TrueGame2Instance.h"
#include "Common_Enums.h"

// Building Interactions
#include "map/GeneralMapComponent.h"

#include "AllCharactersClass.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class ESpecialStatus : uint8
{
	ENone,
	ETest,
	EStun,
	EForceMoveByTime,
	EForceMoveByStrength,
	ESpeed
};

UCLASS(BlueprintType, Blueprintable)
class LIMITLESS_API AAllCharactersClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAllCharactersClass();

protected:
	// Game Instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance")
		UTrueGame2Instance* GameInstance;

	// Camara
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCamaraComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Health Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
		class UHealthComponent* Health;

	// Health Regenerate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Stats Regeration", meta = (AllowPrivateAccess = "true"))
		float HealthPointRegenerate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Stats Regeration", meta = (AllowPrivateAccess = "true"))
		float HealthRegenerateTime = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Health Regeration")
		FTimerHandle HealthRegenerateTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Health Regeration")
		void HealthRegenerate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Stats Control", meta = (AllowPrivateAccess = "true"))
		float initHealth = 10.0f;

	// Power Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
		class UCharacterPowerComponent* PowerComponent;

	// Speed and Rotation
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector CharacterVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CharacterSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CharacterMaxSpeed = 500.0f;
	// Fly Configuration
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsFlying;

	// Power Component Management
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Stats Control")
		float initPower = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Stats Control")
		float initCritChance = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Stats Control")
		float initCritMult = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Stats Control")
		float initAttackSpeed = 1.0f;

	/* Speed:
	* The player speed is a sum of different factors -> almost never change the default speed, only change other factors
	* Default Speed, RunSpeed, Speed Boost (Frenzy Reward...), Status Boost
	* Each Time some of these value change -> should re calculate the default speed
	*/
	// Basic Movement Stats for all
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void ChangeCurrentMoveSpeed();
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void ResetAllSpeedFactors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control To Set")
		float DefaultMoveSpeed = 700.0f; // should only changed permanently
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float DefaultMoveSpeedRatio = 1.0f; // should only changed permanently
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float MoveSpeed = DefaultMoveSpeed;
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void UpdateDefaultMoveSpeedRatio(float ratio);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control To Set")
		float DefaultRunSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float RunSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float RunSpeedRatio = 1.0f; // just a ratio of running
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void UpdateRunSpeedRatio(float ratio);
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void ResetRunSpeedRatio();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float DefaultSpeedBoost = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float SpeedBoost = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float SpeedBoostRatio = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		FTimerHandle SpeedBoosterTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void UpdateSpeedBoostRatio(float ratio);
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void ResetSpeedBoost();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float DefaultStatusSpeedBoost = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float StatusSpeedBoost = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float StatusSpeedBoostRatio = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		FTimerHandle StatusSpeedBoostTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float StatusSpeedBoosterDuration = 5.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void UpdateStatusSpeedBoostRatio(float ratio);
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void ResetStatusSpeedBoost();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Control")
		float DashDistance; //-> maybe for main only 
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control To Set")
		float ExtraSpeed = 0.0f;
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void UpdateExtraSpeed(float ASpeed);
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void ResetExtraSpeed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		float ImmovilizeSpeed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
		FTimerHandle ImmovilizeTimerHandle;
	
	// Add lots of check for each movement, sprint, jump, crouch, dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Control")
		bool isRunning = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Control")
		bool ableToRun = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Control")
		bool isCrouching = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Control")
		bool isSliding = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Control")
		bool bToSlide = false;
	FTimerHandle SlidingCooldownTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Control")
		bool isDashing = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Control")
		bool isAbleToDash = false;

	// Camera Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FVector CameraLocationStand = FVector(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FRotator CameraRotationStand = FRotator(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FVector CameraLocationCrouch = FVector(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FRotator CameraRotationCrouch = FRotator(0.f, 0.f, 0.f);
	
	
	// Simulate Tick Function
	FTimerHandle TickSimulatorTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Tick")
		float TickSimulateTime = 0.1f;
	
	virtual void CustomTickFunction();

	// Detection 
	UFUNCTION(BlueprintCallable, Category = "Detect")
		void Detect();

	UFUNCTION(BlueprintCallable, Category = "Detect")
		void DetectReaction();

	UFUNCTION(BlueprintCallable, Category = "Detect")
		virtual void BeDetected();

	// Line Trace detection
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace")
		FVector Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace")
		FVector ForwardVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace")
		FVector End;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace")
		FVector ViewEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace")
		FHitResult Hit;

	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;
	
	// Level XPPPPPPPPP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP")
		class UXPComponent* XPComponent;

	UFUNCTION(BlueprintCallable, Category = "XP")
		void UpdateXP(float modifier);
	UFUNCTION(BlueprintCallable, Category = "XP")
		bool IsAbleToSpendXP(float xpAmount);
	UFUNCTION(BlueprintCallable, Category = "XP")
		float GiveXPPercentage();
	UFUNCTION(BlueprintCallable, Category = "XP")
		FText GiveLevelText();
	UFUNCTION(BlueprintCallable, Category = "XP")
		float GiveXP();
	UFUNCTION(BlueprintCallable, Category = "XP")
		float GiveXPRequired();

	virtual void UpdateBasicStatsByLevelingUp();

	// Call when the game ends ??? or should be character died 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Special Status Control
	// Stun -> override the previus stun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Control")
		bool IsStunned;
	FTimerHandle StunStatusTimer;
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void ApplyStunStatus(float Duration);
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void ResetStunStatus();

	//void GetStunned(); -> run the timer to reset
	// void ResetTheStunStatus() -> reset the stun value
	
	// ForceToMove
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		bool bGotForceToMove();

		// force to move variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Control")
		bool bForcedToMoveInTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Control")
		bool bForcedToMoveByStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Control")
		FVector ForcedToMoveLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Control")
		FTimerHandle ForToMoveTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Control")
		float SegsForMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Control")
		float StrengthForMove;

		// force to move by time
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void StartForceToMoveInTime(FVector TargetLocation, float Segs);
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void ForceToMoveInTime(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void ForceToMoveInTimeFinished();

		// force to move by speed/strength
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void StartForceToMoveByStrength(FVector TargetLocation, float Strength);
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void ForceToMoveByStrength(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void ForceToMoveByStrengthFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Control")
		bool isInShadow;

	// Building Interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Interaction")
		EFloorType CurrentFloorType;

	// Reset Everything
	UFUNCTION(BlueprintCallable, Category = "Reset")
		virtual void ResetCharacterStats();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// return Componenets values
	UFUNCTION(BlueprintCallable, Category = "Health")
		float GiveHealthPercentage();
	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetCharacterHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetCharacterMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Camera")
		FVector GetForwardDirection();

	// Basic Character functions
	// Movement
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void Move(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void Run();
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void RunEnd();
	//void Jump();
	//void JumpEnd();
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void Dash();
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void CrouchStart();
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void CrouchEnd();
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void Sliding();
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void ResetSlidingStatus();

	// Camara
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void Look(const FInputActionValue& Value);

	// Set player moment location and rotation
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		FVector GetPlayerPosition();
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		FRotator GetPlayerRotation();

	// Health Component Management
	// Set max health -> set the maxHealth and Health value to character as init
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void InitCharacHealth(float HP);

	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateHealthPoint(float healthModifier);
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void FullHeal();
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateHealthByCurrentPercentage(float healthModifier);
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateHealthByMaxPercentage(float healthModifier);
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateMaxHealth(float healthModifier, float maxHealthModifier);

	// Power Component Management
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		UCharacterPowerComponent* GetCharacterPowerComponent();
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateCharacterPowerUp(float PowerValue);
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateCharacterPowerUpPercentage(float PowerValuePercentage);
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateCharacterCritChance(float CritChanceValue);
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateCharacterCritMultiplier(float CritMultiplierValue);
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void UpdateCharacterAttackRate(float AttackRateValue);

	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		float GetPlayerAttackRate();

	// Receive Damage
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		bool isPlayerDied();
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	FTimerHandle DestroyTimeHandle;
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void TrueDied();
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void DestroyDelay();
	UFUNCTION(BlueprintCallable, Category = "Stats Control")
		void Revive(float percentage);

	// Movement function
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void SetIsAbleToFly(bool flyState);
	
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void UpdateDefaultMoveSpeed(float ratio);
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void ReceiveSpeedBoost(float ratio, float SpeedBoosterDuration);
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void ReceiveStatusSpeedBoost(float statusduration, float ratio);
	UFUNCTION(BlueprintCallable, Category = "Speed Control")
		void Immovilize(float immovilzeTime);

	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void SetDashDistance(float initSpeed);
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void SetIsRunning(bool checkRunning);
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void SetIsCrouching(bool checkCrouching);
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void SetIsSliding(bool checkSliding);
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void SetAbleToSlide(bool modifier);
	UFUNCTION(BlueprintCallable, Category = "Movement Control")
		void SetIsDashing(bool checkDashing);

	// Special Status Control
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		void ReceiveSpecialStatus(ESpecialStatus SpecialStatus,
			float Duration, float modifier, FVector Location);

	// for those status that change actor behaviour -> stun/ ForcedToMove...
	UFUNCTION(BlueprintCallable, Category = "Special Control")
		bool isBehaviourChanged();

	// Building Interaction
	UFUNCTION(BlueprintCallable, Category = "Environment Interaction")
		void SetCurrentFloor(EFloorType AFloorType);

	// Bones controls
	// FVector GetLeftHandLocation();

	// Sounds and Particles
	UFUNCTION(BlueprintCallable, Category = "Audio")
		void PlaySound(class USoundBase* Sound2Play, FVector Location2Play, FRotator Rotation2Play);

	UFUNCTION(BlueprintCallable, Category = "VFX")
		void SpawnNiagara(class UNiagaraSystem* Niagara2Play, FVector Location2Play, FRotator Rotation2Play);
	
};
