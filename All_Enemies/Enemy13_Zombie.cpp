// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy13_Zombie.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "../components/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../Main.h"
#include "../meshes/Weapon_GeneralClass.h"
#include "../meshes/Weapon_Shotgun.h"

// Sets default values
AEnemy13_Zombie::AEnemy13_Zombie()
{
}