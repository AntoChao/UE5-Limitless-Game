// Fill out your copyright notice in the Description page of Project Settings.

// Basics:
#include "Main.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TrueGame2Instance.h"

//Enemies to recognize:
#include "All_Enemies/EnemyClass.h"
//Components:
#include "components/HealthComponent.h"
#include "components/FrenzyComponent.h"
#include "components/CalmComponent.h"
#include "components/CharacterPowerComponent.h"
#include "components/XPComponent.h"

// Ability System
#include "AbilitySystem/AbilitySystem.h"

// Container
#include "DataContainer/Data_AbilityRequiredInfo.h"
#include "DataContainer/Data_abilityFeedBackInfo.h"

// Abilities
#include "abilities/GeneralAbilityClass.h"
#include "abilities/Ability_Teleport.h"
// meshes
#include "meshes/Weapon_Pistol.h"
#include "meshes/Weapon_Shotgun.h"
#include "meshes/Weapon_SniperRifle.h"
#include "meshes/Weapon_Blade.h"
#include "meshes/Weapon_BlackHoleBomb.h"
#include "meshes/Weapon_ReverseProjectile.h"
#include "meshes/Weapon_TeleportMark.h"
#include "meshes/Weapon_MomFoot.h"

// Animation
#include "Animation/AnimInstance.h"
// Timer managment
#include "TimerManager.h"

//Projectile function like AddForce()
#include "GameFramework/ProjectileMovementComponent.h"

// UI/ Widget
#include "Blueprint/UserWidget.h"
#include "WidgetsBase/PlayerStatsUMG.h"

AMain::AMain() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// First Person CameraComponent	
	FirstPersonCamaraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamara"));
	FirstPersonCamaraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamaraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Position the camera
	FirstPersonCamaraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	FirstPersonCamaraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	BodyComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	BodyComponent->SetOnlyOwnerSee(false);
	BodyComponent->SetupAttachment(FirstPersonCamaraComponent);
	BodyComponent->bCastDynamicShadow = false;
	BodyComponent->CastShadow = false;
	BodyComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	BodyComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	// Ability system
	// AbilitySystem = CreateDefaultSubobject<AbilitySystemClass>(TEXT("MainAbilitySystem"));

	// Use a sphere to detect enemies/ projectile...etc
	DetectionArea = CreateDefaultSubobject<USphereComponent>(TEXT("Detection Area"));
	DetectionArea->SetupAttachment(GetMesh());

	// UI
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;

	// Initialized basic Components
	Frenzy = CreateDefaultSubobject<UFrenzyComponent>(TEXT("Frenzy"));
	Calm = CreateDefaultSubobject<UCalmComponent>(TEXT("Calm"));
	
	AbilityRequiredContainer = CreateDefaultSubobject<UData_AbilityRequiredInfo>(TEXT("Required Info"));
	FeedBackContainer = CreateDefaultSubobject<UData_AbilityFeedBackInfo>(TEXT("FeedBack Info"));
	
	Left_Hand_Position = FVector(0.0f, 0.0f, 0.0f);
	Right_Hand_Position = FVector(0.0f, 0.0f, 0.0f);

	Weapon_Pistol = nullptr;
	Weapon_Shotgun = nullptr;
	Weapon_SniperRifle = nullptr;
	Weapon_Blade = nullptr;
	Weapon_BlackHoleBomb = nullptr;

	// anim montage
	PistolFire_Montage = nullptr;
	ShotgunFire_Montage = nullptr;
	SniperRifleFire_Montage = nullptr;
	SwordAttack_Montage = nullptr;
	GetAttacked_Montage = nullptr;

	// weapon / body control
	WeaponRotation = FRotator(0.0f, 0.0f, 0.0f);

	Left_Hand_Position = FVector(0.0f, 0.0f, 0.0f);
	Right_Hand_Position = FVector(0.0f, 0.0f, 0.0f);
	Weapon_Left_Hand_Position = FVector(0.0f, 0.0f, 0.0f);
	Weapon_Right_Hand_Position = FVector(0.0f, 0.0f, 0.0f);
	Weapon_Fire_Point_Position = FVector(0.0f, 0.0f, 0.0f);

	CurrentAbilityInHand = EAbilityCode::ETest;
}

// Called when the game starts or when spawned
void AMain::BeginPlay() {
	Super::BeginPlay();

	// Spawn ability system
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (IsValid(AbilitySystemClass)) {

		AbilitySystem = NewObject<AAbilitySystem>(this, AbilitySystemClass);
		AbilitySystem->SetPlayer(this);
		AbilitySystem->SetWorld(GetWorld());
	}
	
	// Inicialize all stats
	Frenzy->SetFrenzy(0.0f);
	Calm->SetCalm(0.0f);

	SetDashDistance(2000);

	SetIsRunning(false);
	SetIsCrouching(false);
	SetIsSliding(false);
	SetAbleToSlide(true);
	SetIsDashing(false);

	IsDoingAnAnimation = false;

	SetDefaultAbilityChosen(EAbilityCode::ENone);
	SetCurrentAbilityInHand(EAbilityCode::ENone);
	SetLastAbilityUsed(EAbilityCode::ENone);

	AbilitiesChangeInput = { EAbilityCode::EBlackHoleBomb };

	// Test -> grand self ability
	ProcessGameInstance();

	DefaultDetectionAreaRadius = DetectionArea->GetScaledSphereRadius();
	NewDetectionAreaRadius = 0.0f;

	// Start Calm Grow Timer
	PermaGrowCalm();

	// instanciate the UI Widget
	if (IsValid(PlayerHUDClass)) {
		APlayerController* controller = GetWorld()->GetFirstPlayerController();
		// APlayerController* Control = GetController();
		PlayerHUD = CreateWidget<UPlayerStatsUMG>(controller, PlayerHUDClass);
		PlayerHUD->AddToPlayerScreen();
	}
}

// Called every frame
void AMain::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Detect();

	UpdateDisplayMainVariables();

	// need to do it on tick function in order to let hands keep up with weapon location
	GetWeaponSocketsInfo();
}

// receive main abiltiies and set it
void AMain::ProcessGameInstance() {
	UTrueGame2Instance* TrueGameInstance = Cast<UTrueGame2Instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(TrueGameInstance)) {
		// Set Main Abilities
		
		SetAbility(0, TrueGameInstance->GetMainWeapon());
		SetAbility(1, TrueGameInstance->GetMainAbilityOne());
		SetAbility(2, TrueGameInstance->GetMainAbilityTwo());
		SetAbility(3, TrueGameInstance->GetMainAbilityThree());
		SetAbility(4, TrueGameInstance->GetMainAbilityFour());
	}
}

// Updates of post game stats
void AMain::UpdateTotalDamage(float damage) {
	TotalDamage += damage;
}
void AMain::UpdateTotalEnemiesKilled() {
	TotalEnemiesKilled ++;
}
void AMain::UpdateTotalDamageTaken(float damageTaken) {
	TotalDamageTaken += damageTaken;
}
	// Getters
int AMain::GetTotalDamageDealed() {
	return FMath::RoundToInt(TotalDamage);
}
int AMain::GetTotalDamageTaken() {
	return FMath::RoundToInt(TotalDamageTaken);
}
int AMain::GetTotalEnemiesKilled() {
	return TotalEnemiesKilled;
}
int AMain::GetTotalXP() {
	return FMath::RoundToInt(XPComponent->GetXP());
}
int AMain::GetAmountArtifact() {
	return AllArtifactList.Num();
}

/*Fail Ending*/
void AMain::GameOverPlayerDied() {
	ATrueProject2GameModeBase* TrueGameMode = Cast<ATrueProject2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (IsValid(TrueGameMode)) {
		TrueGameMode->SetGameOver(EGameOverReason::EFailMission);
	}
}

/*True Ending*/
void AMain::CheckTruePowerWin() {
	if (AllArtifactList.Num() >= ArtifactAmountRequired) {
		GameOverTruePower();
	}
}

void AMain::GameOverTruePower() {
	ATrueProject2GameModeBase* TrueGameMode = Cast<ATrueProject2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (IsValid(TrueGameMode)) {
		TrueGameMode->SetGameOver(EGameOverReason::ETrueEnding);
	}
}

/*Time Freezed Ending*/
void AMain::GameOverTimeFreezed() {
	ATrueProject2GameModeBase* TrueGameMode = Cast<ATrueProject2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (IsValid(TrueGameMode)) {
		TrueGameMode->SetGameOver(EGameOverReason::ETimeFreezed);
	}
}

/*Step Void Ending*/
void AMain::GameOverStepedVoid() {
	ATrueProject2GameModeBase* TrueGameMode = Cast<ATrueProject2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (IsValid(TrueGameMode)) {
		TrueGameMode->SetGameOver(EGameOverReason::EEmbraceVoid);
	}
}

float AMain::GetMainHalfHeight() {
	return GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 2;
}

void AMain::SetNewDetectionAreaRadius(float NewScale) {
	// Calculate the new radius after scaling
	NewDetectionAreaRadius = DefaultDetectionAreaRadius * NewScale/10.0f;
	bDetection = true;

	// Set the new radius to the sphere component
	if (IsValid(DetectionArea)) {
		DetectionArea->SetSphereRadius(NewDetectionAreaRadius);
	}
}
bool AMain::isMainDetecting() {
	return bDetection;
}
float AMain::GetNewDetectionAreaRadius() {
	return NewDetectionAreaRadius;
}
void AMain::ResetDetectionAreaRadius() {
	bDetection = false;
	if (IsValid(DetectionArea)) {
		DetectionArea->SetSphereRadius(DefaultDetectionAreaRadius);
	}
}
TArray<AActor*> AMain::GetAllDetectedActors() {
	TArray<AActor*> ActorsDetected = {};
	if (IsValid(DetectionArea)) {
		DetectionArea->GetOverlappingActors(ActorsDetected, AActor::StaticClass());
	}
	
	return ActorsDetected;
}

// Main UI
UPlayerStatsUMG* AMain::GetPlayerUIWidget() {
	return PlayerHUD;
}

void AMain::UpdateDisplayMainVariables() {
	if (IsValid(PlayerHUD)) {
		PlayerHUD->SetHealth(GiveHealthPercentage());
		PlayerHUD->SetFrenzy(GiveFrenzyPercentage());
		PlayerHUD->SetCalm(GiveCalmPercentage());

		PlayerHUD->SetLevelNumber(GiveLevelText());
		PlayerHUD->SetLevelPercentage(GiveXPPercentage());
	}
}

// Controller
void AMain::InitializeMainController() {
	MainController = Cast<AMainController>(GetController());
}

AMainController* AMain::GetMainController() {
	return MainController;
}

// Stats Control
void AMain::PermaGrowCalm() {
	if (IsValid(Calm)) {
		Calm->UpdateCalm(CalmGrowRate);

		GetWorldTimerManager().SetTimer(CalmGrownTimer, this,
			&AMain::PermaGrowCalm, CalmGrownCooldown, true);
	}
}
void AMain::UpdateCalmGrowRate(float modifier) {
	CalmGrowRate = CalmGrowRate + CalmGrowRate * modifier;
}
void AMain::SpendAllCalm() {
	// need to have a bool which check the next attack -> after next attack, turn the calm false
	float DeltaCalmAcumulated = Calm->UseAllCalm();
	CalmToPowerConverter(DeltaCalmAcumulated);
}

// The standard is 1, per each 1 calm -> add 1 % of damage. When 100% -> deal double damage
void AMain::CalmToPowerConverter(float calmAmount) {
	CalmPowerMultiplier = BaseCalmPower + calmAmount / 100;
}

/*A check for, after the last hit of player, the calm dessapear
PROBLEM ARISE -> ABILITIES WITH NO DAMAGE -> ABILITY FAIL TO USE...
*/
// SHOULD BE PROCESS BY PROCESS FEEDBACK
void AMain::ResetCalmMultiplier()
{
	CalmPowerMultiplier = BaseCalmPower;
}


void AMain::GetWeaponSocketsInfo() {
	switch (CurrentAbilityInHand) {
		case EAbilityCode::EPistol: {
			Front_Position = this->GetMesh()->GetSocketLocation(Front_Socket);
			Right_Hand_Position = this->GetMesh()->GetSocketLocation(Right_Hand_Socket);

			// two hand weapon rotation
			FVector WeaponDirection = Front_Position - Right_Hand_Position;
			WeaponRotation = WeaponDirection.Rotation();

			// weapon control for 2k bone IK
			if (Weapon_Pistol)
			{
				Weapon_Pistol->SetActorRotation(WeaponRotation, ETeleportType::None);

				Weapon_Left_Hand_Position = Weapon_Pistol->GetMesh()->GetSocketLocation(Weapon_Left_Hand_Socket);
				Weapon_Right_Hand_Position = Weapon_Pistol->GetMesh()->GetSocketLocation(Weapon_Right_Hand_Socket);
				Weapon_Fire_Point_Position = Weapon_Pistol->GetMesh()->GetSocketLocation(Weapon_Fire_Point_Socket);
			}
			
			break;
		}
		case EAbilityCode::EShotgun: {
			// left right hand position in world space
			Left_Hand_Position = this->GetMesh()->GetSocketLocation(Left_Hand_Socket);
			Right_Hand_Position = this->GetMesh()->GetSocketLocation(Right_Hand_Socket);

			// two hand weapon rotation
			FVector WeaponDirection = Left_Hand_Position - Right_Hand_Position;
			WeaponRotation = WeaponDirection.Rotation();

			Weapon_Shotgun->SetActorRotation(WeaponRotation, ETeleportType::None);

			// weapon control for 2k bone IK
			Weapon_Left_Hand_Position = Weapon_Shotgun->GetMesh()->GetSocketLocation(Weapon_Left_Hand_Socket);
			Weapon_Right_Hand_Position = Weapon_Shotgun->GetMesh()->GetSocketLocation(Weapon_Right_Hand_Socket);
			Weapon_Fire_Point_Position = Weapon_Shotgun->GetMesh()->GetSocketLocation(Weapon_Fire_Point_Socket);
			
			break;
		}
		case EAbilityCode::ESniper: {
			// left right hand position in world space
			Left_Hand_Position = this->GetMesh()->GetSocketLocation(Left_Hand_Socket);
			Right_Hand_Position = this->GetMesh()->GetSocketLocation(Right_Hand_Socket);

			// two hand weapon rotation
			FVector WeaponDirection = Left_Hand_Position - Right_Hand_Position;
			WeaponRotation = WeaponDirection.Rotation();

			Weapon_SniperRifle->SetActorRotation(WeaponRotation, ETeleportType::None);

			// weapon control for 2k bone IK
			Weapon_Left_Hand_Position = Weapon_SniperRifle->GetMesh()->GetSocketLocation(Weapon_Left_Hand_Socket);
			Weapon_Right_Hand_Position = Weapon_SniperRifle->GetMesh()->GetSocketLocation(Weapon_Right_Hand_Socket);
			Weapon_Fire_Point_Position = Weapon_SniperRifle->GetMesh()->GetSocketLocation(Weapon_Fire_Point_Socket);
			
			break;
		}
		case EAbilityCode::EBlade: {
			// weapon control for 2k bone IK

			Weapon_Left_Hand_Position = Weapon_Blade->GetMesh()->GetSocketLocation(Weapon_Left_Hand_Socket);
			Weapon_Right_Hand_Position = Weapon_Blade->GetMesh()->GetSocketLocation(Weapon_Right_Hand_Socket);
			
			break;
		}
		case EAbilityCode::EBlackHoleBomb: {
			// Need to show in HUD the projectile/ destination of the bomb
			break;
		}
		default: {
			break;
		}
	}
}

// return Componenets values
float AMain::GiveFrenzyPercentage() {
	return Frenzy->GetFrenzyPercentage();
}
float AMain::GiveFrenzy() {
	return Frenzy->GetFrenzy();
}
float AMain::GiveMaxFrenzy() {
	return Frenzy->GetMaxFrenzy();
}

float AMain::GiveCalmPercentage() {
	return Calm->GetCalmPercentage();
}
float AMain::GiveCalm() {
	return Calm->GetCalm();
}
float AMain::GiveMaxCalm() {
	return Calm->GetMaxCalm();
}

// Receive damage
// TakeDamage only respond flat damage
float AMain::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	// question -> should main receive damage by everyone even herself ??? or only enemies.
	float DamageCaused = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	DamageCaused = ApplyAllDefenseArtifacts(DamageCaused, this);

	// store the total receive damage
	UpdateTotalDamageTaken(DamageCaused);

	DamageCaused = -DamageCaused;
	Health->UpdateHealthFloat(DamageCaused);

	if (Health->GetDied()) {
		if (ApplyAllDiedArtifacts(this)) {

			// set game over to gamemode
			GameOverPlayerDied();

			ResetCharacterStats();
			Destroy();

			// it is definitly died, no hope
			// should respawn and next run
			// TrueDied(); -> unimplemented
		}
		else { // still "incorrect", cuz the player did not "disappear" {
			// how to revive -> dk should be part of artifact.
		}
	}
	return DamageCaused;
}

// Animation and attachment for default and weapon selected
EAbilityCode AMain::GetDefaultAbilityChosen() {
	return DefaultAbilityChosen;
}
void AMain::SetDefaultAbilityChosen(EAbilityCode NewAbilityChosen) {
	DefaultAbilityChosen = NewAbilityChosen;
}

EAbilityCode AMain::GetCurrentAbilityInHand() {
	return CurrentAbilityInHand;
}
void AMain::SetCurrentAbilityInHand(EAbilityCode NewAbilityInHand) {
	CurrentAbilityInHand = NewAbilityInHand;
}

EAbilityCode AMain::GetLastAbilityUsed() {
	return LastAbilityUsed;
}
void AMain::SetLastAbilityUsed(EAbilityCode NewAbilityChosen) {
	LastAbilityUsed = NewAbilityChosen;
}


void AMain::AttachWeaponSelected(EAbilityCode AbilityCode) {
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	const FTransform orientation_socket_left = GetMesh()->GetSocketTransform(Left_Hand_Socket, ERelativeTransformSpace::RTS_World);
	const FTransform orientation_socket_right = GetMesh()->GetSocketTransform(Right_Hand_Socket, ERelativeTransformSpace::RTS_World);

	switch (AbilityCode) {
		case EAbilityCode::EPistol: {
			SetCurrentAbilityInHand(EAbilityCode::EPistol);
			Weapon_Pistol = GetWorld()->SpawnActor<AWeapon_Pistol>(PistolClass, orientation_socket_right, ActorSpawnParams);

			if (Weapon_Pistol != nullptr) {
				Weapon_Pistol->AttachToComponent(GetMesh(),
					FAttachmentTransformRules::SnapToTargetIncludingScale, Right_Hand_Socket);
			}

			break;
		}
		case EAbilityCode::EShotgun: {
			SetCurrentAbilityInHand(EAbilityCode::EShotgun);
			Weapon_Shotgun = GetWorld()->SpawnActor<AWeapon_Shotgun>(ShotgunClass, orientation_socket_right, ActorSpawnParams);
		
			if (Weapon_Shotgun != nullptr) {
				Weapon_Shotgun->AttachToComponent(GetMesh(), 
					FAttachmentTransformRules::SnapToTargetIncludingScale, Right_Hand_Socket);
			}
		
			break;
		}
		case EAbilityCode::ESniper: {
			SetCurrentAbilityInHand(EAbilityCode::ESniper);
			Weapon_SniperRifle = GetWorld()->SpawnActor<AWeapon_SniperRifle>(SniperRifleClass, orientation_socket_right, ActorSpawnParams);

			if (Weapon_SniperRifle != nullptr) {
				Weapon_SniperRifle->AttachToComponent(GetMesh(),
					FAttachmentTransformRules::SnapToTargetIncludingScale, Right_Hand_Socket);
			}

			break;
		}
		case EAbilityCode::EBlade: {
			SetCurrentAbilityInHand(EAbilityCode::EBlade);
			Weapon_Blade = GetWorld()->SpawnActor<AWeapon_Blade>(BladeClass, orientation_socket_right, ActorSpawnParams);

			if (Weapon_Blade != nullptr) {
				Weapon_Blade->AttachToComponent(GetMesh(),
					FAttachmentTransformRules::SnapToTargetIncludingScale, Right_Hand_Socket);
			}

			break;
		}
		case EAbilityCode::EBlackHoleBomb: {
			// BOMB 
			SetCurrentAbilityInHand(EAbilityCode::EBlackHoleBomb);

			// It does not spawn the bomb, it just set the current ability 
			// in order to let the get socket info to know
			break;
		}
		case EAbilityCode::EOpenCommand: {
			// Open Command
			SetCurrentAbilityInHand(EAbilityCode::EOpenCommand);
			// ADD LOGIC -> EXIT PLAYER CONTROL AND ABLE TO WRITE IN COMMAND
			break;
		}
		default:
			break;
	}
}

/*
Cuz the widget should only access character and no its ability system, so the widget is going
to send character function, ability system check if the ability exist or not, store in character
*/
void AMain::SetAbility(int slot, EAbilityCode abilityCode) {
	if (IsValid(AbilitySystem)) {
		if (AbilitySystem->CheckAbility(slot)) {
			// should change it, case 0 is weapons
			switch (slot) {
			case 0: {
				BasicAttackChosen = abilityCode;
				AttachWeaponSelected(BasicAttackChosen);

				SetDefaultAbilityChosen(abilityCode);
				SetCurrentAbilityInHand(abilityCode);

				break;
			}
			case 1: {
				AbilityOneChosen = abilityCode;
				break;
			}
			case 2: {
				AbilityTwoChosen = abilityCode;
				break;
			}
			case 3: {
				AbilityThreeChosen = abilityCode;
				break;
			}
			case 4: {
				AbilityFourChosen = abilityCode;
				break;
			}
			case 5: {
				PassiveChosen = abilityCode;
				break;
			}
			default:
				break;
			}
		}
	}
}

// Use Abilities, can not do polimorphism because is related to input
void AMain::UsePassive() {
	CreateRequirementContainer(PassiveChosen);
	FeedBackContainer = AbilitySystem->ActivateAbility(AbilityRequiredContainer);
	ProcessAbilityFeedBacks();
}

// MAY ADD LOGICS OF DEPEDING WEAPON IN HAND -> CHANGE INPUT
void AMain::UseBasicAttack() {
	// Run a weapon in hand check
	if (AbilitiesChangeInput.Contains(CurrentAbilityInHand)) {
		switch (CurrentAbilityInHand) {	
			case EAbilityCode::EBlackHoleBomb: {
				// Check Hit Result -> End or Hit
				if (Hit.IsValidBlockingHit()) {
					BombDestination = Hit.ImpactPoint;
				}
				else {
					BombDestination = ViewEnd;
				}
				CreateRequirementContainer(CurrentAbilityInHand);
				FeedBackContainer = AbilitySystem->ActivateAbility(AbilityRequiredContainer);
				ProcessAbilityFeedBacks();

				break;
			}
			default: {
				break;
			}
		}		
		// may add if statement for each different case
		CreateRequirementContainer(CurrentAbilityInHand);
		FeedBackContainer = AbilitySystem->ActivateAbility(AbilityRequiredContainer);
		ProcessAbilityFeedBacks();
	}
	else {
		CreateRequirementContainer(BasicAttackChosen);
		FeedBackContainer = AbilitySystem->ActivateAbility(AbilityRequiredContainer);
		ProcessAbilityFeedBacks();
	}
}

// disable all others inputs if the ability in hand is: bomb/ comand...etc
void AMain::UseAbilityOne() {
	if (AbilitiesChangeInput.Contains(AbilityOneChosen)) {
		// may add if statement for each different case
		// As this ability change input, attach it which automatically set CurrentInHand
		AttachWeaponSelected(AbilityOneChosen);
	}
	else {
		CreateRequirementContainer(AbilityOneChosen);
		FeedBackContainer = AbilitySystem->ActivateAbility(AbilityRequiredContainer);
		ProcessAbilityFeedBacks();
	}
}

void AMain::UseAbilityTwo() {
	if (AbilitiesChangeInput.Contains(AbilityTwoChosen)) {
		// may add if statement for each different case
		// As this ability change input, attach it which automatically set CurrentInHand
		AttachWeaponSelected(AbilityTwoChosen);
	}
	else {
		CreateRequirementContainer(AbilityTwoChosen);
		FeedBackContainer = AbilitySystem->ActivateAbility(AbilityRequiredContainer);
		ProcessAbilityFeedBacks();
	}
}

void AMain::UseAbilityThree() {
	if (AbilitiesChangeInput.Contains(AbilityThreeChosen)) {
		// may add if statement for each different case
		// As this ability change input, attach it which automatically set CurrentInHand
		AttachWeaponSelected(AbilityThreeChosen);
	}
	else {
		CreateRequirementContainer(AbilityThreeChosen);
		FeedBackContainer = AbilitySystem->ActivateAbility(AbilityRequiredContainer);
		ProcessAbilityFeedBacks();
	}
}

void AMain::UseAbilityFour() {
	if (AbilitiesChangeInput.Contains(AbilityFourChosen)) {
		// As this ability change input, attach it which automatically set CurrentInHand
		AttachWeaponSelected(AbilityFourChosen);
		// may add if statement for each different case
	}
	else {
		CreateRequirementContainer(AbilityFourChosen);
		FeedBackContainer = AbilitySystem->ActivateAbility(AbilityRequiredContainer);
		ProcessAbilityFeedBacks();
	}
	
}

// USE "MONTAGE PLAY" and no "PlayAnimMontage"
void AMain::PlayMontages(EAbilityCode abilityCode, float PlayRate) {
	SetLastAbilityUsed(abilityCode);

	switch (abilityCode) {
		case EAbilityCode::EPistol: {
			if (IsValid(PistolFire_Montage)) {
				PlaySelectedMontage(PistolFire_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EShotgun: {
			if (IsValid(ShotgunFire_Montage)) {
				PlaySelectedMontage(ShotgunFire_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::ESniper: {
			if (IsValid(SniperRifleFire_Montage)) {
				PlaySelectedMontage(SniperRifleFire_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EBlade: {
			if (IsValid(SwordAttack_Montage)) {
				PlaySelectedMontage(SwordAttack_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EBlackHoleBomb: {
			// TURN THE WEAPON IN HAND TO BOMB, AND IF THE ABILITY ACTIVATE ->
			// ANIMATION MONTAGE -> THROW IT 
			if (IsValid(ThrowBlackHoleBomb_Montage)) {
				PlaySelectedMontage(ThrowBlackHoleBomb_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EAlienGun: {
			if (IsValid(AlienGunFire_Montage)) {
				PlaySelectedMontage(AlienGunFire_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EBombBaiter: {
			if (IsValid(ThrowBaiterBomb_Montage)) {
				PlaySelectedMontage(ThrowBaiterBomb_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EWallBreaker: {
			if (IsValid(WallBreaker_Montage)) {
				PlaySelectedMontage(WallBreaker_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EWireTrap: {
			if (IsValid(PlaceWireTrap_Montage)) {
				PlaySelectedMontage(PlaceWireTrap_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EShadowSolder: {
			if (IsValid(InvokeShadowSolder_Montage)) {
				PlaySelectedMontage(InvokeShadowSolder_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EShadowTravel: {
			if (IsValid(ShadowTravel_Montage)) {
				PlaySelectedMontage(ShadowTravel_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EReverseProjectiles: {
			if (IsValid(ReverseProjectiles_Montage)) {
				PlaySelectedMontage(ReverseProjectiles_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::ETeleport: {
			// It should somehow detec if it is putting a mark or TP
			if (IsValid(Teleport_TP_Montage)) {
				PlaySelectedMontage(Teleport_TP_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::ESwitchDimention: {
			if (IsValid(SwitchDimention_Montage)) {
				PlaySelectedMontage(SwitchDimention_Montage, PlayRate);
			}
			break;
		}
		// It may no have animation montage
		case EAbilityCode::EBulletTime: {
			if (IsValid(StartBulletTime_Montage)) {
				PlaySelectedMontage(StartBulletTime_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EFForward: {
			if (IsValid(StartFForward_Montage)) {
				PlaySelectedMontage(StartFForward_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EParalysis: {
			if (IsValid(ParalysisEnemies_Montage)) {
				PlaySelectedMontage(ParalysisEnemies_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EOpenCommand: {
			if (IsValid(OpenCommand_Montage)) {
				PlaySelectedMontage(OpenCommand_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::ESumEagle: {
			if (IsValid(SumEagle_Montage)) {
				PlaySelectedMontage(SumEagle_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::ESumBigFoot: {
			if (IsValid(SumBigFoot_Montage)) {
				PlaySelectedMontage(SumBigFoot_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::ESumRabbit:{
			if (IsValid(SumRabbit_Montage)){
				PlaySelectedMontage(SumRabbit_Montage, PlayRate);
			}
			break;
		}
		case EAbilityCode::EItemBox:{
			if (IsValid(OpenItemBox_Montage)){
				PlaySelectedMontage(OpenItemBox_Montage, PlayRate);
			}
			break;
		}
		default:
			break;
	}
}

void AMain::PlaySelectedMontage(UAnimMontage* ChosenMontage, float PlayRate) {
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance) {
		if (IsValid(ChosenMontage)) {
			IsDoingAnAnimation = true;
			AnimInstance->Montage_Play(ChosenMontage, PlayRate);

			// Bind the OnMontageEnded event to a custom function
			AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &AMain::OnMontageEnded);
		}
	}
}


// USE the bInterrupted parameter
void AMain::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) {
	// when montage finished -> specially deal depending ability used
	if (LastAbilityUsed == EAbilityCode::EBlackHoleBomb) {
		// after throw the bomb, turn the ability default back
		SetCurrentAbilityInHand(GetDefaultAbilityChosen());
	}
	// turn to false on the end
	IsDoingAnAnimation = false;
}

bool AMain::IsPlayerInAnimation() {
	return IsDoingAnAnimation;
}

// complicate, may redo.
// AbilityCode is part of allcharacter and no main -> need for ability system
void AMain::CreateRequirementContainer(EAbilityCode abilityCode) {	
	UWorld* const World = GetWorld();
	AbilityRequiredContainer->InitializedAllAbilityInfo(World, abilityCode,
		Frenzy->GetFrenzy(), Calm->GetCalm(),
		GetPlayerPosition(), GetPlayerRotation(),
		Hit, this, AbilitySystem);

}

// may add a feed back duration
void AMain::ProcessAbilityFeedBacks() {
	if (IsValid(FeedBackContainer)) {
		if (FeedBackContainer->GetExistance()) {
			// spend the frenzy cost and get the frenzy reward
			if (IsValid(Frenzy)) {
				Frenzy->UpdateFrenzy(FeedBackContainer->GetFrenzyCost());
				Frenzy->UpdateFrenzy(FeedBackContainer->GetFrenzyReward());
			}
			
			// update movement speed -> this need a cooldown, can not add speed infinitive
			ReceiveSpeedBoost(FeedBackContainer->GetMoveSpeedReward(), 5.0f);

			// XP reward
			UpdateXP(FeedBackContainer->GetXPReward());

			// Calm Multiplier Reset
			ResetCalmMultiplier();
		}
	}
}

void AMain::ProcessKillFeedBacks(UData_KillFeedBackInfo* KillFeedBack) {

	UpdateTotalEnemiesKilled();
	if (IsValid(KillFeedBack)) {
		// frenzy, calm, speed, xp
		if (IsValid(Frenzy) && IsValid(Calm)) {
			Frenzy->UpdateFrenzy(KillFeedBack->GetFrenzyReward());
			Calm->UpdateCalm(KillFeedBack->GetCalmReward());
		}

		ReceiveSpeedBoost(KillFeedBack->GetMoveSpeedReward(), 5.0f);
		// need to put XP logic ->restructure
		UpdateXP(KillFeedBack->GetXPReward());
	}
}

void AMain::ChangeMainFrenzy(float modifier) {
	if (IsValid(Frenzy)) {
		Frenzy->UpdateFrenzy(modifier);
	}
}
void AMain::ChangeMainCalm(float modifier) {
	if (IsValid(Calm)) {
		Calm->UpdateCalm(modifier);
	}
}

// Get/Add artifact
void AMain::GetArtifact(AActor* AArtifact) {
	if (IsValid(AArtifact)) {
		if (AArtifact->GetClass()->IsChildOf(AGeneralArtifact::StaticClass())) {
			AGeneralArtifact* GeneralArtifact = Cast<AGeneralArtifact>(AArtifact);
			if (IsValid(GeneralArtifact)) {
				AllArtifactList.Add(GeneralArtifact);

				CheckTruePowerWin();
			}

			if (AArtifact->GetClass()->IsChildOf(AGeneralPickUpArtifact::StaticClass())) {
				AGeneralPickUpArtifact* APickUpArtifact = Cast<AGeneralPickUpArtifact>(AArtifact);
				if (IsValid(APickUpArtifact)) {
					AllPickUpArtifactList.Add(APickUpArtifact);
					// try to apply the PickUp effect now
					APickUpArtifact->ApplyPickUpEffect(this);
				}
			}
			else if (AArtifact->GetClass()->IsChildOf(AGeneralAttackArtifact::StaticClass())) {
				AGeneralAttackArtifact* AAttackArtifact = Cast<AGeneralAttackArtifact>(AArtifact);
				if (IsValid(AAttackArtifact)) {
					AllAttackArtifactList.Add(AAttackArtifact);
				}
			}
			else if (AArtifact->GetClass()->IsChildOf(AGeneralDefenseArtifact::StaticClass())) {
				AGeneralDefenseArtifact* ADefenseArtifact = Cast<AGeneralDefenseArtifact>(AArtifact);
				if (IsValid(ADefenseArtifact)) {
					AllDefenseArtifactList.Add(ADefenseArtifact);
				}
			}
			else if (AArtifact->GetClass()->IsChildOf(AGeneralCostArtifact::StaticClass())) {
				AGeneralCostArtifact* ACostArtifact = Cast<AGeneralCostArtifact>(AArtifact);
				if (IsValid(ACostArtifact)) {
					AllAbilityCostArtifactList.Add(ACostArtifact);
				}
			}
			else if (AArtifact->GetClass()->IsChildOf(AGeneralDiedArtifact::StaticClass())) {
				AGeneralDiedArtifact* ADiedArtifact = Cast<AGeneralDiedArtifact>(AArtifact);
				if (IsValid(ADiedArtifact)) {
					AllDiedArtifactList.Add(ADiedArtifact);
				}
			}
			else if (AArtifact->GetClass()->IsChildOf(AGeneralKillFeedBackArtifact::StaticClass())) {
				AGeneralKillFeedBackArtifact* AKillFBArtifact = Cast<AGeneralKillFeedBackArtifact>(AArtifact);
				if (IsValid(AKillFBArtifact)) {
					AllKillFeedBackArtifactList.Add(AKillFBArtifact);
				}
			}
		}
	}
	
}

// apply/ eliminate all artifact by type at once
void AMain::EliminateAllPickUpArtifactsEffect(AMain* PlayerMain) {
	if (IsValid(PlayerMain)) {
		for (AGeneralPickUpArtifact* PickUpArtifactDelta : AllPickUpArtifactList) {
			if (IsValid(PickUpArtifactDelta)) {
				PickUpArtifactDelta->EliminatePickUpEffect(PlayerMain);
				AllPickUpArtifactList.Remove(PickUpArtifactDelta); // may cause error
			}
		}
	}
}

float AMain::ApplyAllAttackArtifacts(float alphaDamage, FHitResult EnemyHit, AMain* PlayerMain) {
	if (IsValid(PlayerMain)) {
		for (AGeneralAttackArtifact* AttackArtifactDelta : AllAttackArtifactList) {
			if (IsValid(AttackArtifactDelta)) {
				alphaDamage = AttackArtifactDelta->ApplyAttackEffect(alphaDamage, EnemyHit, PlayerMain);
			}
		}
	}
	return alphaDamage;
}

float AMain::ApplyAllDefenseArtifacts(float alphaDamage, AMain* PlayerMain) {
	if (IsValid(PlayerMain)) {
		for (AGeneralDefenseArtifact* DefenseArtifactDelta : AllDefenseArtifactList) {
			if (IsValid(DefenseArtifactDelta)) {
				alphaDamage = DefenseArtifactDelta->ApplyDefenseEffect(alphaDamage, PlayerMain);
			}
		}
	}
	return alphaDamage;
}

float AMain::ApplyAllFrenzyCostArtifacts(float frenzyCost, AMain* PlayerMain) {
	if (IsValid(PlayerMain)) {
		for (AGeneralCostArtifact* CostArtifactDelta : AllAbilityCostArtifactList) {
			if (IsValid(CostArtifactDelta)) {
				frenzyCost = CostArtifactDelta->ApplyFrenzyCostEffect(frenzyCost, PlayerMain);
			}
		}
	}
	
	return frenzyCost;
}

float AMain::ApplyAllCalmCostArtifacts(float CalmCost, AMain* PlayerMain) {
	if (IsValid(PlayerMain)) {
		for (AGeneralCostArtifact* CostArtifactDelta : AllAbilityCostArtifactList) {
			if (IsValid(CostArtifactDelta)) {
				CalmCost = CostArtifactDelta->ApplyCalmCostEffect(CalmCost, PlayerMain);
			}
		}
	}
	
	return CalmCost;
}

// definitly died
bool AMain::ApplyAllDiedArtifacts(AMain* PlayerMain) {
	bool deltaDied = true;
	
	if (IsValid(PlayerMain)) {
		for (AGeneralDiedArtifact* DieArtifactDelta : AllDiedArtifactList) {
			if (IsValid(DieArtifactDelta)) {
				deltaDied = deltaDied && DieArtifactDelta->ApplyDiedEffect(PlayerMain);
			}
		}
	}
	
	return deltaDied;
}

UData_KillFeedBackInfo* AMain::ApplyAllKillerFeedBackArtifacts(UData_KillFeedBackInfo* KillInfo, AActor* Enemy) {
	// auto& Elem : ArtifactList
	if (IsValid(KillInfo) && IsValid(Enemy)) {
		for (AGeneralKillFeedBackArtifact* KillFBArtifactDelta : AllKillFeedBackArtifactList) {
			if (IsValid(KillFBArtifactDelta))
			{
				KillInfo = KillFBArtifactDelta->ApplyKillFeedBackEffect(KillInfo, Enemy);
			}
		}
	}
	
	return KillInfo;
}

// Reset Everything of Main
void AMain::ResetCharacterStats() {
	BodyComponent = nullptr;
	DetectionArea = nullptr;
	MainController = nullptr;
	Frenzy = nullptr;
	Calm = nullptr;
	AbilitySystem = nullptr;
	AbilityRequiredContainer = nullptr;
	FeedBackContainer = nullptr;
	PistolClass = nullptr;
	if (IsValid(Weapon_Pistol)){
		Weapon_Pistol->Destroy();
		Weapon_Pistol = nullptr;
	}
	ShotgunClass = nullptr;

	if (IsValid(Weapon_Shotgun)){
		Weapon_Shotgun->Destroy();
		Weapon_Shotgun = nullptr;
	}
	SniperRifleClass = nullptr;

	if (IsValid(Weapon_SniperRifle)){
		Weapon_SniperRifle->Destroy();
		Weapon_SniperRifle = nullptr;
	}
	BladeClass = nullptr;
	if (IsValid(Weapon_Blade)) {
		Weapon_Blade->Destroy();
		Weapon_Blade = nullptr;
	}

	BlackHoleBombClass = nullptr;
	if (IsValid(Weapon_BlackHoleBomb)) {
		Weapon_BlackHoleBomb->Destroy();
		Weapon_BlackHoleBomb = nullptr;
	}
	AWeapon_ReverseProjectile_Class = nullptr;
	AWeapon_TeleportMark_Class = nullptr;

	// To add
}


// Functions for Abilities Customization
// General
FTransform AMain::GetMainRightHandTrans() {
	return this->GetMesh()->GetSocketTransform(Right_Hand_Socket);
}
FTransform AMain::GetMainLeftHandTrans() {
	return this->GetMesh()->GetSocketTransform(Left_Hand_Socket);
}
FTransform AMain::GetMainLeftHandThrowTrans() {
	return this->GetMesh()->GetSocketTransform(Left_Hand_Socket_Throw);
}

// FURTHER ABILITIES
// Ability Bomb
// should be call in animation blueprint

void AMain::SpawnAndAttachBHBomb() {
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform Left_Hand_Trans = GetMainLeftHandTrans();

	Weapon_BlackHoleBomb = GetWorld()->SpawnActor<AWeapon_BlackHoleBomb>(BlackHoleBombClass, Left_Hand_Trans, ActorSpawnParams);

	if (Weapon_BlackHoleBomb != nullptr) {
		Weapon_BlackHoleBomb->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale, Left_Hand_Socket);
	}
}

void AMain::ReleaseBHBomb() {
	if (Weapon_BlackHoleBomb != nullptr) {
		FVector StartPoint = Weapon_BlackHoleBomb->GetActorLocation();

		FVector Direction = (BombDestination - StartPoint).GetSafeNormal();
		float Distance = FVector::Dist(StartPoint, BombDestination);
		// Assuming you want to apply the force in the Z direction (upward)
		FVector Force = Direction * (Distance * ThrowForceMultiplier) + FVector(0.f, 0.f, ThrowForceVertical);

		Weapon_BlackHoleBomb->SetTargetLocation(BombDestination);
		Weapon_BlackHoleBomb->SetMainController(MainController);
		Weapon_BlackHoleBomb->SetDamage(10.0f);
		Weapon_BlackHoleBomb->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon_BlackHoleBomb->SetbGravityFire(3000.0f, true);

		//BombReleaseForce(Force);
	}
}

// Ability Reverse Projectiles
TSubclassOf<class AWeapon_ReverseProjectile> AMain::GetReverseProjectilesClass() {
	return AWeapon_ReverseProjectile_Class;
}

// Ability TP Mark
TSubclassOf<class AWeapon_TeleportMark> AMain::GetTPMarkClass() {
	return AWeapon_TeleportMark_Class;
}

// Ability Mom foot
TSubclassOf<class AWeapon_MomFoot> AMain::GetMomFootClass() {
	return AWeapon_MomFoot_Class;
}

// Ability BulletTime
void AMain::SetIsBulletTimeNiagaraSpawned(bool SpawnState) {
	bBulletTimeNiagaraSpawned = SpawnState;
}

bool AMain::GetIsBulletTimeNiagaraSpawned() {
	return bBulletTimeNiagaraSpawned;
}

// Ability FForward
void AMain::SetIsFForwardNiagaraSpawned(bool SpawnState) {
	bFForwardNiagaraSpawned = SpawnState;
}

bool AMain::GetIsFForwardNiagaraSpawned() {
	return bFForwardNiagaraSpawned;
}

// Time Dilation
void AMain::CustomRunResetDilationTimer(float segs) {
	GetWorld()->GetTimerManager().SetTimer(ResetTimeDilationTimer, this,
		&AMain::ResetTimeDilation, segs, true);
}

void AMain::ResetTimeDilation() {
	if (IsValid(GetWorld())) {
		GetWorld()->GetWorldSettings()->SetTimeDilation(1.0f);

		CustomTimeDilation = 1.0f;
		FForwardDilation = 1.0f;

		// if the bullet time niagara is spawned
		if (GetIsBulletTimeNiagaraSpawned()) {
			DestroyBulletTimeNiagara();
			SetIsBulletTimeNiagaraSpawned(false);
		}
		if (GetIsFForwardNiagaraSpawned()) {
			DestroyFForwardNiagara();
			SetIsFForwardNiagaraSpawned(false);
		}
	}
}

void AMain::SetFForwardDilation(float newvalue) {
	FForwardDilation = newvalue;
}
float AMain::GetFForwardDilation() {
	return FForwardDilation;
}
