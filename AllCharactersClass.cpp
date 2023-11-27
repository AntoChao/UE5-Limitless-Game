// Fill out your copyright notice in the Description page of Project Settings.


#include "AllCharactersClass.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "components/HealthComponent.h"
#include "components/CharacterPowerComponent.h"
#include "components/XPComponent.h"
#include "Math/UnrealMathUtility.h" // idk if is this file

// Timer managment
#include "TimerManager.h"

// UI/ Widget
#include "Blueprint/UserWidget.h"
#include "WidgetsBase/PlayerStatsUMG.h"

// Sets default values
AAllCharactersClass::AAllCharactersClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Character Health"));
	XPComponent = CreateDefaultSubobject<UXPComponent>(TEXT("Character XP"));
	PowerComponent = CreateDefaultSubobject<UCharacterPowerComponent>(TEXT("Character Power"));
}

// Called when the game starts or when spawned
void AAllCharactersClass::BeginPlay()
{
	Super::BeginPlay();

	// Set game instance
	GameInstance = Cast<UTrueGame2Instance>(UGameplayStatics::GetGameInstance(this));

	// set power basic stats
	PowerComponent->SetPower(5.0f);
	PowerComponent->SetCharacCritChance(0.0f);
	PowerComponent->SetCharacCritMultiplier(1.0f);
	PowerComponent->SetCharacAttackRate(1.0f);

	// Special Status
	// Stun
	IsStunned = false;

	// Forces
	bForcedToMoveInTime = false;
	bForcedToMoveByStrength = false;
	ForcedToMoveLocation = FVector(0.0f, 0.0f, 0.0f);
	SegsForMove = 0.0f;
	StrengthForMove = 0.0f;

	// Speed
	DefaultMoveSpeed = 700.0f;
	MoveSpeed = DefaultMoveSpeed;

	DefaultRunSpeed = 300.0f;
	DefaultSpeedBoost = 10.0f;
	DefaultStatusSpeedBoost = 10.0f;
}

// EndPlay
void AAllCharactersClass::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AAllCharactersClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGotForceToMove())
	{
		if (bForcedToMoveInTime)
		{
			ForceToMoveInTime(DeltaTime);
		}
		else 
		{
			if (bForcedToMoveByStrength)
			{
				ForceToMoveByStrength(DeltaTime);
			}
		}
	}
}

void AAllCharactersClass::CustomTickFunction()
{
	GetWorldTimerManager().SetTimer(TickSimulatorTimer, this,
		&AAllCharactersClass::CustomTickFunction, TickSimulateTime, true);

	CharacterVelocity = GetCharacterMovement()->Velocity;
	CharacterSpeed = CharacterVelocity.Size();
}

// return Componenets values
// Health
float AAllCharactersClass::GiveHealthPercentage()
{
	return Health->GetHealthPercentage();
}
float AAllCharactersClass::GetCharacterHealth()
{
	return Health->GetHealth();
}

// XP
void AAllCharactersClass::UpdateXP(float modifier)
{
	XPComponent->ReceiveXP(modifier);
}
bool AAllCharactersClass::IsAbleToSpendXP(float xpAmount)
{
	return XPComponent->isAbleToBuy(xpAmount);
}
float AAllCharactersClass::GiveXPPercentage()
{
	return XPComponent->GetXPPercentage();
}

FText AAllCharactersClass::GiveLevelText()
{
	return XPComponent->GetLevelText();
}



// update health, power...stats depending level
void AAllCharactersClass::UpdateBasicStatsByLevelingUp()
{
	return;
}

void AAllCharactersClass::Detect()
{
	//Expose function, should not be an attack
	if (IsValid(FirstPersonCamaraComponent))
	{
		Start = FirstPersonCamaraComponent->GetComponentLocation();
		ForwardVector = FirstPersonCamaraComponent->GetForwardVector();
		End = ((ForwardVector * 200000.f) + Start);
		ViewEnd = ((ForwardVector * 10000.f) + Start);

		// DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, DefaultComponentQueryParams, DefaultResponseParam);
		DetectReaction();
	}
}

void AAllCharactersClass::DetectReaction()
{
	// let the enemy health bar to be visible
	if (Hit.bBlockingHit)
	{
		if (IsValid(Hit.GetActor()))
		{
			AEnemyClass* EnemyDelta = Cast<AEnemyClass>(Hit.GetActor());
			if (IsValid(EnemyDelta))
			{
				EnemyDelta->SetHealthBarVisible();
			}
		}
	}
}

FVector AAllCharactersClass::GetForwardDirection()
{
	return ForwardVector;
}

void AAllCharactersClass::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}
void AAllCharactersClass::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
//custom jump, need to be upgraded 
/*
void APlayerCharacter::Jump()
{
	ttps://www.youtube.com/watch?v=oe2vPXvFLpI
}

void APlayerCharacter::JumpEnd()
{
	return;
}
*/

void AAllCharactersClass::Run()
{
	if (!isCrouching)
	{
		if (!isRunning)
		{
			RunSpeed = DefaultRunSpeed * RunSpeedRatio;
			ChangeCurrentMoveSpeed();
			isRunning = true;
		}
	}
}
void AAllCharactersClass::RunEnd()
{
	RunSpeed = 0.0f;
	ChangeCurrentMoveSpeed();
	isRunning = false;
}

/*Dash should be better define: 
	1 : No infinite 
	2 : Distance should be progresive
*/
void AAllCharactersClass::Dash()
{
	const FVector ForwardDir = this->GetActorRotation().Vector();
	LaunchCharacter(ForwardDir * DashDistance, true, true);
}
void AAllCharactersClass::CrouchStart()
{
	if (isRunning)
	{
		isSliding = true;	
		if ((GetCharacterMovement()->MaxWalkSpeed > 200.0f) && (bToSlide))
		{
			Sliding();
		}
		else
		{
			CrouchEnd();
		}
	}
	else
	{
		isCrouching = true;
		this->FirstPersonCamaraComponent->SetRelativeLocation(CameraLocationCrouch);
	}
}
void AAllCharactersClass::CrouchEnd()
{
	if (isCrouching)
	{
		this->FirstPersonCamaraComponent->SetRelativeLocation(CameraLocationStand);
		isCrouching = false;
	}
	else
	{
		bToSlide = false;
		isSliding = false;
		GetWorldTimerManager().SetTimer(SlidingCooldownTimerHandle, this, &AAllCharactersClass::ResetSlidingStatus, 8.0f, false);

		ChangeCurrentMoveSpeed();
	}
}
void AAllCharactersClass::Sliding()
{
	if (isSliding)
	{
		ReceiveSpeedBoost(0.99f, 5.0f);
	}
}
void AAllCharactersClass::ResetSlidingStatus()
{
	bToSlide = true;
}

// Health Component Management
void AAllCharactersClass::InitCharacHealth(float InitHealth)
{
	Health->InitHealth(InitHealth);
}
void AAllCharactersClass::UpdateHealthPoint(float healthModifier)
{
	Health->UpdateHealthFloat(healthModifier);
}
void AAllCharactersClass::UpdateHealthByCurrentPercentage(float healthModifier)
{
	Health->UpdateHealthByPercentageOfCurrentHealth(healthModifier);
}
void AAllCharactersClass::UpdateHealthByMaxPercentage(float healthModifier)
{
	Health->UpdateHealthByPercentageOfMaxHealth(healthModifier);
}
void AAllCharactersClass::UpdateMaxHealth(float healthModifier, float maxHealthModifier)
{
	Health->UpdateMaxHealth(healthModifier, maxHealthModifier);
}

// Power Component Management
UCharacterPowerComponent* AAllCharactersClass::GetCharacterPowerComponent()
{
	return PowerComponent;
}

void AAllCharactersClass::UpdateCharacterPowerUp(float PowerValue)
{
	PowerComponent->UpdateFlatPower(PowerValue);
}
void AAllCharactersClass::UpdateCharacterPowerUpPercentage(float PowerValuePercentage)
{
	PowerComponent->UpdatePercentagePower(PowerValuePercentage);
}
void AAllCharactersClass::UpdateCharacterCritChance(float CritChanceValue)
{
	PowerComponent->UpdateCritChance(CritChanceValue);
}
void AAllCharactersClass::UpdateCharacterCritMultiplier(float CritMultiplierValue)
{
	PowerComponent->UpdateCritMultiplier(CritMultiplierValue);
}
void AAllCharactersClass::UpdateCharacterAttackRate(float AttackRateValue)
{
	PowerComponent->UpdateAttackRate(AttackRateValue);
}

float AAllCharactersClass::GetPlayerAttackRate()
{
	return PowerComponent->GetCharacAttackRate();
}

// Receive Damage:
bool AAllCharactersClass::isPlayerDied()
{
	return Health->GetDied();
}

// Receive Damage by point or radial damage
// Be override by main and enemy, main need loop defense artifact, enemy need to give out reward
float AAllCharactersClass::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageCaused = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return DamageCaused;
}

void AAllCharactersClass::TrueDied()
{
	// simulate phisics = true ***********
	//GetWorldTimerManager().SetTimer(DestroyTimeHandle, this, &AAllCharactersClass::DestroyDelay, 5.0f, false);
}

void AAllCharactersClass::DestroyDelay()
{
	Destroy();
}

void AAllCharactersClass::Revive(float percentage)
{
	Health->SetDied(false);
	float deltaAmountHealth = Health->GetMaxHealth() * percentage;
	InitCharacHealth(deltaAmountHealth);
}

void AAllCharactersClass::SetIsAbleToFly(bool flyState)
{
	bIsFlying = flyState;
}

// For widget use -> in order to get percentage for show
void AAllCharactersClass::SetDashDistance(float initDashDistance)
{
	DashDistance = initDashDistance;
}
void AAllCharactersClass::SetIsRunning(bool checkRunning)
{
	isRunning = checkRunning;
}
void AAllCharactersClass::SetIsCrouching(bool checkCrouching)
{
	isCrouching = checkCrouching;
}
void AAllCharactersClass::SetIsSliding(bool checkSliding)
{
	isSliding = checkSliding;
}
void AAllCharactersClass::SetAbleToSlide(bool modifier)
{
	bToSlide = modifier;
}
void AAllCharactersClass::SetIsDashing(bool checkDashing)
{
	isDashing = checkDashing;
}

/*Update Basic Stats
If change the default MoveSpeed -> use setMoveSpeed()
run == is updating the moveSpeed -> never change the ratio, only change the default moveSpeed
artifact == update defaultSpeed
moveSpeedBoost -> also updating the moveSpeed -> but has a timer which going to delete the moveSpeedAfter x Time
				  But if meanwhile get a new one, restart the timer
*/

// Speed Control
void AAllCharactersClass::ChangeCurrentMoveSpeed()
{
	MoveSpeed = DefaultMoveSpeed + RunSpeed + SpeedBoost + StatusSpeedBoost + ExtraSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}
void AAllCharactersClass::ResetAllSpeedFactors()
{
	MoveSpeed = DefaultMoveSpeed;
	RunSpeed = 0.0f;
	SpeedBoost = 0.0f;
	StatusSpeedBoost = 0.0f;
}

void AAllCharactersClass::UpdateDefaultMoveSpeed(float ratio)
{
	// update the ratio
	UpdateDefaultMoveSpeedRatio(ratio);

	// set the default move speed
	DefaultMoveSpeed = DefaultMoveSpeed * DefaultMoveSpeedRatio;
	ChangeCurrentMoveSpeed();
}
void AAllCharactersClass::UpdateDefaultMoveSpeedRatio(float ratio)
{
	DefaultMoveSpeedRatio = DefaultMoveSpeedRatio * ratio;
}

void AAllCharactersClass::UpdateRunSpeedRatio(float ratio)
{
	RunSpeedRatio = RunSpeedRatio * ratio;
}
void AAllCharactersClass::ResetRunSpeedRatio()
{
	RunSpeedRatio = 1.0f;
}

void AAllCharactersClass::ReceiveSpeedBoost(float ratio, float SpeedBoosterDuration)
{
	// update the speed boost ratio
	UpdateSpeedBoostRatio(ratio);
	// calculate the speed boost
	SpeedBoost = DefaultSpeedBoost * SpeedBoostRatio;
	// set the value
	ChangeCurrentMoveSpeed();
	// run a timer
	GetWorldTimerManager().SetTimer(SpeedBoosterTimerHandle, this,
		&AAllCharactersClass::ResetSpeedBoost, SpeedBoosterDuration, true);
}
void AAllCharactersClass::UpdateSpeedBoostRatio(float ratio)
{
	SpeedBoostRatio = SpeedBoostRatio * ratio;
}
void AAllCharactersClass::ResetSpeedBoost()
{
	SpeedBoost = 0.0f;
	SpeedBoostRatio = 1.0f;
	ChangeCurrentMoveSpeed();
}

void AAllCharactersClass::ReceiveStatusSpeedBoost(float statusduration, float ratio)
{
	// update the speed boost ratio
	UpdateStatusSpeedBoostRatio(ratio);
	// calculate the speed boost
	StatusSpeedBoost = DefaultStatusSpeedBoost * StatusSpeedBoostRatio;
	// set the value
	ChangeCurrentMoveSpeed();
	// run a timer
	GetWorldTimerManager().SetTimer(StatusSpeedBoostTimer, this,
		&AAllCharactersClass::ResetStatusSpeedBoost, statusduration, true);
}
void AAllCharactersClass::UpdateStatusSpeedBoostRatio(float ratio)
{
	StatusSpeedBoostRatio = StatusSpeedBoostRatio * ratio;
}
void AAllCharactersClass::ResetStatusSpeedBoost()
{
	StatusSpeedBoost = 0.0f;
	StatusSpeedBoostRatio = 1.0f;
	ChangeCurrentMoveSpeed();
}

void AAllCharactersClass::UpdateExtraSpeed(float ASpeed)
{
	ExtraSpeed = ASpeed;
	ChangeCurrentMoveSpeed();
}

void AAllCharactersClass::ResetExtraSpeed()
{
	ExtraSpeed = 0.0f;
	ChangeCurrentMoveSpeed();
}


// Position and Rotation
FVector AAllCharactersClass::GetPlayerPosition()
{
	return GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
}

FRotator AAllCharactersClass::GetPlayerRotation()
{
	return GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();
}

// Special Status Control
// General Status Control
void AAllCharactersClass::ReceiveSpecialStatus(ESpecialStatus SpecialStatus,
	float Duration, float modifier, FVector Location)
{
	switch (SpecialStatus)
	{
		case ESpecialStatus::ETest:
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Got Special Status Test"));
			break;
		}
		case ESpecialStatus::EStun:
		{
			// it is just once time, does not need to check per tick
			ApplyStunStatus(Duration);
			break;
		}
		case ESpecialStatus::EForceMoveByTime:
		{
			StartForceToMoveInTime(Location, Duration);
			break;
		}
		case ESpecialStatus::EForceMoveByStrength:
		{
			StartForceToMoveByStrength(Location, modifier);
			break;
		}
		case ESpecialStatus::ESpeed:
		{
			ReceiveStatusSpeedBoost(Duration, modifier);
			break;
		}
		default:
		{
			break;
		}
	}
}
bool AAllCharactersClass::isBehaviourChanged()
{
	return IsStunned || bGotForceToMove();
}

// Stun Status
void AAllCharactersClass::ApplyStunStatus(float Duration)
{
	IsStunned = true;
	GetCharacterMovement()->SetMovementMode(IsStunned ? MOVE_None : MOVE_Walking);
	GetWorldTimerManager().SetTimer(StunStatusTimer, this,
		&AAllCharactersClass::ResetStunStatus, Duration, false);
}

void AAllCharactersClass::ResetStunStatus()
{
	IsStunned = false;
	GetCharacterMovement()->SetMovementMode(IsStunned ? MOVE_None : MOVE_Walking);
}

// Force to Move
	// For Behaviour Tree to cut the MoveTo() logic flow 
bool AAllCharactersClass::bGotForceToMove()
{
	return bForcedToMoveInTime || bForcedToMoveByStrength;
}
	// Force to Move In Time
	// Call by other class
void AAllCharactersClass::StartForceToMoveInTime(FVector TargetLocation, float Segs)
{
	bForcedToMoveInTime = true;
	ForcedToMoveLocation = TargetLocation;
	SegsForMove = Segs;
	
	// set a timer to reset the status
	if (bForcedToMoveInTime)
	{
		// A timer for finish
		GetWorldTimerManager().SetTimer(ForToMoveTimer, this,
			&AAllCharactersClass::ForceToMoveInTimeFinished, SegsForMove, false);
	}
}
	// Need to be called in tick function
void AAllCharactersClass::ForceToMoveInTime(float DeltaTime)
{
	// Calculate the direction and distance to the target location.
	FVector DirectionToTarget = (ForcedToMoveLocation - GetActorLocation()).GetSafeNormal();
	float DistanceToTarget = FVector::Dist(ForcedToMoveLocation, GetActorLocation());

	// Calculate the speed (distance to move per second).
	float Speed = DistanceToTarget / SegsForMove;

	// Calculate the increment to move this frame.
	FVector MovementIncrement = DirectionToTarget * Speed * DeltaTime;

	// Move the actor incrementally towards the target location.
	SetActorLocation(GetActorLocation() + MovementIncrement, true);
}

void AAllCharactersClass::ForceToMoveInTimeFinished()
{
	bForcedToMoveInTime = false;
	ForcedToMoveLocation = FVector(0.0f, 0.0f, 0.0f);
	SegsForMove = 0.0f;
}

	// Force to Move By Strength
void AAllCharactersClass::StartForceToMoveByStrength(FVector TargetLocation, float Strength)
{
	bForcedToMoveByStrength = true;
	ForcedToMoveLocation = TargetLocation;
	StrengthForMove = Strength;
}

void AAllCharactersClass::ForceToMoveByStrength(float DeltaTime)
{
	// Calculate the direction and distance to the target location.
	FVector DirectionToTarget = (ForcedToMoveLocation - GetActorLocation()).GetSafeNormal();
	float DistanceToTarget = FVector::Dist(ForcedToMoveLocation, GetActorLocation());

	// Calculate the increment to move this frame.
	FVector MovementIncrement = DirectionToTarget * StrengthForMove * DeltaTime;

	// Move the actor incrementally towards the target location.
	SetActorLocation(GetActorLocation() + MovementIncrement, true);
}
void AAllCharactersClass::ForceToMoveByStrengthFinished()
{
	bForcedToMoveByStrength = false;
	ForcedToMoveLocation = FVector(0.0f, 0.0f, 0.0f);
	StrengthForMove = 0.0f;
}

void AAllCharactersClass::SetCurrentFloor(EFloorType AFloorType)
{
	CurrentFloorType = AFloorType;
}

// Reset All Variables/ Pointers -> Be overrided by childen class
void AAllCharactersClass::ResetCharacterStats()
{
	return;
}

// useless
void AAllCharactersClass::PlaySound(class USoundBase* Sound2Play, FVector Location2Play, FRotator Rotation2Play)
{
	if (Sound2Play)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound2Play, Location2Play, Rotation2Play);
	}
}

void AAllCharactersClass::SpawnNiagara(class UNiagaraSystem* Niagara2Play, FVector Location2Play, FRotator Rotation2Play)
{

	if (IsValid(Niagara2Play))
	{
		//GetWorld()->SpawnActor<UNiagaraComponent>(Niagara2Play->GetClass(), Location2Play, Rotation2Play, ActorSpawnParams);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara2Play, Location2Play, Rotation2Play);
	}
}