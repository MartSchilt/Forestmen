// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"
#include "Engine/LevelStreamingDynamic.h"

// Sets default values for this component's properties
UWorldGenerator::UWorldGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set default values for world generation

	// Size of the map
	this->mapY = 500;
	this->mapX = 500;

	// Size of one tile in UE, when objects are placed in the world the vectors should be multiplied by this value
	this->tileSize = 100;

	// Max amount of rooms in our world
	this->maxNumberOfRooms = 20;

	// Size of 1 room in X and Y direction
	this->roomSize = 50;

	// Distance between rooms so they won't spawn next to eachother
	this->minDistanceBetweenRooms = 15;

	// Number of retries if this number is hit the world gen will stop spawning rooms
	this->maxNumberOfRetries = 100;
	this->countTriesplacing = 0;

}






void UWorldGenerator::SpawnRooms()
{

	while (!TooManyTries())
	{
		TryPlaceRoom();
	}

	CreateSpanningTree();



}

// Called every frame
void UWorldGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWorldGenerator::TryPlaceRoom()
{

	FRoomStruct newRoom = GenerateRoom();

	for (FRoomStruct existingRoom : this->rooms)
	{
		if (isRoomOverlapping(existingRoom, newRoom))
		{
			this->countTriesplacing++;
			return;
		}
	}

	newRoom.roomNumber = this->rooms.Num();
	newRoom.roomCenter = FVector(newRoom.roomPosition.X + newRoom.roomSize.X / 2, newRoom.roomPosition.Y + newRoom.roomSize.Y / 2, 0);

	rooms.Add(newRoom);

	return;
}

// Generate a new roomStruct
FRoomStruct UWorldGenerator::GenerateRoom()
{

	FVector pos;
	FVector size = FVector(this->roomSize, this->roomSize, 0);


	// Make sure the room doesn't spawn outside of the map
	int xMax = this->mapX - size.X;
	int yMax = this->mapY - size.Y;

	int x = FMath::RandRange(0, xMax);
	int y = FMath::RandRange(0, yMax);

	pos = FVector(x, y, 0);

	FRoomStruct tempRoom = FRoomStruct();
	tempRoom.roomPosition = pos;
	tempRoom.roomSize = size;

	return tempRoom;
}


// Checks if there are too many rooms or tries
bool UWorldGenerator::TooManyTries()
{

	if ((this->rooms.Num() != this->maxNumberOfRooms) && (this->countTriesplacing < this->maxNumberOfRetries))
	{
		return false;
	}

	return true;
}


// Checks whether 2 Rooms overlap with a minimun distance between them
bool UWorldGenerator::isRoomOverlapping(FRoomStruct existingRoom, FRoomStruct newRoom)
{

	FVector Room1Pos = existingRoom.roomPosition;
	FVector Room1Size = existingRoom.roomSize;
	FVector Room2Pos = newRoom.roomPosition;
	FVector Room2Size = newRoom.roomSize;

	if (Room1Pos.X >= (Room2Pos.X + Room2Size.X + this->minDistanceBetweenRooms) || Room2Pos.X >= (Room1Pos.X + Room1Size.X + this->minDistanceBetweenRooms))
		return false;
	if ((Room1Pos.Y + Room1Size.Y + this->minDistanceBetweenRooms) <= Room2Pos.Y || (Room2Pos.Y + Room2Size.Y + this->minDistanceBetweenRooms) <= Room1Pos.Y)
		return false;

	return true;

}

void UWorldGenerator::CreateSpanningTree()
{
	
	TArray<FVector> rest;
	TArray<FVector> done;
	
	for (FRoomStruct room : rooms)
	{
		FVector center = room.roomCenter;
		center.Z = room.roomNumber;

		rest.Add(center);
	}

	done.Add(rest[0]);
	rest.RemoveAt(0);

	while (rest.Num() != 0)
	{
		FRoomConnection connection = FindMinimalDistance(rest, done);

		FRoomConnection corridor = FRoomConnection();
		corridor.from = done[connection.from].Z;
		corridor.to = rest[connection.to].Z;

		done.Add(rest[connection.to]);
		rest.RemoveAt(connection.to);


		this->roomConnections.Add(corridor);
	}




}

FRoomConnection UWorldGenerator::FindMinimalDistance(TArray<FVector> rest, TArray<FVector> done)
{

	float minDist = MAX_FLT;
	FRoomConnection ret;

	int counterDone = 0;
	for (FVector posDone : done)
	{
		int counterRest = 0;
		for(FVector posRest : rest)
		{
			float dist = FVector::Dist(posDone, posRest);

			if (dist < minDist)
			{
				minDist = dist;
				ret.from = counterDone;
				ret.to = counterRest;
			}
			counterRest++;
		}
		counterDone++;
	}

	return ret;
}

