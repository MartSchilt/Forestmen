// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActor.h"
#include "PlayerCharacter.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
ATimeActor::ATimeActor()
{
	Seconds = 0;
	Minutes = 0;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATimeActor::BeginPlay()
{
	Super::BeginPlay();
	//FTimerHandle object, this, the function we call every 1.0f seconds, the delay between calls, idk, delay before we begin with the loop
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATimeActor::Timer, 1.0f, true, 1.0f);
}

// Called every frame
void ATimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATimeActor::Timer()
{
	Seconds++;
	if (Seconds == 60) {
		Minutes++;
		Seconds = 0;
	}
}