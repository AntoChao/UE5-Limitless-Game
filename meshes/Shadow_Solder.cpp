// Fill out your copyright notice in the Description page of Project Settings.


#include "Shadow_Solder.h"

// Sets default values
AShadow_Solder::AShadow_Solder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	BodyComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShadowSolderMesh"));
	BodyComponent->SetOnlyOwnerSee(false);
	//BodyComponent->SetupAttachment(FirstPersonCamaraComponent);
	BodyComponent->bCastDynamicShadow = false;
	BodyComponent->CastShadow = false;
	BodyComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BodyComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

}

// Called when the game starts or when spawned
void AShadow_Solder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShadow_Solder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

