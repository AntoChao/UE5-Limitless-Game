// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy2_Parasite_VenomGas.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"
#include "EnemyClass.h"

// Sets default values
AEnemy2_Parasite_VenomGas::AEnemy2_Parasite_VenomGas()
{

}

// Called when the game starts or when spawned
void AEnemy2_Parasite_VenomGas::BeginPlay()
{
	Super::BeginPlay();

	Damage = 1.0f;

	GetWorldTimerManager().SetTimer(LifeSpamTimer, this,
		&AEnemy2_Parasite_VenomGas::CustomTickFunction, LifeSpamTime, false);

	CustomTickFunction();
}

void AEnemy2_Parasite_VenomGas::VenomDesapear()
{
	Destroy();
}

void AEnemy2_Parasite_VenomGas::CustomTickFunction()
{
	GetWorldTimerManager().SetTimer(TickSimulatorTimer, this,
		&AEnemy2_Parasite_VenomGas::CustomTickFunction, TickSimulateTime, true);
	
	CollisionComp->SetGenerateOverlapEvents(false);
	CollisionComp->SetGenerateOverlapEvents(true);
}

void AEnemy2_Parasite_VenomGas::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Wind Slash Is Colliding with main"));

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//if (OtherActor->GetClass()->IsChildOf(AAllCharactersClass::StaticClass()))
		if (OtherActor->IsA(AMain::StaticClass()))
		{
			Main = Cast<AMain>(OtherActor);
			//GetOverlappingActors(EnemyHitten, AEnemyClass::StaticClass());
			DoDamage();
		}
	}
}

void AEnemy2_Parasite_VenomGas::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// nothing
}

void AEnemy2_Parasite_VenomGas::SetDamage(float ReceiveDamage)
{
	Damage = ReceiveDamage;
}

void AEnemy2_Parasite_VenomGas::DoDamage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Doing Damage to enemy"));

	UGameplayStatics::ApplyPointDamage(Main, Damage, GetActorLocation(), MyHit, nullptr, this, NULL);
}