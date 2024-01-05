// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrueProject2GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"

#include "Main.h"
#include "map/MapCompMainBase.h"
#include "map/MapCompSecretPortal.h"

// Enemies
#include "All_Enemies/EnemyClass.h"
#include "All_Enemies/BasicEnemy.h"
#include "All_Enemies/Enemy1_Bird.h"
#include "All_Enemies/Enemy2_Parasite_Baby.h"
#include "All_Enemies/Enemy3_Parasite_Rookie.h"
#include "All_Enemies/Enemy4_Parasite_Ultimate.h"
#include "All_Enemies/Enemy5_Human_Blade.h"
#include "All_Enemies/Enemy6_Human_Pistol.h"
#include "All_Enemies/Enemy7_Human_Shotgun.h"
#include "All_Enemies/Enemy8_Boar.h"
#include "All_Enemies/Enemy9_Robot_Girl.h"
#include "All_Enemies/Enemy10_Robot_Papu.h"
#include "All_Enemies/Enemy11_Robot_Executor.h"
#include "All_Enemies/Enemy13_Zombie.h"
#include "All_Enemies/Enemy15_Bat_1.h"
#include "All_Enemies/Enemy19_Hunter_Sniper.h"
#include "All_Enemies/Enemy22_Cultist.h"
#include "All_Enemies/Enemy24_MiniBot.h"
#include "All_Enemies/Enemy25_Sandworn.h"
#include "All_Enemies/Enemy26_Spider_Queen.h"
#include "All_Enemies/Enemy27_Swat.h"
#include "All_Enemies/Enemy28_Wasp.h"
#include "All_Enemies/Enemy29_Scorpio.h"
#include "All_Enemies/Enemy30_AttackDrone.h"
#include "All_Enemies/Enemy31_KillerRabbit.h"

ATrueProject2GameModeBase::ATrueProject2GameModeBase() {
    // PrimaryActorTick.bCanEverTick = true;
}

void ATrueProject2GameModeBase::BeginPlay() {
    Super::BeginPlay();

    // Game GameInstance
    GameInstance = Cast<UTrueGame2Instance>(UGameplayStatics::GetGameInstance(this));
    
    MainIsSpawned = false;
    /*
    MainBaseRotation = FRotator(0, FMath::RandRange(0.0f, 360.0f), 0);
    SecretPortalRotation = MainBaseRotation;
    */
    // Process GameState
    HandleGameState();

    if (GameInstance->GetCurrentState() == EGamePlayState::EPlaying) {
        // Time control
        TimeRunning();
    }

    if (MainIsSpawned) {
        CurrentObjective = ObjExplore;

        GetWorldTimerManager().SetTimer(ExploreTimerHandle, this,
            &ATrueProject2GameModeBase::FinishExploration, ExploreSeg, false);
    }

    PlayBGM();
}

// Time Control
void ATrueProject2GameModeBase::TimeRunning() {

    CurrentSecond += SegRate;

    if (CurrentSecond >= Seg2Minutes) {
        int minutesExceed = CurrentSecond / Seg2Minutes;
        CurrentSecond = CurrentSecond - Seg2Minutes * minutesExceed;
        CurrentMinute += minutesExceed;

        if (CurrentMinute >= Minutes2Hour) {
            int hourExceed = CurrentMinute / Minutes2Hour;
            CurrentMinute = CurrentMinute - (Minutes2Hour * hourExceed);
            CurrentHour += hourExceed;

            CheckTime();

            if (CurrentHour >= Hour2Day) {
                int dayExceed = CurrentHour / Hour2Day;
                CurrentHour = CurrentHour - (Hour2Day * dayExceed);
                CurrentDay += dayExceed;
                
                if (!isSurvived) {
                    CheckSurvive();
                }    
            }
        }
    }

    // run the world timer
    GetWorldTimerManager().SetTimer(RunTimerHandle, this,
        &ATrueProject2GameModeBase::TimeRunning, 1.0f, false);
}

void ATrueProject2GameModeBase::SetGameOver(EGameOverReason NewReason) {

    PastAllPostGameStats();

    if (IsValid(GameInstance)) {
        GameInstance->SetGameOverReason(NewReason);
        GameInstance->SetCurrentState(EGamePlayState::EGameOver);
        OpenPostGameState();
    }
}

// Ending: Survived
void ATrueProject2GameModeBase::FinishExploration() {
    CurrentObjective = ObjSurvive;
}

void ATrueProject2GameModeBase::CheckSurvive() {
    // maybe more complicate
    if (CurrentDay >= SurviveDay) {
        
        isSurvived = true;

        // update the objective
        CurrentObjective = ObjPrepareExit;

        GetWorldTimerManager().SetTimer(SurvivedTimerHandle, this,
            &ATrueProject2GameModeBase::Survived, ExitSeg, false);
    }
}

void ATrueProject2GameModeBase::Survived() {
    // activate the base and update the objective
    CurrentObjective = ObjExit;

    if (IsValid(MainBase)) {
        MainBase->SetIfIsActivated(true);
    }
    
    GetWorldTimerManager().SetTimer(SecretPortalTimerHandle, this,
        &ATrueProject2GameModeBase::SpawnSecretPortal, SecretPortalSpawnSegs, false);
}

void ATrueProject2GameModeBase::HandleGameState() {
    if (IsValid(GameInstance)) {
        if (GameInstance->GetCurrentState() == 
            EGamePlayState::EPlaying) {
            // Reset all values

            // Spawn Main
            if (!MainIsSpawned) {
                SpawnMainBase();
                SpawnMain();
            }
            
            // Spawn Enemies overtime
            SpawnEnemiesRandomly();

        }
    }
}

/* Game State
Each time a new level open -> the game mode override -> call GetGameMode() in order to
process what is going to do
*/
/*
void ATrueProject2GameModeBase::OpenPreGameState() {
    if (IsValid(GameInstance)) {
        GameInstance->SetCurrentState(EGamePlayState::EPreparing);
        UGameplayStatics::OpenLevel(this, FName("TruePreGameLevel"));
    }
}
void ATrueProject2GameModeBase::OpenPlayingState() {
    if (IsValid(GameInstance)) {
        GameInstance->SetCurrentState(EGamePlayState::EPlaying);
        UGameplayStatics::OpenLevel(this, FName("TrueTheGameLevel"));
    }
}
void ATrueProject2GameModeBase::OpenPostGameState() {
    if (IsValid(GameInstance)) {
        // Open the level
        GameInstance->SetCurrentState(EGamePlayState::EGameOver);
        UGameplayStatics::OpenLevel(this, FName("TruePostGameLevel"));
    }
}*/

void ATrueProject2GameModeBase::PastAllPostGameStats() {
    // Total Time
    if (IsValid(GameInstance)) {
        GameInstance->SetTotalInGameDays(FMath::RoundToInt(CurrentDay));
        
        // in case the ending is activated without main dying
        if (IsValid(MainCharacter)) { 
            GameInstance->SetTotalDamageDealed(MainCharacter->GetTotalDamageDealed());
            GameInstance->SetTotalEnemiesKilled(MainCharacter->GetTotalEnemiesKilled());
            GameInstance->SetTotalXPLeanrt(MainCharacter->GetTotalXP());
            GameInstance->SetTotalDamageTaken(MainCharacter->GetTotalDamageTaken());
            GameInstance->SetTotalItemsCollected(MainCharacter->GetAmountArtifact());
        }
    }
}

// Check Time 
void ATrueProject2GameModeBase::CheckTime() {
    
    // Manage day/ night circle
    if (CurrentHour < nightStart) {
        bIsInMorning = false;
    }
    else {
        bIsInMorning = true;
    }

    HandleTime();
}

void ATrueProject2GameModeBase::HandleTime() {
    if (bIsInMorning) {
        // Refresh enemies list
        RefreshEnemiesList();

        // when night finish -> the day and difficulty also change
        UpdateDifficulty();

        // Debuff all enemies spawned
        DebuffAllDayEnemies();
        UpdateNightBuff();
    }
    else {
        // Buff to all enemies spawned -> detection, speed, damage, health
        BuffAllNightEnemies();
    }
}

void ATrueProject2GameModeBase::PlayBGM() {
    if (IsValid(GameInstance)) {
        if (GameInstance->GetCurrentState() ==
            EGamePlayState::EPlaying) {

            if (CurrentDay > SurviveDay / 2) {
                PlayCombatBGM();
            }
            else {
                PlayChillBGM();
            }
        }
        else {
            PlayChillBGM();
        }
    }
}

void ATrueProject2GameModeBase::PlayChillBGM() {
    if (IsValid(ChillBGMSoundCue)) {
        BGMComponent = UGameplayStatics::SpawnSound2D(GetWorld(),
            ChillBGMSoundCue);

        if (IsValid(BGMComponent)) {
            BGMComponent->OnAudioFinished.AddUniqueDynamic(this, &ATrueProject2GameModeBase::PlayBGM);
        }
    }
}

void ATrueProject2GameModeBase::PlayCombatBGM() {
    if (IsValid(CombatBGMSoundCue)) {
        BGMComponent = UGameplayStatics::SpawnSound2D(GetWorld(),
            CombatBGMSoundCue);

        if (IsValid(BGMComponent)) {
            BGMComponent->OnAudioFinished.AddUniqueDynamic(this, &ATrueProject2GameModeBase::PlayBGM);
        }
    }
}

// FOR NOW -> It does not reset the difficulties of already spawned enemies
void ATrueProject2GameModeBase::BuffAllEnemiesByDifficulty() {
    for (AEnemyClass* EnemyDelta : EnemiesSpawned) {
        if (IsValid(EnemyDelta)) {
            EnemyDelta->GetDifficultBuff(difficultyBuff);
        }
    }
}

void ATrueProject2GameModeBase::UpdateDifficulty() {
    difficultyBuff = difficultyBuff * difficultyModifier;
    if (spawnRate > minSpawnRate) {
        spawnRate = spawnRate * (1 / difficultyBuff);
    }
}

void ATrueProject2GameModeBase::BuffAllNightEnemies() {
    for (AEnemyClass* EnemyDelta : EnemiesSpawned) {
        if (IsValid(EnemyDelta)) {
            EnemyDelta->GetNightBuff(nightBuff);
        }
    }
}

void ATrueProject2GameModeBase::DebuffAllDayEnemies() {
    for (AEnemyClass* EnemyDelta : EnemiesSpawned) {
        if (IsValid(EnemyDelta)) {
            EnemyDelta->GetMorningDebuff(1 / nightBuff);
        }
    }
}

void ATrueProject2GameModeBase::UpdateNightBuff() {
    nightBuff = nightBuff * nightBuffModifier;
}

void ATrueProject2GameModeBase::RefreshEnemiesList() {
    TArray<AEnemyClass*> DeltaValidEnemies = {};
    for (AEnemyClass* EnemyDelta : EnemiesSpawned) {
        if (IsValid(EnemyDelta)) {
            DeltaValidEnemies.Add(EnemyDelta);
        }
    }
    EnemiesSpawned = DeltaValidEnemies;
}

// Main Stats
void ATrueProject2GameModeBase::SpawnMain() {
    // ***** Need to add logic about where spawn player and not just restart it
    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


    if (IsValid(MainBase)) {
        MainSpawnLocation = MainBaseLocation + MainBase->GetSpawnMainOffSet() + FVector(0.0f, 0.0f, MainHalfHeight);
    }

    if (IsValid(MainClass)) {
        MainCharacter = GetWorld()->SpawnActor<AMain>(MainClass, MainSpawnLocation,
            MainSpawnRotation, ActorSpawnParams);

        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

        if (IsValid(PlayerController) && IsValid(MainCharacter)) {
            PlayerController->Possess(MainCharacter);
            MainIsSpawned = true;
            MainCharacter->InitializeMainController();
        }
    }   
}

void ATrueProject2GameModeBase::SpawnMainBase() {
    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    if (IsValid(MainBaseClass)) {
        MainBase = GetWorld()->SpawnActor<AMapCompMainBase>(MainBaseClass, MainBaseLocation,
            MainBaseRotation, ActorSpawnParams);
    }
}

void ATrueProject2GameModeBase::SpawnSecretPortal() {
    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    GenerateRandomLocation();
    SecretPortalLocation = RandomLocationToSpawn;

    if (IsValid(SecretPortalClass)) {
        SecretPortal = GetWorld()->SpawnActor<AMapCompSecretPortal>(SecretPortalClass, SecretPortalLocation,
            SecretPortalRotation, ActorSpawnParams);

        if (IsValid(SecretPortal)) {
            SecretPortalSpawnSound();
            SecretPortal->SetIfIsActivated(true);
        }
    }
}

void ATrueProject2GameModeBase::GetMainLocation() {
    if (IsValid(MainCharacter)) {
        PlayerLocation = MainCharacter->GetPlayerPosition();
    }
}
void ATrueProject2GameModeBase::GetMainRotation() {
    if (IsValid(MainCharacter)) {
        PlayerRotation = MainCharacter->GetPlayerRotation();
    }
}

bool ATrueProject2GameModeBase::GetIsMorning() {
    return bIsInMorning;
}
float ATrueProject2GameModeBase::GetCurrentSecond() {
    return CurrentSecond;
}
float ATrueProject2GameModeBase::GetCurrentMinute() {
    return CurrentMinute;
}
float ATrueProject2GameModeBase::GetCurrentHour() {
    return CurrentHour;
}
float ATrueProject2GameModeBase::GetCurrentDay() {
    return CurrentDay;
}

// Spawn Enemies
void ATrueProject2GameModeBase::SpawnEnemiesRandomly() {
    GetMainLocation();
    GetMainRotation();

    GenerateRandomLocation();
    if (CheckRandomLocationValid()) {
        SpawnEnemy();
    }

    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, 
        &ATrueProject2GameModeBase::SpawnEnemiesRandomly, spawnRate, false);
}

void ATrueProject2GameModeBase::GenerateRandomLocation() {
    NavArea = FNavigationSystem::
        GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if (NavArea) {
        NavArea->K2_GetRandomReachablePointInRadius(GetWorld(),
            PlayerLocation, RandomLocationToSpawn, maxRadio);
    }

    RandomLocationToSpawn = RandomLocationToSpawn + FVector(0.0f, 0.0f, SpawnHeightOffset);
}

bool ATrueProject2GameModeBase::CheckRandomLocationValid() {
    float DistOfRandom = (PlayerLocation - RandomLocationToSpawn).Size();

    return minRadio <= DistOfRandom;
}

void ATrueProject2GameModeBase::SpawnEnemy() {
    // Change the rotation -> should be spawnLocation - ActorLocation
    // have to spawn based on rarity just like miniworld
    AEnemyClass* aRandomEnemy = GetRandomEnemy();

    // When a enemy spawn -> update its stats by difficulty and night if it is night
    if (IsValid(aRandomEnemy)) {
        EnemiesSpawned.Add(aRandomEnemy);

        aRandomEnemy->GetDifficultBuff(difficultyBuff);

        if (!bIsInMorning) {
            aRandomEnemy->GetNightBuff(nightBuff);
        }
    }
}

AEnemyClass* ATrueProject2GameModeBase::GetRandomEnemy() {
    
    EEnemyRarity EnemyRarity = GenerateRandomEnemyRarity();
    AEnemyClass* theRandomEnemy;

    switch (EnemyRarity) {
        case EEnemyRarity::ENormal: {
            theRandomEnemy = GenerateNormalEnemy();
            break;
        }
        case EEnemyRarity::ESpecial: {
            theRandomEnemy = GenerateSpecialEnemy();
            break;
        }
        case EEnemyRarity::EElite: {
            theRandomEnemy = GenerateEliteEnemy();
            break;
        }
        case EEnemyRarity::EBoss: {
            theRandomEnemy = GenerateBossEnemy();
            break;
        }
        default:
        {
            theRandomEnemy = GenerateNormalEnemy();
            break;
        }
    }

    return theRandomEnemy;
}

EEnemyRarity ATrueProject2GameModeBase::GenerateRandomEnemyRarity() {
    int Chance = FMath::RandRange(1, 100);
    
    /*
    * 60% -> normal enemy
    * 30% -> special enemy
    * 9% -> elite enemy
    * 1% -> boss enemy
    * 0% -> giga boss enemy
    */
    if (Chance < 50) {
        return EEnemyRarity::ENormal;
    }
    else if (Chance < 75) {
        return EEnemyRarity::ESpecial;
    }
    else if (Chance < 90) {
        return EEnemyRarity::EElite;
    }
    else {
        return EEnemyRarity::EBoss;
    }
}

/* Rarity per enemy
Normal -> 12
1: Bird -> Normal
2: Parasite Baby -> Normal
3: Parasite Rookie -> Normal
5: Robot Blade -> Normal
6: Human pistol -> Nomral
7: Human shotgun -> Normal
8: Boar -> Normal
22: Cultist -> Normal
13: Zombie -> Normal
25: Sandworm -> Normal
28: Wasp -> Normal
30: Attack Drone -> Normal

Special -> 7
9: Robot girl -> Special
11: Robot executor -> Special
15: Bat -> Special
19: Hunter sniper -> Special
27: Swat -> Special
29: Scorpio -> Special
31: Rabbit -> Special

Elite -> 3
4: Parasite Ultimate -> Elite
10: Robot Papu -> Elite
24: Minibot -> Elite

Boss -> 1
26: Spider queen -> Boss
*/

AEnemyClass* ATrueProject2GameModeBase::GenerateNormalEnemy() {
    int chosenNumber = FMath::RandRange(1, normalEnemy);

    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


    switch (chosenNumber) {
        case 1: {
            if (IsValid(EnemyBirdClass)) {
                return GetWorld()->SpawnActor<AEnemy1_Bird>(EnemyBirdClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 2: {
            if (IsValid(EnemyParasiteBabyClass)) {
                return GetWorld()->SpawnActor<AEnemy2_Parasite_Baby>(EnemyParasiteBabyClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 3: {
            if (IsValid(EnemyZombieClass)) {
                return GetWorld()->SpawnActor<AEnemy13_Zombie>(EnemyZombieClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 4: {
            if (IsValid(EnemyCultistClass)) {
                return GetWorld()->SpawnActor<AEnemy22_Cultist>(EnemyCultistClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 5: {
            if (IsValid(EnemySandBoxClass)) {
                return GetWorld()->SpawnActor<AEnemy25_Sandworn>(EnemySandBoxClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 6: {
            if (IsValid(EnemyWaspClass)) {
                return GetWorld()->SpawnActor<AEnemy28_Wasp>(EnemyWaspClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 7: {
            if (IsValid(EnemyDroneClass)) {
                return GetWorld()->SpawnActor<AEnemy30_AttackDrone>(EnemyDroneClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
    }
    return GetWorld()->SpawnActor<AEnemy1_Bird>(EnemyBirdClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}

AEnemyClass* ATrueProject2GameModeBase::GenerateSpecialEnemy() {
    int chosenNumber = FMath::RandRange(1, specialEnemy);

    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    switch (chosenNumber) {
        case 1: {
            if (IsValid(EnemyRobotGirlClass)) {
                return GetWorld()->SpawnActor<AEnemy9_Robot_Girl>(EnemyRobotGirlClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 2: {
            if (IsValid(EnemyExucutorClass)) {
                return GetWorld()->SpawnActor<AEnemy11_Robot_Executor>(EnemyExucutorClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 3: {
            if (IsValid(EnemyBatClass)) {
                return GetWorld()->SpawnActor<AEnemy15_Bat_1>(EnemyBatClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 4: {
            if (IsValid(EnemyHunterClass)) {
                return GetWorld()->SpawnActor<AEnemy19_Hunter_Sniper>(EnemyHunterClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 5: {
            if (IsValid(EnemySwatClass)) {
                return GetWorld()->SpawnActor<AEnemy27_Swat>(EnemySwatClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 6: {
            if (IsValid(EnemyScorpioClass)) {
                return GetWorld()->SpawnActor<AEnemy29_Scorpio>(EnemyScorpioClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
    }
    return GetWorld()->SpawnActor<AEnemy29_Scorpio>(EnemyScorpioClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}

AEnemyClass* ATrueProject2GameModeBase::GenerateEliteEnemy() {
    int chosenNumber = FMath::RandRange(1, eliteEnemy);

    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    switch (chosenNumber) {
        case 1: {
            if (IsValid(EnemyPapuClass)) {
                return GetWorld()->SpawnActor<AEnemy10_Robot_Papu>(EnemyPapuClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
        case 2: {
            if (IsValid(EnemyMiniBotClass)) {
                return GetWorld()->SpawnActor<AEnemy24_MiniBot>(EnemyMiniBotClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
            }
            break;
        }
    }

    return GetWorld()->SpawnActor<AEnemy24_MiniBot>(EnemyMiniBotClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}

AEnemyClass* ATrueProject2GameModeBase::GenerateBossEnemy() {
    int chosenNumber = FMath::RandRange(1, bossEnemy);

    FActorSpawnParameters ActorSpawnParams;
    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    if (IsValid(EnemySpiderQueenClass)) {
        return GetWorld()->SpawnActor<AEnemy26_Spider_Queen>(EnemySpiderQueenClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
    }

    return GetWorld()->SpawnActor<AEnemy26_Spider_Queen>(EnemySpiderQueenClass, RandomLocationToSpawn, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
}