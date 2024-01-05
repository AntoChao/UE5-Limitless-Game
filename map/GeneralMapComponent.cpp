// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralMapComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "../Main.h"

// Sets default values
AGeneralMapComponent::AGeneralMapComponent() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Building Area"));
	CollisionComp->SetupAttachment(SceneComponent);

	// Set as root component
	// RootComponent = CollisionComp;

	BuildingBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building"));
	BuildingBody->SetOnlyOwnerSee(false);
	BuildingBody->SetupAttachment(SceneComponent);
	BuildingBody->bCastDynamicShadow = false;
	BuildingBody->CastShadow = false;
	BuildingBody->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AGeneralMapComponent::BeginPlay() {
	Super::BeginPlay();

	// overlap event
	if (IsValid(CollisionComp)) {
		CollisionComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGeneralMapComponent::OnOverlapBegin);
	}
}

void AGeneralMapComponent::SetPlayerInArea(bool isInArea) {
	playerInArea = isInArea;
}

void AGeneralMapComponent::SetRandomRotation() {
	if (setRandomLocation) {
		float randomPitch = FMath::RandRange(-180, 180);
		float randomYaw = FMath::RandRange(-180, 180);
		float randomRoll = FMath::RandRange(-180, 180);

		FRotator RandomRotation = FRotator(randomPitch, randomYaw, randomRoll);
		SetActorRotation(RandomRotation);
	}	
}

// is able to add some bonus for certain enemies in certain area
void AGeneralMapComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		AMain* player = Cast<AMain>(OtherActor);

		if (IsValid(player)) {
			PlayerInAreaResponse(player);
		}
	}
}

void AGeneralMapComponent::PlayerInAreaResponse(AMain* player) {
	SetPlayerInArea(true);
	player->SetCurrentFloor(floorType);
}

void AGeneralMapComponent::PlayerLeaveAreaResponse(AMain* player) {
	SetPlayerInArea(false);
	player->SetCurrentFloor(floorType);
}