// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralAbilityClass.h"

// Sets default values
AGeneralAbilityClass::AGeneralAbilityClass(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {
	// feed back container, this does not do anything by its own, it exist just for function: createFeedBack
	// feedBackContainer = CreateDefaultSubobject<UData_AbilityFeedBackInfo>(TEXT("FeedBackContainer"));
}

bool AGeneralAbilityClass::IsAbilityLocked() {
	return Locked;
}

// Ability Info For Displaying
UTexture2D* AGeneralAbilityClass::GetAbilityImage() {
	return AbilityImage;
}
FString AGeneralAbilityClass::GetAbilityName(ELanguageSelected ALanguage) {
	switch (ALanguage) {
		case ELanguageSelected::English: {
			return AbilityNameEng;
		}
		case ELanguageSelected::Chinese: {
			return AbilityNameChi;
		}
		case ELanguageSelected::Spanish: {
			return AbilityNameSpn;
		}
		default: {
			return AbilityNameEng;
		}
	}
}
FString AGeneralAbilityClass::GetAbilityDiscription(ELanguageSelected ALanguage) {
	switch (ALanguage) {
		case ELanguageSelected::English: {
			return AbilityDiscriptionEng;
		}
		case ELanguageSelected::Chinese: {
			return AbilityDiscriptionChi;
		}
		case ELanguageSelected::Spanish: {
			return AbilityDiscriptionSpn;
		}
		default: {
			return AbilityDiscriptionEng;
		}
	}
}

UData_AbilityFeedBackInfo* AGeneralAbilityClass::Activate(UData_AbilityRequiredInfo* requiredInfo) {
	/*
	1 Initialize all stats to avoid errors
	2 Do what the ability should do
	3 Create feed Back
	*/

	feedBackContainer = NewObject<UData_AbilityFeedBackInfo>(this, 
		UData_AbilityFeedBackInfo::StaticClass());

	if (AbilityRequirement(requiredInfo)) {

		if (IsValid(AbilitySound)) {
			UGameplayStatics::PlaySoundAtLocation(this, AbilitySound, 
				requiredInfo->GetPlayer()->GetActorLocation());
		}

		ActivateAbilityEffect(requiredInfo);
		CreateFeedBackContainer();
	}

	return feedBackContainer;
}

void AGeneralAbilityClass::ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo) {
	// depends on ability
	return;
}

// should be call by before the return -> because they define these basic values
void AGeneralAbilityClass::CreateFeedBackContainer() {
	feedBackContainer->InitializedAllFeedBacks(true, frenzyCost, calmCost,
		frenzyReward, calmReward,
		moveSpeedReward, XPReward);
}

// be defined in each ability
bool AGeneralAbilityClass::AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo) {
	return (requiredInfo->GetPlayerFrenzy() >= frenzyCost 
		&& requiredInfo->GetPlayerCalm() >= calmCost);
}

// These are actually bad -> Cuz should be polimorphis to enemies abilities, but whatever
void AGeneralAbilityClass::ApplyDamageToEnemy(AEnemyClass* EnemySelected, float TheDamage, UData_AbilityRequiredInfo* requiredInfo) {
	if (IsValid(EnemySelected))	{
		UGameplayStatics::ApplyPointDamage(EnemySelected, TheDamage, 
			requiredInfo->GetPlayerLocation(), requiredInfo->GetHitResult(), 
			requiredInfo->GetPlayer()->GetMainController(), this, nullptr);

		SpawnHitEffectNiagara(requiredInfo->GetHitResult());
	}
}

float AGeneralAbilityClass::CalculateGeneralDamage(UData_AbilityRequiredInfo* requiredInfo) {
	return CalculateDamage(requiredInfo->GetPlayer()->GetCharacterPowerComponent());
}

float AGeneralAbilityClass::CalculateDamage(UCharacterPowerComponent* PowerComponent) {
	float deltaBaseDamage = baseDamage + PowerComponent->GetPower();
	float deltaCritChance = baseCritChance + PowerComponent->GetCharacCritChance();
	float deltaCritMultiplier = baseCritMultiplier + PowerComponent->GetCharacCritMultiplier();

	if (CritictStrike(deltaCritChance)) {
		return deltaBaseDamage * deltaCritMultiplier;
	}
	else {
		return deltaBaseDamage;
	}
}

bool AGeneralAbilityClass::CritictStrike(float Probability) {
	float Chance = FMath::RandRange(1, 100);

	return (Chance <= Probability);
}

float AGeneralAbilityClass::CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo) {
	return 0.0f;
}

float AGeneralAbilityClass::GetAbilityFireRate() {
	return abilityRate;
}