// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCompSecretPortal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "../TrueProject2GameModeBase.h"
#include "../Main.h"

// Sets default values
AMapCompSecretPortal::AMapCompSecretPortal() {

	return;
}

void AMapCompSecretPortal::PlayerInAreaResponse(AMain* player) {
	if (IsValid(player)) {
		if (IsActivated) {
			ATrueProject2GameModeBase* GameMode = 
				Cast<ATrueProject2GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			
			// no, it should only transport main to another place in order kill game author
			if (IsValid(GameMode)) {
				GameMode->SetGameOver(EGameOverReason::ETrueEnding);
			}
		}
	}
}

bool AMapCompSecretPortal::GetIfIsActivated() {
	return IsActivated;
}

void AMapCompSecretPortal::SetIfIsActivated(bool newActivation) {
	IsActivated = newActivation;
}