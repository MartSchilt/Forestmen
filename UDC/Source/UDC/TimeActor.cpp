// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActor.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
ATimeActor::ATimeActor()
{
	Seconds = 0;
	Minutes = 2;
	TickDown = true;
	Count = 6;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATimeActor::BeginPlay()
{
	Super::BeginPlay();
	//FTimerHandle object, this, the function we call every 1.0f seconds, the delay between calls, idk, delay before we begin with the loop
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATimeActor::Timer, 0.2f, true, 1.0f);
}

// Called every frame
void ATimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATimeActor::Timer()
{
	// Mooie code
	
	// If enemies alive
	if (Count > 0)
	{
		// If timer hasn't ended yet
		if (TickDown) {
			Seconds--;
			if (Seconds < 0) {
				Minutes--;
				if (Minutes < 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Time's up"));
					
					TickDown = false;
				}
				else if (Minutes >= 0)
				{
					Seconds = 59;
					UE_LOG(LogTemp, Warning, TEXT("Time: %d : %d. Count: %d"), Minutes, Seconds, Count);
				}
			} else
			{
				UE_LOG(LogTemp, Warning, TEXT("Time: %d : %d. Count: %d"), Minutes, Seconds, Count);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Return to main menu"));
			GetWorldTimerManager().ClearTimer(MemberTimerHandle);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You done did it"));
	}
}

void ATimeActor::Decrease()
{
	Count = 2;
}