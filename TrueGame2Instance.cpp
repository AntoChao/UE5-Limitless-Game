// Fill out your copyright notice in the Description page of Project Settings.


#include "TrueGame2Instance.h"

UTrueGame2Instance::UTrueGame2Instance()
{

}

// BeginPlay of the intance class
void UTrueGame2Instance::Init()
{
	Super::Init();
	// whenever open the game, load last time stats
	// LoadSaveGameStats();
}

void UTrueGame2Instance::LoadSaveGameStats()
{
	// first try to load and if it does not exist, then create a save object
	UTrueSaveGame* SaveGameObj = Cast<UTrueSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameInstance"), 0));
	if (SaveGameObj)
	{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SaveGame Object already exist"));
		GameLanguage = SaveGameObj->GetGameLanguageSaved();
		WeaponSelected = SaveGameObj->GetMainWeapon();
		AbilityOne = SaveGameObj->GetMainAbilityOne();
		AbilityTwo = SaveGameObj->GetMainAbilityTwo();
		AbilityThree = SaveGameObj->GetMainAbilityThree();
		AbilityFour = SaveGameObj->GetMainAbilityFour();
	}
	else
	{
		SaveGameObj = Cast<UTrueSaveGame>(UGameplayStatics::CreateSaveGameObject(UTrueSaveGame::StaticClass()));
		if (SaveGameObj)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Creating SaveGame Object"));
			// if the gamesave does not exist -> create it and save it
			GameLanguage = SaveGameObj->GetGameLanguageSaved();
			WeaponSelected = SaveGameObj->GetMainWeapon();
			AbilityOne = SaveGameObj->GetMainAbilityOne();
			AbilityTwo = SaveGameObj->GetMainAbilityTwo();
			AbilityThree = SaveGameObj->GetMainAbilityThree();
			AbilityFour = SaveGameObj->GetMainAbilityFour();

			UGameplayStatics::SaveGameToSlot(SaveGameObj, TEXT("GameInstance"), 0);
		}
	}
}

void UTrueGame2Instance::SaveGameLanguageStats(ELanguageSelected ALanguage)
{
	UTrueSaveGame* SaveGameObj = Cast<UTrueSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameInstance"), 0));
	if (SaveGameObj)
	{
		SaveGameObj->SetGameLanguageSaved(ALanguage);
	}
}

void UTrueGame2Instance::SaveMainAbilitiesStats(EAbilityCode WeaponChosen, EAbilityCode Ability1Chosen,
	EAbilityCode Ability2Chosen, EAbilityCode Ability3Chosen, EAbilityCode Ability4Chosen)
{
	// try to access the existing savegame object which should exist always
	UTrueSaveGame* SaveGameObj = Cast<UTrueSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameInstance"), 0));
	if (SaveGameObj)
	{
		SaveGameObj->SetMainWeapon(WeaponChosen);
		SaveGameObj->SetMainAbilityOne(Ability1Chosen);
		SaveGameObj->SetMainAbilityTwo(Ability2Chosen);
		SaveGameObj->SetMainAbilityThree(Ability3Chosen);
		SaveGameObj->SetMainAbilityFour(Ability4Chosen);
	}
}

void UTrueGame2Instance::ResetSaveGameStats()
{
	UTrueSaveGame* SaveGameObj = Cast<UTrueSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("GameInstance"), 0));
	// Reset variables to default values
	if (SaveGameObj)
	{
		UGameplayStatics::SaveGameToSlot(SaveGameObj, TEXT("GameInstance"), 0);
	}
	
}

// Game Language
void UTrueGame2Instance::SetGameLanguage(ELanguageSelected ALanguage)
{
	GameLanguage = ALanguage;
}

// Game State
bool UTrueGame2Instance::GetJustOpen()
{
	return JustOpen;
}
void UTrueGame2Instance::SetJustOpen(bool aState)
{
	JustOpen = aState;
}

EGamePlayState UTrueGame2Instance::GetCurrentState() const
{
	return CurrentState;
}
void UTrueGame2Instance::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
}

EAbilityCode UTrueGame2Instance::GetMainWeapon()
{
	return WeaponSelected;
}
void UTrueGame2Instance::SetMainWeapon(EAbilityCode AbilityChosen)
{
	WeaponSelected = AbilityChosen;
}

EAbilityCode UTrueGame2Instance::GetMainAbilityOne()
{
	return AbilityOne;
}
void UTrueGame2Instance::SetMainAbilityOne(EAbilityCode AbilityChosen)
{
	AbilityOne = AbilityChosen;
}

EAbilityCode UTrueGame2Instance::GetMainAbilityTwo()
{
	return AbilityTwo;
}
void UTrueGame2Instance::SetMainAbilityTwo(EAbilityCode AbilityChosen)
{
	AbilityTwo = AbilityChosen;
}

EAbilityCode UTrueGame2Instance::GetMainAbilityThree()
{
	return AbilityThree;
}
void UTrueGame2Instance::SetMainAbilityThree(EAbilityCode AbilityChosen)
{
	AbilityThree = AbilityChosen;
}

EAbilityCode UTrueGame2Instance::GetMainAbilityFour()
{
	return AbilityFour;
}
void UTrueGame2Instance::SetMainAbilityFour(EAbilityCode AbilityChosen)
{
	AbilityFour = AbilityChosen;
}

void UTrueGame2Instance::SetTotalInGameSegs(int TotalGameTime)
{
	TotalInGameSegs = TotalGameTime;
}
void UTrueGame2Instance::SetTotalDamageDealed(float DamagedDealed)
{
	TotalDamageDealed = DamagedDealed;
}
void UTrueGame2Instance::SetTotalEnemiesKilled(int EnemiesKilled)
{
	TotalEnemiesKilled = EnemiesKilled;
}
void UTrueGame2Instance::SetTotalXPLeanrt(float XPReceived)
{
	TotalXPLeanrt = XPReceived;
}
void UTrueGame2Instance::SetTotalDamageTaken(float DamageTaken)
{
	TotalDamageTaken = DamageTaken;
}
void UTrueGame2Instance::SetTotalItemsCollected(int NumberOfItemsCollected)
{
	TotalItemsCollected = NumberOfItemsCollected;
}
void UTrueGame2Instance::SetDieReason(FText ADieReason)
{
	DieReason = ADieReason;
}
void UTrueGame2Instance::SetAllArtifactList(TArray<AGeneralArtifact*> MainArtifactList)
{
	AllArtifactList = MainArtifactList;
}