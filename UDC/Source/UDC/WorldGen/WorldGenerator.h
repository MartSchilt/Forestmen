// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldGenerator.generated.h"


USTRUCT(BlueprintType)
struct FRoomStruct
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
		int32 roomNumber;
	UPROPERTY(BlueprintReadOnly)
		FVector roomPosition;
	UPROPERTY(BlueprintReadOnly)
		FVector roomSize;
	UPROPERTY(BlueprintReadOnly)
		FVector roomCenter;
	UPROPERTY(BlueprintReadOnly)
		TArray<FVector> roomEntrances;

};


USTRUCT(BlueprintType)
struct FRoomConnection
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		int from;
	UPROPERTY(BlueprintReadOnly)
		int to;
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDC_API UWorldGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWorldGenerator();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int mapY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int mapX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int tileSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int maxNumberOfRooms;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int roomSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int maxNumberOfRetries;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int minDistanceBetweenRooms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
	TArray<FRoomStruct> rooms;
	TArray<FRoomConnection> roomConnections;

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void SpawnRooms();

protected:

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:	
	
	int countTriesplacing;

	void TryPlaceRoom();
	FRoomStruct GenerateRoom();
	bool TooManyTries();
	bool isRoomOverlapping(FRoomStruct existingRoom, FRoomStruct newRoom);
	void CreateSpanningTree();
	FRoomConnection FindMinimalDistance(TArray<FVector> rest, TArray<FVector> done);


};
