// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "GeneralArtifact.generated.h"

UENUM()
enum class EArtifactType
{
	EPickUp,
	EAttack,
	EDefense,
	EKillFeedBack,
	EDied,
	ECost,
	EUnknown
};

UENUM()
enum class EArtifactRarity
{
	ENormal,
	ESpecial,
	ERare,
	EOP,
	EUnknown
};

UCLASS()
class LIMITLESS_API AGeneralArtifact : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralArtifact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Sphere collision component */
	UPROPERTY(EditAnywhere, Category = "Collision")
		class USphereComponent* CollisionComp;

	/** Body Structure */
	UPROPERTY(EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* Body;

	EArtifactType ThisArtifactType;

	UPROPERTY(EditAnywhere, Category = "Rotation")
		float RotationSpeed = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Rotation")
		float ArtifactDuration = 5.0f;

	// Artifact Info For Displaying
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		class UTexture2D* ArtifactImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		FString ArtifactName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		FString ArtifactDiscription;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetArtifact(EArtifactType AArtifactType);
	EArtifactType GetArtifact();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Artifact for display
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		UTexture2D* GetArtifactImage();
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		FString GetArtifactName();
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		FString GetArtifactDiscription();

};
