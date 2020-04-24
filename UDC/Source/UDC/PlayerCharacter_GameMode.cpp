// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter_GameMode.h"
#include "GameFramework/Actor.h"

APlayerCharacter_GameMode::APlayerCharacter_GameMode() {
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter_GameMode::BeginPlay() {
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayerCharacter_GameMode::SpawnPlayerRecharge, FMath::RandRange(2, 5), true);
}

void APlayerCharacter_GameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APlayerCharacter_GameMode::SpawnPlayerRecharge()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	// Don't worry about the red line, it works when building
	GetWorld()->SpawnActor(PlayerRecharge, &SpawnPosition, &SpawnRotation);
}
