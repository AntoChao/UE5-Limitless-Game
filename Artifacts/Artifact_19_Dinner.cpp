// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact_19_Dinner.h"
#include "../All_Enemies/EnemyClass.h"
// killfeddback container
#include "../DataContainer/data_killfeedbackinfo.h"

// Sets default values
AArtifact_19_Dinner::AArtifact_19_Dinner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ThisArtifactType = EArtifactType::EKillFeedBack;
}

// Called when the game starts or when spawned
void AArtifact_19_Dinner::BeginPlay()
{
	Super::BeginPlay();

	//SetArtifact(Attack);
}

UData_KillFeedBackInfo* AArtifact_19_Dinner::ApplyKillFeedBackEffect(class UData_KillFeedBackInfo* KillInfo, AActor* Enemy)
{
	KillInfo->UpdateFrenzyReward(frenzyRatio);
	KillInfo->UpdateCalmReward(calmRatio);

	return KillInfo;
}

void AArtifact_19_Dinner::UpdateFrenzyRatio(float newRatio)
{
	frenzyRatio = newRatio;
}
void AArtifact_19_Dinner::UpdateCalmRatio(float newRatio)
{
	calmRatio = newRatio;
}