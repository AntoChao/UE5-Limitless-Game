// Fill out your copyright notice in the Description page of Project Settings.

// normal character headers
#include "EnemyClass.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Enemies_Controller/AIEnemyClassController.h"

// perception headers
#include "GameFramework/Controller.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"

// navigation
#include "NavigationSystem.h"

// kill reward container
#include "../DataContainer/data_killfeedbackinfo.h"

// headers to recognize
#include "../Main.h"
#include "../MiniWorld.h"
#include "../components/HealthComponent.h"


// Sets default values
AEnemyClass::AEnemyClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->SetupAttachment(GetCapsuleComponent());
	// RootComponent = CollisionComp;

	// overlap event
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyClass::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AEnemyClass::OnOverlapEnd);

	//Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyBody"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	HealthBarRoot = CreateDefaultSubobject<USceneComponent>(TEXT("HealthBarRoot"));
	HealthBarRoot->SetupAttachment(GetCapsuleComponent());
	SetHealthBarNotVisible();

	setup_stimulus();
	KillReward = nullptr;

}

void AEnemyClass::BeginPlay()
{
	Super::BeginPlay();
	
	MainPlayerTarget = Cast<AMain>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	InitCharacHealth(1.0f);

	SpawnAttachHealthBar();
	SetRarity(EEnemyRarity::EUnknown);
	
	KillReward = NewObject<UData_KillFeedBackInfo>();
	// bool exist, float freGain, float calGain, float moveSpeed, int XP
	KillReward->InitializedAllKillFeedBacks(true, 0.0f, 0.0f, 1.0f, 0);

	if (IsValid(AMiniWorld::StaticClass()) && IsValid(AMiniWorldArtifact) && IsValid(this))
	{
		ArtifactLoot = NewObject<AMiniWorld>(this, AMiniWorld::StaticClass(),
			NAME_None, RF_NoFlags, AMiniWorldArtifact->GetDefaultObject(), true);
	}

	EnemyController = Cast<AAIEnemyClassController>(GetController());
	
	// Base Damage
	EnemyBaseDamage = 10.0f;
	// for random location
	GeneralDistance = 100.0f;

	IsAttacking = false;
	BasicAttackDuration = 3.0f;

	// Abilities
	IsUsingAbility1 = false;
	IsUsingAbility2 = false;
	IsUsingAbility3 = false;
	AbilityOneDistance = 100.0f;
	AbilityTwoDistance = 100.0f;
	AbilityThreeDistance = 100.0f;
	Ability1Duration = 1.0f;
	Ability2Duration = 1.0f;
	Ability3Duration = 1.0f;

	PlayRate = 1.0f;

	MinHeight = 0.0f;
	MaxHeight = 0.0f;

	SetHeightLimit();
	CalculateMinimalDistance();
	SetEnemyDefaultSpeed();

	CustomTickFunction();
}

// Called every frame

void AEnemyClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Health Bar
void AEnemyClass::SpawnAttachHealthBar()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform HealthBarTrans = HealthBarRoot->GetComponentTransform();

	HealthBar = GetWorld()->SpawnActor<AHealthBarActor>(HealthBarActorClass,
		HealthBarTrans, ActorSpawnParams);

	if (HealthBar != nullptr)
	{
		HealthBar->AttachToComponent(HealthBarRoot,
			FAttachmentTransformRules::SnapToTargetIncludingScale);

		UpdateHealthBarDisplay();
	}
}

void AEnemyClass::UpdateHealthBarDisplay()
{
	if (IsValid(HealthBar))
	{
		HealthBar->SetProgressPercentage(GiveHealthPercentage());
		SetHealthBarVisible();
	}
}

// Health Bar Visibility
void AEnemyClass::SetHealthBarVisible()
{
	if (IsValid(HealthBar))
	{
		HealthBar->SetProgressBarVisibility(true);
		GetWorldTimerManager().SetTimer(HealthBarVisibleTimer, this,
			&AEnemyClass::SetHealthBarNotVisible, HealthBarVisibleDuration, true);
	}
}

void AEnemyClass::SetHealthBarNotVisible()
{
	if (IsValid(HealthBar))
	{
		HealthBar->SetProgressBarVisibility(false);
	}
}

void AEnemyClass::RemoveHealthBar()
{
	if (IsValid(HealthBar))
	{
		HealthBar->Destroy();
		HealthBar = NULL;
		HealthBarRoot = NULL;
	}
}

void AEnemyClass::CustomTickFunction()
{
	Super::CustomTickFunction();
	UpdatePositions();
}

void AEnemyClass::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}

void AEnemyClass::SetRarity(EEnemyRarity ARarity)
{
	ItsRarity = ARarity;
}
EEnemyRarity AEnemyClass::GetRarity()
{
	return ItsRarity;
}

void AEnemyClass::SetHeightLimit()
{
	LimitHeight = FMath::RandRange(MinHeight, MaxHeight);
}

void AEnemyClass::SetEnemyDefaultSpeed()
{
	DefaultMoveSpeed = EnemyMovementSpeed;
	ChangeCurrentMoveSpeed();
}

// Behavior tree 
// General distance is for calculate the random location
float AEnemyClass::GetGeneralDistance()
{
	return GeneralDistance;
}

void AEnemyClass::CalculateMinimalDistance()
{
	TArray<float> Distances = { BasicAttackDistance, AbilityOneDistance, 
							   AbilityTwoDistance, AbilityThreeDistance };

	MinimalDistance = Distances[0];
	for (int i = 1; i < AmountOfPerformance; ++i)
	{
		if (Distances[i] < MinimalDistance)
		{
			MinimalDistance = Distances[i];
		}
	}
}

// parent (Standard) -> get pre attack position based on action performing
FVector AEnemyClass::GetPreAttackPosition()
{
	// if the enemy is tooo close -> not even run closer, should run far away
	/*
	if (AttackDirection.Size() < MinimalDistance)
	{
		return GetPostAttackReposition();
	}
	else*/ {}

	if (PerformBasicAttack)
	{
		return GetRandLocation(SelfPosition, MainPosition, BasicAttackDistance);
	}
	else if (PerformAbilityOne)
	{
		return GetRandLocation(SelfPosition, MainPosition, AbilityOneDistance);
	}
	else if (PerformAbilityTwo)
	{
		return GetRandLocation(SelfPosition, MainPosition, AbilityTwoDistance);
	}
	else if (PerformAbilityThree)
	{
		return GetRandLocation(SelfPosition, MainPosition, AbilityThreeDistance);
	}
	else
	{
		return MainPosition;
	}

}
FVector AEnemyClass::GetAttackFinishedPosition()
{
	return SelfPosition; /*Standard*/
}
FVector AEnemyClass::GetPostAttackReposition()
{
	return GetRetreatLocation(SelfPosition, MainPosition, GeneralDistance);
}

/* The Random Location Point Logic
	1: Get a mid point between player and enemy
	2: Get a valid random navigatable location from this point
	3: Validate the random point by comparing with the general distance */
FVector AEnemyClass::GetRandLocation(FVector InitLocation, FVector
	TargetLocation, float Distance)
{
	NavArea = FNavigationSystem::
		GetCurrent<UNavigationSystemV1>(MainPlayerTarget);

	int counter;

	if (NavArea)
	{
		GenerateRandomPoint(InitLocation, TargetLocation);
		
		for (counter = 0; counter < MaxRandomTryTimes; counter++)
		{
			if (RandomLocationValid(TargetLocation, Distance))
			{
				break;
			}
			GenerateRandomPoint(InitLocation, TargetLocation);
		}
	}
	
	if (counter >= MaxRandomTryTimes)
	{
		DrawDebugSphere
		(
			GetWorld(), RandomLocation, 10.0f, 10, FColor::Red, false, 10.0f, 2, 10.0f
		);
	}
	else
	{
		DrawDebugSphere
		(
			GetWorld(), RandomLocation, 10.0f, 10, FColor::Purple, false, 10.0f, 2, 10.0f
		);
	}
	
	return RandomLocation;
}

// void cuz the navarea directly set the value to RandomLocation
void AEnemyClass::GenerateRandomPoint(FVector InitLocation, FVector TargetLocation)
{
	FVector Direction = TargetLocation - InitLocation;
	FVector MidPoint = InitLocation + Direction * 0.5f;
	float MidPointRadiu = (Direction * 0.5f).Size();

	// set randomlocation to random value reachable fvector
	NavArea->K2_GetRandomReachablePointInRadius(GetWorld(),
		MidPoint, RandomLocation,
		MidPointRadiu);
}

/*  is valid the location is outside of general distance
	Cuz otherwise could happen range enemies walking into player face */
bool AEnemyClass::RandomLocationValid(FVector TargetLocation, float MaxDistance)
{
	FVector ObjectiveDirection = TargetLocation - RandomLocation;
	float Distance = ObjectiveDirection.Size();
	float MinDistance = MaxDistance - MaxDistance * 0.3f;

	return (Distance < MaxDistance) && (Distance > MinDistance);
}

FVector AEnemyClass::EnemyGetRandMainLocation()
{
	if (IsValid(MainPlayerTarget))
	{
		return GetRandLocation(SelfPosition, MainPosition, GeneralDistance);
	}
	else
	{
		return SelfPosition;
	}
}


FVector AEnemyClass::GetRetreatLocation(FVector InitPosition, FVector TargetLocation,
	float RetreatDistance)
{
	FVector ReverseDirection = (InitPosition - TargetLocation).GetSafeNormal();

	return ReverseDirection * RetreatDistance + InitPosition;
}
FVector AEnemyClass::GetOppositeLocation(FVector InitPosition, FVector TargetLocation,
	float OppositeDistance)
{
	FVector ObjectiveDirection = (TargetLocation - InitPosition).GetSafeNormal();

	return ObjectiveDirection * OppositeDistance + TargetLocation;
}

// Selection between basic, attack, ability 1 2 3.
// Worst implemented function
void AEnemyClass::TieBreakAction()
{
	
	PerformBasicAttack = false;
	PerformAbilityOne = false;
	PerformAbilityTwo = false;
	PerformAbilityThree = false;

	/* 2 -> Basic Attack + Ability 1
	*  3 -> + Ability 2
	*  4 -> + Ability 3
	*/

	int ActionChosen = FMath::RandRange(0, AmountOfPerformance - 1);
	/*
	FString Miau = FString::Printf(TEXT("%d"), ActionChosen);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Miau);
	*/
	if (ActionChosen == 0) /*Basic Attack + Ability 1*/
	{
		PerformBasicAttack = true;
	}
	else if (ActionChosen == 1)
	{
		PerformAbilityOne = true;
	}
	else if (ActionChosen == 2)
	{
		PerformAbilityTwo = true;
	}
	else if (ActionChosen == 3)
	{
		PerformAbilityThree = true;
	}
}

bool AEnemyClass::IsPerformingAction()
{
	return PerformBasicAttack || PerformAbilityOne || PerformAbilityTwo || PerformAbilityThree;
}
bool AEnemyClass::GetPerformBasicAttack()
{
	return PerformBasicAttack;
}
bool AEnemyClass::GetPerformAbilityOne()
{
	return PerformAbilityOne;
}
bool AEnemyClass::GetPerformAbilityTwo()
{
	return PerformAbilityTwo;
}
bool AEnemyClass::GetPerformAbilityThree()
{
	return PerformAbilityThree;
}

bool AEnemyClass::IsAbleToUseBasicAttack()
{
	return AttackDirection.Size() <= BasicAttackDistance;
}
bool AEnemyClass::IsAbleToUseAbility1()
{
	return AttackDirection.Size() <= AbilityOneDistance;
}
bool AEnemyClass::IsAbleToUseAbility2()
{
	return AttackDirection.Size() <= AbilityTwoDistance;
}
bool AEnemyClass::IsAbleToUseAbility3()
{
	return AttackDirection.Size() <= AbilityThreeDistance;
}

// Abilities
bool AEnemyClass::GetIsAttacking()
{
	return IsAttacking;
}
bool AEnemyClass::GetIsUsingAbility1()
{
	return IsUsingAbility1;
}

bool AEnemyClass::GetIsUsingAbility2()
{
	return IsUsingAbility2;
}

bool AEnemyClass::GetIsUsingAbility3()
{
	return IsUsingAbility3;
}

void AEnemyClass::PrepareBasicAttack()
{
	return;
}

// Basic Attack, there is no cooldown for basic attack
void AEnemyClass::BasicAttack()
{
	IsAttacking = true;
	PlayAnimBasicAttack();
}
void AEnemyClass::BasicAttackFinished()
{
	IsAttacking = false;
	PerformBasicAttack = false;
}


// Abilities do no automatically link to animation. should define on dif classes
// Ability 1
void AEnemyClass::PrepareAbility1()
{
	return;
}

void AEnemyClass::Ability1()
{
	IsUsingAbility1 = true;
	PlayAnimAbilityOne(); /*Play Animation by default*/
}

void AEnemyClass::Ability1Finished()
{
	IsUsingAbility1 = false;
	PerformAbilityOne = false;
}



// Ability 2
void AEnemyClass::PrepareAbility2()
{
	return;
}

void AEnemyClass::Ability2()
{
	IsUsingAbility2 = true;
	PlayAnimAbilityTwo(); /*Play Animation by default*/
}

void AEnemyClass::Ability2Finished()
{
	IsUsingAbility2 = false;
	PerformAbilityTwo = false;
}


// Ability 3
void AEnemyClass::PrepareAbility3()
{
	return;
}
void AEnemyClass::Ability3()
{
	IsUsingAbility3 = true;
	PlayAnimAbilityThree(); /*Play Animation by default*/
}

void AEnemyClass::Ability3Finished()
{
	IsUsingAbility3 = false;
	PerformAbilityThree = false;
}


void AEnemyClass::UpdatePositions()
{
	if (IsValid(MainPlayerTarget))
	{
		MainPosition = MainPlayerTarget->GetActorLocation();
		SelfPosition = GetActorLocation();
		AttackDirection = MainPosition - SelfPosition;
	}
}

// General Damage to overlap actors for basic attack
void AEnemyClass::DealDamage2Overlapped()
{
	CollisionComp->GetOverlappingActors(OverlappedActors, AActor::StaticClass());
	for (AActor* Actor : OverlappedActors)
	{
		if (IsValid(Actor))
		{
			UGameplayStatics::ApplyPointDamage(Actor, EnemyBaseDamage,
				GetActorLocation(), EnemyHit, EnemyController,
				this, nullptr);
		}
	}
}

FVector AEnemyClass::GetRandomNearbyLocationOfPlayer(float Distance)
{
	// Generate random angles for azimuth (in radians)
	float RandomAngle = FMath::RandRange(0.0f, 2 * PI);

	// Calculate the random offset vector based on the generated angle and Distance
	FVector RandomOffset = FVector(
		FMath::Cos(RandomAngle),
		FMath::Sin(RandomAngle),
		0.0f
	) * (FMath::RandRange(0.0f, Distance));


	return  MainPosition + RandomOffset;
}

void AEnemyClass::PlayAnimBasicAttack()
{
	UAnimInstance* AnimInstance = Body->GetAnimInstance();

	if (AnimInstance)
	{
		if (IsValid(AnimMontage_BasicAttack))
		{
			AnimInstance->Montage_Play(AnimMontage_BasicAttack, PlayRate);

			// Bind the OnMontageEnded event to a custom function
			AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemyClass::OnMontageBasicAttackEnded);
		}
	}
}

void AEnemyClass::PlayAnimAbilityOne()
{
	UAnimInstance* AnimInstance = Body->GetAnimInstance();

	if (AnimInstance)
	{
		if (IsValid(AnimMontage_Ability1))
		{
			AnimInstance->Montage_Play(AnimMontage_Ability1, PlayRate);

			// Bind the OnMontageEnded event to a custom function
			AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemyClass::OnMontageOneEnded);
		}
	}
}

void AEnemyClass::PlayAnimAbilityTwo()
{
	UAnimInstance* AnimInstance = Body->GetAnimInstance();

	if (AnimInstance)
	{
		if (IsValid(AnimMontage_Ability2))
		{
			AnimInstance->Montage_Play(AnimMontage_Ability2, PlayRate);

			// Bind the OnMontageEnded event to a custom function
			AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemyClass::OnMontageTwoEnded);
		}
	}
}

void AEnemyClass::PlayAnimAbilityThree()
{
	UAnimInstance* AnimInstance = Body->GetAnimInstance();

	if (AnimInstance)
	{
		if (IsValid(AnimMontage_Ability3))
		{
			AnimInstance->Montage_Play(AnimMontage_Ability3, PlayRate);

			// Bind the OnMontageEnded event to a custom function
			AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemyClass::OnMontageThreeEnded);
		}
	}
}

void AEnemyClass::OnMontageBasicAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	BasicAttackFinished();
}
void AEnemyClass::OnMontageOneEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Ability1Finished();
}
void AEnemyClass::OnMontageTwoEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Ability2Finished();
}
void AEnemyClass::OnMontageThreeEnded(UAnimMontage* Montage, bool bInterrupted)
{
	Ability3Finished();
}

// receive damage, but if it get kill, just leave the rewards
float AEnemyClass::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageCaused = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	DamageCaused = -DamageCaused;

	// may check validation of eventInstigator
	if (IsValid(EventInstigator))
	{
		if (EventInstigator->IsA(AMainController::StaticClass()))
		{
			
			UpdateHealthPoint(DamageCaused);

			TakeDamageReaction(Damage, DamageCauser);

			if (Health->GetDied())
			{
				// TrueDied(); enemy should insta died
				ExtraDiedAction();

				Destroy();
			}
			return DamageCaused;
		}
		return DamageCaused;
	}
	else
	{
		return DamageCaused;
	}
}

// some enemies may do extra things when they died.
void AEnemyClass::ExtraDiedAction()
{
	// eliminate the health bar
	RemoveHealthBar();

	// reward main
	RewardMainCharacter();

	// spawn artifact
	ArtifactLoot->SpawnArtifact(ItsRarity, GetWorld(), GetActorLocation(), GetActorRotation());


}


void AEnemyClass::TakeDamageReaction(float Damage, AActor* DamageCauser)
{
	// Update Health Bar Display as the health is already decrease
	UpdateHealthBarDisplay();

	// Print the damage number
	SpawnFloatingHealthWidget(Damage);

	//save the damage amount 
	SaveTotalDamageAmount(Damage);

	// spawn niagara effect
	SpawnHitEffectNiagara(SelectHitEffectTrans(DamageCauser->GetActorLocation()));

	// spawn decal effect
	SpawnHitEffectDecal(GetHitEffectDecalTrans(DamageCauser->GetActorLocation()));
}

void AEnemyClass::SpawnFloatingHealthWidget(float Damage)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	FTransform FloatNumberTrans = HealthBarRoot->GetComponentTransform();

	AFloatingNumberActor* FloatNumberActorDelta = GetWorld()->SpawnActor<AFloatingNumberActor>(FloatingNumberActorClass,
		FloatNumberTrans, ActorSpawnParams);

	FloatNumberActorDelta->SetDamageNumber(Damage);
	FloatNumberActorDelta->SetDamageColor(EDamageColor::ERed);

	// the widget should be responsible to destroy itself
}

EDamageColor AEnemyClass::GetFloatHealthColor(float Damage)
{
	return EDamageColor::ERed;
}

void AEnemyClass::SaveTotalDamageAmount(float Damage)
{
	MainPlayerTarget->UpdateTotalDamage(Damage);
}

FTransform AEnemyClass::SelectHitEffectTrans(FVector DamageDauserPosition)
{
	int index = 0;
	int correctIndex = 0;
	int minimumValue = 0;
	FVector SocketLocation;

	for (FName SocketName: HitEffectSocketsNames)
	{
		if (index == 0)
		{
			if (Body->DoesSocketExist(HitEffectSocketsNames[index]))
			{
				SocketLocation = Body->GetSocketLocation(HitEffectSocketsNames[index]);
				minimumValue = (DamageDauserPosition - SocketLocation).Size();
				correctIndex = 0;

				index++;
			}	 
		}
		else
		{
			if (Body->DoesSocketExist(HitEffectSocketsNames[index]))
			{
				SocketLocation = Body->GetSocketLocation(HitEffectSocketsNames[index]);

				if (minimumValue > (DamageDauserPosition - SocketLocation).Size())
				{
					minimumValue = (DamageDauserPosition - SocketLocation).Size();
					correctIndex = index;
				}
				index++;
			}
		}
	}
	return Body->GetSocketTransform(HitEffectSocketsNames[correctIndex]);
}

void AEnemyClass::SpawnHitEffectNiagara(FTransform SpawnTrans)
{
	if (HitEffectNiagara)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation
		(
			GetWorld(),
			HitEffectNiagara,
			SpawnTrans.GetTranslation(),
			SpawnTrans.Rotator(),
			SpawnTrans.GetScale3D(),
			true,
			true,
			ENCPoolMethod::AutoRelease,
			true
		);
	}
}

FTransform AEnemyClass::GetHitEffectDecalTrans(FVector DamageDauserPosition)
{
	// Calculate the direction from self to the target location
	FVector SelfLocation = GetActorLocation();
	FVector Direction = (DamageDauserPosition - SelfLocation).GetSafeNormal();

	for (int i = 0; i < TraceAmount; ++i)
	{
		// Calculate the rotation for this trace
		FRotator TraceRotation(0.0f, i * TraceAngle, 0.0f);

		// Rotate the direction vector based on the TraceRotation
		FVector RotatedDirection = TraceRotation.RotateVector(Direction);

		// Calculate the start location for the trace
		FVector StartTrace = SelfLocation;

		// Calculate the end location for the trace
		FVector EndTrace = SelfLocation + RotatedDirection * (DamageDauserPosition - SelfLocation).Size();

		// Perform the linetrace
		FHitResult DecalHitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this); // Ignore the self actor

		bool bHit = GetWorld()->LineTraceSingleByChannel(DecalHitResult, StartTrace, EndTrace, ECC_Visibility, CollisionParams);
		
		// DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 3, 0, 3);

		// Check if we hit an actor
		if (bHit && DecalHitResult.GetActor())
		{
			// There is an actor in between, you can perform actions here
			AActor* HitActor = DecalHitResult.GetActor();
		}
		else
		{
			// No actor in between, you can perform actions here
		}
	}

	FTransform deltaTrans = FTransform::Identity;
	deltaTrans.SetLocation(FVector::ZeroVector);
	deltaTrans.SetRotation(FQuat::Identity);
	deltaTrans.SetScale3D(FVector::OneVector);
	return deltaTrans;
}
void AEnemyClass::SpawnHitEffectDecal(FTransform SpawnTrans)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (HitEffectDecalClass)
	{
		GetWorld()->SpawnActor<AGeneralDecalActor>(HitEffectDecalClass,
			SpawnTrans, ActorSpawnParams);
	}
}

void AEnemyClass::ApplyDamageToMain(float damage)
{
	if (IsValid(MainPlayerTarget))
	{
		UGameplayStatics::ApplyPointDamage(MainPlayerTarget, damage, GetActorLocation(), EnemyHit, nullptr, this, nullptr);
	}
}

void AEnemyClass::RewardMainCharacter()
{
	// AMain* Player = Cast<AMain>(MainPlayerTarget);
	KillReward = MainPlayerTarget->ApplyAllKillerFeedBackArtifacts(KillReward, this);
	MainPlayerTarget->ProcessKillFeedBacks(KillReward);
}

/* Kind of useless, because at the end of the day, it can not realize the navigation system
* it go through buildings
* It work more likely as a tp
*/
void AEnemyClass::CustomMoveTo()
{
	if (MoveCurveFloat)
	{
		FOnTimelineFloat MoveProgressFunction;

		MoveProgressFunction.BindUFunction(this, FName("CustomMoving"));

		CustomMoveTimeline.AddInterpFloat(MoveCurveFloat, MoveProgressFunction);
		CustomMoveTimeline.SetLooping(false);

		CustomMoveTimeline.PlayFromStart();

	}
}

void AEnemyClass::CustomMoving(float Value)
{
	// check float value	
	// FString miau = FString::SanitizeFloat(Value);
	// GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, *miau);

	// FVector NewLocation = FMath::Lerp(GetActorLocation(), RandomLocation, Value)
	// sSetActorLocation(NewLocation);
}

// ok
void AEnemyClass::testing()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Is testing"));
}

void AEnemyClass::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	return;
}

void AEnemyClass::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	return;
}