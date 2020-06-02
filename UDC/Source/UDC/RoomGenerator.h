// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RoomGenerator.generated.h"



// Struct for  saving the info per room
USTRUCT(BlueprintType)
struct FRoomData
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	int32 roomNumber;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> entrancePositions;

	UPROPERTY(BlueprintReadOnly)
	FVector roomPosition;

	UPROPERTY(BlueprintReadOnly)
	FVector roomSize;

	UPROPERTY(BlueprintReadOnly)
	FRotator rotation;
	UPROPERTY(BlueprintReadOnly)
	FVector middle;


};


USTRUCT(BlueprintType)
struct FCorridor
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	int from;
	UPROPERTY(BlueprintReadOnly)
	int to;
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDC_API URoomGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URoomGenerator();

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
		int distanceBetweenRooms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FRoomData> roomsData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FCorridor> Corridors;

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		float GetRandomRotation();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void TryPlaceRoom();
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		bool tooManyTries() const;
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void CreateSpanningTreeV2();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void CreateCorridor(FCorridor corridor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FVector> RoomStart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FVector> RoomEnd;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FVector> RoomCorridorStart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FVector> RoomCorridorEnd;


protected:
	// Called when the game starts

public:	
	// Called every frame
	int countTriesPlacing;

	TArray<FVector> GenerateRoom() const;
	bool isRoomOverlapping(FVector Room1Pos, FVector Room1Size, FVector Room2Pos, FVector Room2Size) const;
	TArray<int> findMinimalDistance(TArray<FVector> rest, TArray<FVector> completed, TMap<FVector, int> EntranceMap);
	TArray<int> FindMinimalDistanceV2(TArray<FVector> rest, TArray<FVector> completed);
};
