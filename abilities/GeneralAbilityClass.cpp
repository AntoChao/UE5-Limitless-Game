// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralAbilityClass.h"

/* -------------------------
Definition: very messy -> should REORDER
	All stats:
		Pre-Calculate/ Define:
			Damage: -> should not be part of general ability, because there are ability that do not do damage
			FrenzyCost:
			CalmCost:
			Type:
		
		Calculate After Activate:
			FrenzyReward
			CalmReward
			XP (reward)
 ------------------------- */

// Sets default values
AGeneralAbilityClass::AGeneralAbilityClass(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// stats
	Damage = CreateDefaultSubobject<UDamageComponent>(TEXT("Damage"));
	FrenzyCost = CreateDefaultSubobject<UFrenzyComponent>(TEXT("FrenzyCost"));
	FrenzyReward = CreateDefaultSubobject<UFrenzyComponent>(TEXT("FrenzyReward"));
	CalmCost = CreateDefaultSubobject<UCalmComponent>(TEXT("CalmCost"));
	CalmReward = CreateDefaultSubobject<UCalmComponent>(TEXT("CalmReward"));
	XP = CreateDefaultSubobject<UXPComponent>(TEXT("XP"));
	
	// AbilityVideoPlayer = CreateDefaultSubobject<UMediaComponent>(TEXT("AbilityVideoSource"));
	// AbilityVideoPlayer->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AbilityVideoSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("AbilityVideoSound"));
	AbilityVideoSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// feed back container, this does not do anything by its own, it exist just for function: createFeedBack
	feedBackContainer = CreateDefaultSubobject<UData_AbilityFeedBackInfo>(TEXT("FeedBackContainer"));
}

bool AGeneralAbilityClass::IsAbilityLocked()
{
	return Locked;
}

// Ability Info For Displaying
UTexture2D* AGeneralAbilityClass::GetAbilityImage()
{
	return AbilityImage;
}
FString AGeneralAbilityClass::GetAbilityName(ELanguageSelected ALanguage)
{
	switch (ALanguage)
	{
		case ELanguageSelected::EEnglish:
		{
			return AbilityNameEng;
		}
		case ELanguageSelected::EChinese:
		{
			return AbilityNameChi;
		}
		case ELanguageSelected::ESpanish:
		{
			return AbilityNameSpn;
		}
		default:
		{
			return AbilityNameEng;
		}
	}
}
FString AGeneralAbilityClass::GetAbilityDiscription(ELanguageSelected ALanguage)
{
	switch (ALanguage)
	{
		case ELanguageSelected::EEnglish:
		{
			return AbilityDiscriptionEng;
		}
		case ELanguageSelected::EChinese:
		{
			return AbilityDiscriptionChi;
		}
		case ELanguageSelected::ESpanish:
		{
			return AbilityDiscriptionSpn;
		}
		default:
		{
			return AbilityDiscriptionEng;
		}
	}
}
UMediaSource* AGeneralAbilityClass::GetAbilityVideoSource()
{
	return AbilityVideoSource;
}
UMediaSoundComponent* AGeneralAbilityClass::GetAbilityVideoSound()
{
	return AbilityVideoSound;
}

UData_AbilityFeedBackInfo* AGeneralAbilityClass::Activate(UData_AbilityRequiredInfo* requiredInfo)
{
	/*
	1 Initialize all stats to avoid errors
	2 Do what the ability should do
	3 Create feed Back
	*/
	if (AbilityRequirement(requiredInfo))
	{
		ActivateAbilityEffect(requiredInfo);
		CreateFeedBackContainer();
	}

	return feedBackContainer;
}

/*	ActivateAbilityEffect has 3 process
*	Customize ability stats
*	Do the effect
*	Calculate feedback in order to return -> override all calculution base on ability
*/
void AGeneralAbilityClass::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo)
{
	// depends on ability
	return;
}

// should be call by before the return -> because they define these basic values
void AGeneralAbilityClass::CreateFeedBackContainer()
{
	// if the ability use neutro, how to process it in the feed back.
	feedBackContainer->InitializedAllFeedBacks(true, FrenzyCost->GetFrenzy(), CalmCost->GetCalm(),
		FrenzyReward->GetFrenzy(), CalmReward->GetCalm(),
		moveSpeedReward, XP->GetXP());
}

// be defined in each ability
bool AGeneralAbilityClass::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo)
{
	return false;
}

void AGeneralAbilityClass::CustomizeStatsPerAbility(float VALUEbaseDamage, float VALUECritChance, 
	float VALUECritMultiplier, float VALUEfireRate, float VALUEradioImpact,
	float VALUEduration, float VALUErange, bool VALUEdoSelfDamage,
	float VALUEbaseFrenzyCost, float VALUEbaseFrenzyReward,
	float VALUEbaseCalmCost, float VALUEbaseCalmReward,
	float VALUEmoveSpeedReward, int VALUEbaseXP)
{
	Damage->SetDamage(VALUEbaseDamage);
	Damage->SetCritChance(VALUECritChance);
	Damage->SetCritMultiplier(VALUECritMultiplier);
	Damage->SetFireRate(VALUEfireRate);
	radioImpact = VALUEradioImpact;
	duration = VALUEduration;
	range = VALUErange;
	doSelfDamage = VALUEdoSelfDamage;
	FrenzyCost->SetFrenzy(VALUEbaseFrenzyCost);
	FrenzyReward->SetFrenzy(VALUEbaseFrenzyReward);
	CalmCost->SetCalm(VALUEbaseCalmCost);
	CalmReward->SetCalm(VALUEbaseCalmReward);
	moveSpeedReward = VALUEmoveSpeedReward;
	XP->SetXP(VALUEbaseXP);
}

// These are actually bad -> Cuz should be polimorphis to enemies abilities, but whatever
void AGeneralAbilityClass::ApplyDamageToEnemy(AEnemyClass* EnemySelected, float TheDamage, UData_AbilityRequiredInfo* requiredInfo)
{
	if (IsValid(EnemySelected))
	{
		UGameplayStatics::ApplyPointDamage(EnemySelected, TheDamage, requiredInfo->GetPlayerLocation(), requiredInfo->GetHitResult(), requiredInfo->GetPlayer()->GetMainController(), this, nullptr);
		SpawnHitEffectNiagara(requiredInfo->GetHitResult());
	}
}

float AGeneralAbilityClass::CalculateGeneralDamage(UData_AbilityRequiredInfo* requiredInfo)
{
	return Damage->CalculateDamage(requiredInfo->GetPlayer()->GetCharacterPowerComponent());
}

float AGeneralAbilityClass::CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo)
{
	return 0.0f;
}

float AGeneralAbilityClass::GetAbilityFireRate()
{
	return Damage->GetFireRate();
}