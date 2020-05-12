// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayablaCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
ANonPlayablaCharacter::ANonPlayablaCharacter()
{
	bDead = false;
	HenkPoints = 100.0f;
	HP_Max = 100.0f;
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Timer is up"));
	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, this, &ANonPlayablaCharacter::onTimerEnd, 5.f, false);
	
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

void ANonPlayablaCharacter::TakeDamage(float Damage)
{
	if (!Is_Attacked) {
		Is_Attacked = true;
	}
}

void ANonPlayablaCharacter::onTimerEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Timer is up"));
}

