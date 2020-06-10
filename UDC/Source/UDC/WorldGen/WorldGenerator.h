// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldGenerator.generated.h"


UENUM(BlueprintType)
enum class ERoomType : uint8 
{
	Spawn	UMETA(DisplayName="Spawn"),
	Normal	UMETA(DisplayName = "Normal"),
	Boss	UMETA(DisplayName = "Boss"),
};


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
	UPROPERTY(BlueprintReadOnly)
		ERoomType roomType;
	UPROPERTY(BlueprintReadOnly)
		int32 numberOfEnemies;
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


USTRUCT(BlueprintType)
struct FCorridorStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		FVector from;
	UPROPERTY(BlueprintReadOnly)
		FVector to;

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
		int maxEnemiesRoom;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
	TArray<FRoomStruct> rooms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
	TArray<FRoomConnection> roomConnections;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
	TArray<FCorridorStruct> corridors;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FCorridorStruct> angledCorridors;

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void SpawnRooms();
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void CreateCorridors();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		FVector GetRandomSpawn(FVector roomPos, FVector Size);

protected:

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:	
	
	int countTriesplacing;
	int corridorWidth;

	void TryPlaceRoom();
	FRoomStruct GenerateRoom();
	bool TooManyTries();
	bool isRoomOverlapping(FRoomStruct existingRoom, FRoomStruct newRoom);
	void CreateSpanningTree();
	FRoomConnection FindMinimalDistance(TArray<FVector> rest, TArray<FVector> done);
	void FindCorridorOverlap(FRoomConnection connection);

	void ChooseRoomTypes();


};
