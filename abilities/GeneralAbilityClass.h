// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DataContainer/Data_AbilityRequiredInfo.h"
#include "../DataContainer/Data_AbilityFeedBackInfo.h"
#include "../components/FrenzyComponent.h"
#include "../components/CalmComponent.h"
#include "../components/DamageComponent.h"
#include "../components/XPComponent.h"
#include "../All_Enemies/EnemyClass.h"
#include "Kismet/GameplayStatics.h"

#include "MediaPlayer.h"
#include "MediaSoundComponent.h"
#include "MediaSource.h"

#include "../Main.h"

#include "../Common_Enums.h"
#include "GeneralAbilityClass.generated.h"

/*
Upgrade == = Customeze != Level Up
	- Pros: more creative, allow to do stupid things
	- Cons: easy to braek the game -> but who cares right.

	- The idea is basically there is no limit on leveling up ability
		* player can level the ability whatever they want, and it will work, 
		beacuse it is just a funcion of the respected component 
		* What is change is the level of container, which is going to increase by 
		each level up.
	
	- Upgrading abilities can be only be done in menu, but it can get xp 2 forms
		* Get xp passively by using the abilities
		* Get xp by spending the memory of protagonist -> bad ending
	- Upgrading stats of character
		* In game by collectings some powers up
		* Menu by spending memory -> bad ending
*/

/* Limitations:
* Test -> infinite
* Weapon -> there is not magazine concept (has infinite bullet per magazine)
*			what have to define is the rate of fire.
* Abilities -> has no cooldown, the require is frenzy/calm and depend on ability
*/
/* All abilities and its code (double digits)
	Weapon category is the basic set, players always have it
	Others abilities are free to choose -> there is not other basic attack
0 -> Category_test
1 -> Category_Weapon (Basic Weapon)
	1 -> Pistol (r == reload, left-click = fire, right-click == zoom)
		Upgrade:
			- more damage/bullet
			- fire rate
	2 -> Shotgun (r == reload, left-click = fire, right-click == zoom)
		Upgrade: 
			- more damage
			- fire rate
	3 -> Sniper (r == reload, left-click = fire, right-click == zoom)
		Upgrade:
			- more damage
			- fire rate
	4 -> Blade (r == "mini ult", left-click = point, right-click == slice)
		Upgrade:
			- more damage
			- more dps/ cooldown
			- more range
	5 -> None (r == "mini ult", left-click = point, right-click == slice)
		To be investigate
		Upgrade:
			- 
	6 -> Alien Gun (r == reload, left-click = fire, right-click == rayos)
2 -> Category_Bomb -> on matter what is FHitResult
	1 -> Throw Bomb -> do radial damage 
		Upgrade:
			- more damage
			- more radial
		Programming:	1- get the target location
						2- appear a sphere box collision that do raidal damage

	2 -> put a bomb baiter -> charm everone to the bomb
		Upgrade:
			- more damage
			- more time charm
			- more radial
		Programming:	1- get target location
						2- spawn an charm actor with overlapping box
						   every enemies who got into the overlapping box get status 
						   charm and walk to the actor location and attack it
						3-  destroy if health got <= 0

	3 -> Break wall bomb 
		Programming:	1- to be investigate

3 -> Category_Hilo
	1 -> Wire trap -> choose 2 points and connect them
		Upgrade:
			- not do damage to yourself
			- more points
			- more distance between points
	2 -> 
4 -> Category_Shadow
	1 -> Shadow solder -> the amount of stats cost == the height/ volume of the object (the damage = ratio of frenzy and height * total enemmy health)
		Upgrade:
			- max height limit
			- cooldown
		Programming:	1- get the target FHitResult -> check if it is an enemy
						2- get the enemy height and compare if is able to cast the ability
						3- if it is ok, then enemy stop moving and spawn a shadow solder to
	2 -> Shadow travel
		Upgrade:
			- less cost
			- more time duration
		Programming:	1- every light in the map should have an sphere collision
						2- every actors overlapped in these spheres collision get bool "inTheDark"
						3- if main is in the dark -> is able to use shadow travel
						4- can not do any other action when it is in shadow travel
						5- can not be seen by enemy nethier by main its self
						6- the ability is able to cancel by:
							6.1- touch the ability again
							6.2- get in to the bright side (not inTheShadow)

5 -> Category_Dimension
	1 -> reverse all projectiles
		Upgrade:
			- more radial
			- 
		Programming:	1- create an sphere around player with an overlap collision
						2- collect every projectile in the sphere 
						3- reverse their direction entirely and is able to hit enemies.

	2 -> teleport -> if front of character has tp point, then tp, if not, put tp if is allowed
		Upgrade:
			- allow to put tp point in distance
			- max range possible
			- more magazine -> does not make sense if there is no cooldown
		Programming:	1- ability get the FHitResultLocation
						2- Have a tpPoint that represent the tp place
						3- if the hitResult is enemytype -> attach the tpPoint to enemy
						   otherwise -> put the tpPoint in the place
						4- the tpPoint is just an actor mesh, which contain the its location
						5- all toPoint meshes are transparent for character, so if there is any tpPoint in front
							of the player -> able to tp
						6- select -> tp
	3 -> switch dimension -> open a self place, which contain some minigame like cooking... a little rest
		Upgrade:
			- more funcionalities in space
		Programming:	1- It is a totally level/map which save by every single player run
						2- 

6 -> Category_Time
	1 -> bullet time
		Upgrade:
			- more time
			- less cost
	2 -> flash -> acelerate self dilation
		Upgrade:
			- more time
			- less cost
	3 -> go back 5 seg ago
		Upgrade:
			ni idea
7 -> Category_Hacker
	1 -> paradise all enemies
		- paradise more duration
	2 -> control one enemy
		- more time controlling duration
	3 -> open command
		- more command allowed:
			a) 
			b) 
			c) 
8 -> Category_Animal/ Summoner
	1 -> eagle -> all info -> show all enemies weekpoint cleary -> if it got hitten, extreme damage
		Upgrade:
			- more time
	2 -> big foot from the sky, crash
		Upgrade:
			- acumulate (other way to say cooldown)
	3 -> rabbit (50/ 50 a killer rabit)
		Upgrade:
			- rabit do not kill summoner himself
			- more probability of spawning killer rabit
9 -> Category_Tool (hard to program, will comflic, maybe add more input)
	1 -> Open a random item box, could open:
		2 -> almost trash 
		3 -> alien gun-> one shot all enemy touched 
		4 -> jump show -> jump very heigh, and crash the ground
		5 -> 
*/


UCLASS(Blueprintable, BlueprintType)
class TRUEPROJECT2_API AGeneralAbilityClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralAbilityClass(const class FObjectInitializer& ObjectInitializer);

/*
there are rewards for character by activating, it should be struct which everyone recognize it
in order to return multiple values.
Maybe the parameters that Activate receive shuold be also a struct which contain everything
*/ 

/*
function activate:
	1- Check the basic requirement
		- Player stats, BA chosen, 
		- If the target is enemy/ floor/ null
	2- activate ability, no level exist, ability should know its level
*/

protected:
	// for game progression
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		bool Locked;

	// Ability Info For Displaying
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		class UTexture2D* AbilityImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		class UMediaSource* AbilityVideoSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		class UMediaSoundComponent* AbilityVideoSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		FString AbilityNameEng;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		FString AbilityNameChi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		FString AbilityNameSpn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		FString AbilityDiscriptionEng;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		FString AbilityDiscriptionChi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display Stat")
		FString AbilityDiscriptionSpn;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Hit Effect Control")
		void SpawnHitEffectNiagara(FHitResult TheHit);

	// stats needed -> should be clasify or all of them should be calculate and not a flat point
	// Damage Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		class UDamageComponent* Damage;

	// Frenzy Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		class UFrenzyComponent* FrenzyCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		class UFrenzyComponent* FrenzyReward;
	// Calm Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		class UCalmComponent* CalmCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		class UCalmComponent* CalmReward;
	// XP Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		class UXPComponent* XP;
	// Feedback container
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability", meta = (AllowPrivateAccess = "true"))
		class UData_AbilityFeedBackInfo* feedBackContainer;

	float radioImpact = 0.0f;
	float duration = 0.0f;
	float range = 0.0f;
	float moveSpeedReward = 0.0f;
	bool doSelfDamage = false;

public:
	// Return Display Stats
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		bool IsAbilityLocked();

	// Ability Info For Displaying
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		UTexture2D* GetAbilityImage();
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		FString GetAbilityName(ELanguageSelected ALanguage);
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		FString GetAbilityDiscription(ELanguageSelected ALanguage);
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		UMediaSource* GetAbilityVideoSource();
	UFUNCTION(BlueprintCallable, Category = "Display Stat")
		UMediaSoundComponent* GetAbilityVideoSound();

	// evaluate the requirement of the ability -> will have lots of parameters 
	virtual bool AbilityRequirement(UData_AbilityRequiredInfo* requiredInfo);

	// calculate stats to store in components -> all calculation is responsability of each components

	// Activate the ability in general -> the reception of ability system
	UData_AbilityFeedBackInfo* Activate(UData_AbilityRequiredInfo* requiredInfo);

	// activate ability based on lv, maybe each lv act totally different
	virtual void ActivateAbilityEffect(UData_AbilityRequiredInfo* requiredInfo);

	void CreateFeedBackContainer();

	void CustomizeStatsPerAbility(float VALUEbaseDamage,
								float VALUECritChance,
								float VALUECritMultiplier,
								float VALUEfireRate,
								float VALUEradioImpact,
								float VALUEduration,
								float VALUErange,
								bool VALUEdoSelfDamage,
								float VALUEbaseFrenzyCost,
								float VALUEbaseFrenzyReward,
								float VALUEbaseCalmCost,
								float VALUEbaseCalmReward,
								float VALUEmoveSpeedReward,
								int VALUEbaseXP);

	// overall functions/ common abilities functions
	virtual void ApplyDamageToEnemy(AEnemyClass* EnemySelected, float TheDamage, UData_AbilityRequiredInfo* requiredInfo);

	// calculate per ability -> override
	virtual float CalculateGeneralDamage(UData_AbilityRequiredInfo* requiredInfo);

	// calculate per ability -> override
	virtual float CalculateSpecialDamage(UData_AbilityRequiredInfo* requiredInfo);

	// setter and getter
	float GetAbilityFireRate();
};

