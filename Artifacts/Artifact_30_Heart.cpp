// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_30_Heart.h"
#include "../All_Enemies/EnemyClass.h"
#include "../Main.h"

// Sets default values
AArtifact_30_Heart::AArtifact_30_Heart()
{
	ThisArtifactType = EArtifactType::EDied;
}

// Called when the game starts or when spawned
void AArtifact_30_Heart::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

bool AArtifact_30_Heart::ApplyDiedEffect(AMain* PlayerMain)
{
	/*
	main should has a parameter of somehow check this and set died on healthcomponent
	main should have the funcion reborn, which revive with half life and do damage around
	*/
	if (PlayerMain->GetCharacterHealth() <= 0.0f) // is died
	{
		PlayerMain->Revive(revivePercentageHealth);
	}

	return false;
}