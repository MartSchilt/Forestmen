// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CustomLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class UDC_API ACustomLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		float maxGridSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		float roomSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		float maxRoomScale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		float minRoomScale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int maxNumberOfRooms;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
	int numberOfRetryPlacingRoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FName> StreamingLevelNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FVector> roomPositions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FVector> roomSizes;

	ACustomLevelScriptActor();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		FName GetStreamingLevelName();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		float GetRandomRotation(); 
	
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void TryPlaceRoom();
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		bool tooManyTries() const;
	
protected:
	// Called when the game starts
	// virtual void BeginPlay() override;

public:
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

private:
	int countTriesPlacing;

	TArray<FVector> GenerateRoom() const;
	bool isRoomOverlapping(FVector Room1Pos, FVector Room1Size, FVector Room2Pos, FVector Room2Size) const;
};
