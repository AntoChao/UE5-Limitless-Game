// Fill out your copyright notice in the Description page of Project Settings.


#include "TrueSaveGame.h"

UTrueSaveGame::UTrueSaveGame()
{
}

ELanguageSelected UTrueSaveGame::GetGameLanguageSaved()
{
	return GameLanguageSaved;
}

void UTrueSaveGame::SetGameLanguageSaved(ELanguageSelected ALanguage)
{
	GameLanguageSaved = ALanguage;
}

EAbilityCode UTrueSaveGame::GetMainWeapon()
{
	return WeaponSaved;
}
void UTrueSaveGame::SetMainWeapon(EAbilityCode AbilityChosen)
{
	WeaponSaved = AbilityChosen;
}

EAbilityCode UTrueSaveGame::GetMainAbilityOne()
{
	return AbilityOneSaved;
}
void UTrueSaveGame::SetMainAbilityOne(EAbilityCode AbilityChosen)
{
	AbilityOneSaved = AbilityChosen;
}

EAbilityCode UTrueSaveGame::GetMainAbilityTwo()
{
	return AbilityTwoSaved;
}
void UTrueSaveGame::SetMainAbilityTwo(EAbilityCode AbilityChosen)
{
	AbilityTwoSaved = AbilityChosen;
}

EAbilityCode UTrueSaveGame::GetMainAbilityThree()
{
	return AbilityThreeSaved;
}
void UTrueSaveGame::SetMainAbilityThree(EAbilityCode AbilityChosen)
{
	AbilityThreeSaved = AbilityChosen;
}

EAbilityCode UTrueSaveGame::GetMainAbilityFour()
{
	return AbilityFourSaved;
}
void UTrueSaveGame::SetMainAbilityFour(EAbilityCode AbilityChosen)
{
	AbilityFourSaved = AbilityChosen;
}
