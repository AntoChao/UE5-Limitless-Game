// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Common_Enums.h"
#include "Kismet/GameplayStatics.h"
#include "TrueSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TRUEPROJECT2_API UTrueSaveGame : public USaveGame
{
	GENERATED_BODY()

	UTrueSaveGame();

protected:
	// Language
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
		ELanguageSelected GameLanguageSaved = ELanguageSelected::EEnglish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode WeaponSaved = EAbilityCode::ENone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode AbilityOneSaved = EAbilityCode::ENone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode AbilityTwoSaved = EAbilityCode::ENone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode AbilityThreeSaved = EAbilityCode::ENone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode AbilityFourSaved = EAbilityCode::ENone;

	// Difficulty
	
	

	// BEST RECORD

	// Unblock stuff...

public:
	// Language
	UFUNCTION(BlueprintCallable, Category = "Language")
		ELanguageSelected GetGameLanguageSaved();
	UFUNCTION(BlueprintCallable, Category = "Language")
		void SetGameLanguageSaved(ELanguageSelected ALanguage);

	// Main Abilities
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		EAbilityCode GetMainWeapon();
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		void SetMainWeapon(EAbilityCode AbilityChosen);
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		EAbilityCode GetMainAbilityOne();
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		void SetMainAbilityOne(EAbilityCode AbilityChosen);
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		EAbilityCode GetMainAbilityTwo();
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		void SetMainAbilityTwo(EAbilityCode AbilityChosen);
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		EAbilityCode GetMainAbilityThree();
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		void SetMainAbilityThree(EAbilityCode AbilityChosen);
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		EAbilityCode GetMainAbilityFour();
	UFUNCTION(BlueprintCallable, Category = "Main AbilityCode")
		void SetMainAbilityFour(EAbilityCode AbilityChosen);

};
