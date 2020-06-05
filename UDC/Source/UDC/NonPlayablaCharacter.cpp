// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayablaCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
ANonPlayablaCharacter::ANonPlayablaCharacter()
{
	DisplayName = "Enemy";
	bDead = false;
	HenkPoints = 750.0f;
	HP_Max = 1000.0f;
	HP_Heal = 10.0f;
	ManaPoints = 80.0f;
	MP_Max = 80.0f;
	MP_Recharge = 10.0f;
	Coins = 0;
	Is_Attacked = false;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANonPlayablaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANonPlayablaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANonPlayablaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ANonPlayablaCharacter::TakeDamage(float Damage)
{
	bool playAnimation = false;

	if (Is_Attacked == false) {
		Is_Attacked = true;
		HenkPoints -= Damage;
		
		GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &ANonPlayablaCharacter::onTimerEnd, 1.667f, false);
		playAnimation = true;
	}

	if (HenkPoints <= 0) {
		bDead = true;
		playAnimation = false;
	}

	return playAnimation;
}

void ANonPlayablaCharacter::onTimerEnd()
{
	Is_Attacked = false;
}

