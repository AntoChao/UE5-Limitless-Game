// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralKillFeedBackArtifact.h"
#include "../Main.h"
// killfeddback container
#include "../DataContainer/data_killfeedbackinfo.h"

// Sets default values
AGeneralKillFeedBackArtifact::AGeneralKillFeedBackArtifact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EKillFeedBack;
}

// Called when the game starts or when spawned
void AGeneralKillFeedBackArtifact::BeginPlay()
{
	Super::BeginPlay();
	
	SetArtifact(EArtifactType::EKillFeedBack);
}

UData_KillFeedBackInfo* AGeneralKillFeedBackArtifact::ApplyKillFeedBackEffect(UData_KillFeedBackInfo* KillInfo, AActor* Enemy)
{
	return KillInfo;
} 