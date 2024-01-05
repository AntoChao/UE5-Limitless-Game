// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Artifacts/GeneralArtifact.h"
#include "Common_Enums.h"
#include "Kismet/GameplayStatics.h"
#include "TrueSaveGame.h"
#include "TrueGame2Instance.generated.h"

/**
 * Preparing -> Just OpenLevel -> Widgets: initMenu, PreGame
 * Playing -> Spawn main, spawn enemies overtime, arise difficulty overtime
 * GameOver -> Widgets: PostGame
 */

UCLASS()
class LIMITLESS_API UTrueGame2Instance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UTrueGame2Instance();

protected:
	virtual void Init() override;

	// Save Game
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void LoadSaveGameStats();
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void ResetSaveGameStats();

	// At the begining of everything -> game instance should read the save game object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
		ELanguageSelected GameLanguage;

	// Game State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState")
		bool JustOpen = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState")
		bool JustEnd = true;

	// variables to store
	// Game State Control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState")
		EGamePlayState CurrentState = EGamePlayState::EPreparing;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Over")
		EGameOverReason TheGameOverReason = EGameOverReason::EFailMission;

	// InitMenu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode WeaponSelected = EAbilityCode::EShotgun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode AbilityOne = EAbilityCode::EBlackHoleBomb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode AbilityTwo = EAbilityCode::EFForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode AbilityThree = EAbilityCode::ETeleport;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main AbilityCode")
		EAbilityCode AbilityFour = EAbilityCode::EBulletTime;
	
	/* In Game
	* Unlocks items
	* Main Stats when died -> pass to Post Game as analisis
	*/
	// Post Game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Info")
		int TotalInGameDays;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats")
		int TotalDamageDealed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats")
		int TotalEnemiesKilled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats")
		int TotalXPLeanrt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats")
		int TotalDamageTaken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats")
		int TotalItemsCollected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats")
		FText DieReason;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Stats")
		TArray<AGeneralArtifact*> AllArtifactList = {};
	

public:
	// Save Game
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void SaveGameLanguageStats(ELanguageSelected ALanguage);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void SaveMainAbilitiesStats(EAbilityCode WeaponChosen, EAbilityCode Ability1Chosen,
			EAbilityCode Ability2Chosen, EAbilityCode Ability3Chosen, EAbilityCode Ability4Chosen);

	UFUNCTION(BlueprintCallable, Category = "Language")
		void SetGameLanguage(ELanguageSelected ALanguage);

	// Game State
	UFUNCTION(BlueprintCallable, Category = "Game State")
		bool GetJustOpen();
	UFUNCTION(BlueprintCallable, Category = "Game State")
		void SetJustOpen(bool aState);

	UFUNCTION(BlueprintCallable, Category = "Game State")
		EGamePlayState GetCurrentState() const;
	UFUNCTION(BlueprintCallable, Category = "Game State")
		void SetCurrentState(EGamePlayState NewState);

	// Game Over
	UFUNCTION(BlueprintCallable, Category = "Game Over")
		EGameOverReason GetGameOverReason();
	UFUNCTION(BlueprintCallable, Category = "Game Over")
		void SetGameOverReason(EGameOverReason NewReason);

	// setters and getters for variables
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

	// PostGame stuff
	// Setters and getters for Postgame stuff
	UFUNCTION(BlueprintCallable, Category = "PostGame Stats")
		void SetTotalInGameDays(float TotalGameDays);
	UFUNCTION(BlueprintCallable, Category = "PostGame Stats")
		void SetTotalDamageDealed(float DamagedDealed);
	UFUNCTION(BlueprintCallable, Category = "PostGame Stats")
		void SetTotalEnemiesKilled(int EnemiesKilled);
	UFUNCTION(BlueprintCallable, Category = "PostGame Stats")
		void SetTotalXPLeanrt(float XPReceived);
	UFUNCTION(BlueprintCallable, Category = "PostGame Stats")
		void SetTotalDamageTaken(float DamageTaken);
	UFUNCTION(BlueprintCallable, Category = "PostGame Stats")
		void SetTotalItemsCollected(int NumberOfItemsCollected);
	UFUNCTION(BlueprintCallable, Category = "PostGame Stats")
		void SetDieReason(FText ADieReason);
	UFUNCTION(BlueprintCallable, Category = "PostGame Stats")
		void SetAllArtifactList(TArray<AGeneralArtifact*> MainArtifactList);

};
