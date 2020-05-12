// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActor.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
int seconds;
int minutes;
bool tickDown;

// Sets default values
ATimeActor::ATimeActor()
{
	seconds = 00;
	minutes = 1;
	tickDown = true;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATimeActor::BeginPlay()
{
	Super::BeginPlay();
	//FTimerHandle object, this, the function we call every 1.0f seconds, the delay between calls, idk, delay before we begin with the loop
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATimeActor::CallThis, 0.1f, true, 1.0f);

}

// Called every frame
void ATimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATimeActor::CallThis()
{
	while (tickDown) {
		seconds--;
		if (seconds < 1) {
			minutes--;
			if (minutes < 0)
			{
				tickDown = 1;
				UE_LOG(LogTemp, Warning, TEXT("Time's up"));
				break;
			}
			else
			{
				seconds = 59;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Time: %d : %d"), minutes, seconds);

		if (!tickDown)
		{
			UE_LOG(LogTemp, Warning, TEXT("Go to main menu and delete actor"));
			//Destroy(this);
		}
	}
}


