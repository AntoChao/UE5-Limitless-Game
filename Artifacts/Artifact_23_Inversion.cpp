// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_23_Inversion.h"
#include "../All_Enemies/EnemyClass.h"
// killfeddback container
#include "../DataContainer/data_killfeedbackinfo.h"

// Sets default values
AArtifact_23_Inversion::AArtifact_23_Inversion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EKillFeedBack;
}

// Called when the game starts or when spawned
void AArtifact_23_Inversion::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

UData_KillFeedBackInfo* AArtifact_23_Inversion::ApplyKillFeedBackEffect(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy)
{
	KillInfo->UpdateFrenzyReward(frenzyRatio);
	KillInfo->UpdateCalmReward(calmRatio);

	return KillInfo;
}

void AArtifact_23_Inversion::UpdateFrenzyRatio(float newRatio)
{
	frenzyRatio = newRatio;
}
void AArtifact_23_Inversion::UpdateCalmRatio(float newRatio)
{
	calmRatio = newRatio;
}