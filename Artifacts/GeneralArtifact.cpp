// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralArtifact.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../Main.h"

// Sets default values
AGeneralArtifact::AGeneralArtifact() {
	
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("BoxComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("HitBox");

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Default, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Artifact Body"));
	Body->SetOnlyOwnerSee(false);
	Body->SetupAttachment(CollisionComp);
	Body->bCastDynamicShadow = false;
	Body->CastShadow = false;
	Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}
// Called when the game starts or when spawned
void AGeneralArtifact::BeginPlay() {
	Super::BeginPlay();
	
	// overlap event
	CollisionComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGeneralArtifact::OnOverlapBegin);

}

// Called every frame
void AGeneralArtifact::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Rotate the actor on the XY plane
	FRotator NewRotation = GetActorRotation();
	float RotationChange = RotationSpeed * DeltaTime;
	NewRotation.Yaw += RotationChange;
	SetActorRotation(NewRotation);

}

void AGeneralArtifact::SetArtifact(EArtifactType AArtifactType) {
	ThisArtifactType = AArtifactType;
}

EArtifactType AGeneralArtifact::GetArtifact() {
	return ThisArtifactType;
}

void AGeneralArtifact::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		AMain* player = Cast<AMain>(OtherActor);

		if (IsValid(player) && !player->isMainDetecting()) {
			// create a delta same artifact which sent to main

			UClass* ActorClass = this->GetClass();
			AActor* DuplicatedActor = nullptr;
			
			if (ActorClass) {
				DuplicatedActor = NewObject<AActor>(GetTransientPackage(), ActorClass);
			}
			
			player->GetArtifact(DuplicatedActor);
			// player->GetArtifact(this);
			
			Destroy();
		}
	}
}

UTexture2D* AGeneralArtifact::GetArtifactImage() {
	return ArtifactImage;
}
FString AGeneralArtifact::GetArtifactName() {
	return ArtifactName;
}
FString AGeneralArtifact::GetArtifactDiscription() {
	return ArtifactDiscription;
}