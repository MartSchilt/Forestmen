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
	this->mapY = 250;
	this->mapX = 250;

	// Size of one tile in UE, when objects are placed in the world the vectors should be multiplied by this value
	this->tileSize = 100;

	// Max amount of rooms in our world
	this->maxNumberOfRooms = 6;

	// Size of 1 room in X and Y direction
	this->roomSize = 50;
	this->corridorWidth = 4;

	// Distance between rooms so they won't spawn next to eachother
	this->minDistanceBetweenRooms = 4;

	// Number of retries if this number is hit the world gen will stop spawning rooms
	this->maxNumberOfRetries = 100;
	this->countTriesplacing = 0;

	this->maxEnemiesRoom = 6;
}

// Called every frame
void UWorldGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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

void UWorldGenerator::CreateCorridors()
{
	for (FRoomConnection connection : this->roomConnections)
	{
		FindCorridorOverlap(connection);
	}
}

FVector UWorldGenerator::GetRandomSpawn(FVector roomPos, FVector Size)
{
	// Make sure the enemies dont spawn at the corner of the room
	roomPos.X += 2;
	roomPos.Y += 2;

	Size.Y -= 4;
	Size.X -= 4;

	int x = FMath::RandRange(roomPos.X, roomPos.X + Size.X);
	int y = FMath::RandRange(roomPos.Y, roomPos.Y + Size.Y);

	// Z must be 1 else the enemie will spawn in the ground
	FVector ret = FVector(x, y, 1);

	return ret;
}


void UWorldGenerator::FindCorridorOverlap(FRoomConnection connection)
{
	FRoomStruct from = this->rooms[connection.from];
	FRoomStruct to = this->rooms[connection.to];

	int ax1 = from.roomPosition.X;
	int ax2 = from.roomPosition.X + from.roomSize.X;

	int ay1 = from.roomPosition.Y;
	int ay2 = from.roomPosition.Y + from.roomSize.Y;

	int bx1 = to.roomPosition.X;
	int bx2 = to.roomPosition.X + to.roomSize.X;

	int by1 = to.roomPosition.Y;
	int by2 = to.roomPosition.Y + to.roomSize.Y;

	int max = FMath::Max(ax1, bx1);
	int min = FMath::Min(ax2, bx2);

	// Check overlap x;
	if (max <= min && (min - max) >= this->corridorWidth)
	{
		//int x = min - (min - max) / 2;
		int x = max;
		FCorridorStruct temp = FCorridorStruct();

		if (ay1 < by1)
		{
			temp.from = FVector(x, ay2, 0);
			temp.to = FVector(x, by1, 0);
		}
		else
		{
			temp.from = FVector(x, by2, 0);
			temp.to = FVector(x, ay1, 0);
		}

		this->corridors.Add(temp);

		for (int i = 0; i < 3; i++)
		{
			temp.from.X++;
			temp.to.X++;
			this->corridors.Add(temp);
		}

		return;
	}

	// Check overlap y
	max = FMath::Max(ay1, by1);
	min = FMath::Min(ay2, by2);

	if (max <= min && (min - max) >= this->corridorWidth)
	{
		int y = max;

		FCorridorStruct temp = FCorridorStruct();
		if (ax1 < bx1)
		{
			temp.from = FVector(ax2, y, 0);
			temp.to = FVector(bx1, y, 0);
		}
		else
		{
			temp.from = FVector(bx2, y, 0);
			temp.to = FVector(ax1, y, 0);
		}

		this->corridors.Add(temp);

		for (int i = 0; i < 3; i++)
		{
			temp.from.Y++;
			temp.to.Y++;
			this->corridors.Add(temp);
		}	

		return;
	}

	int xMax = FMath::Max(ax1, bx1);
	int xMin = FMath::Min(ax2, bx2);

	int yMax = FMath::Max(ay1, by1);
	int yMin = FMath::Min(ay2, by2);

	// Room 1 is upper left from room 2

	FCorridorStruct horizontal;
	FCorridorStruct vertical;

	if (ax1 < bx1)
	{
		int x1 = ax2;
		int x2 = bx1 + 4;

		int y1 = FMath::RandRange(ay1, ay2);

		horizontal.from = FVector(x1, y1, 0);
		horizontal.to = FVector(x2, y1, 0);
		vertical.from = FVector(x2, y1, 0);
		if (ay1 > by1)
		{
			horizontal.to.X += 3;
			vertical.from.Y += 3;
			vertical.to = FVector(x2, by2, 0);
		}
		else
		{
			horizontal.to.X += 3;
			vertical.to = FVector(x2, by1, 0);
		}

		this->corridors.Add(vertical);

		// Corridors breder maken
		for (int i = 0; i < 3; i++)
		{
			vertical.from.X++;
			vertical.to.X++;
			this->corridors.Add(vertical);
		}

		this->corridors.Add(horizontal);

		for (int i = 0; i < 3; i++)
		{
			horizontal.from.Y++;
			horizontal.to.Y++;
			this->corridors.Add(horizontal);
		}

		return;
	}
	else
	{
		int x1 = ax1;
		int x2 = bx2 - 4;
		int y1 = FMath::RandRange(ay1, ay2);

		horizontal.from = FVector(x1, y1, 0);
		horizontal.to = FVector(x2, y1, 0);
		vertical.from = FVector(x2, y1, 0);

		if (ay1 > by1)
		{
			horizontal.from.Y -= 3;
			horizontal.to.Y -= 3;
			vertical.to = FVector(x2, by2, 0);
		}
		else
		{
			horizontal.from.Y += 3;
			horizontal.to.Y += 3;
			vertical.from.Y += 3;
			vertical.to = FVector(x2, by1, 0);
		}
		this->corridors.Add(vertical);

		for (int i = 0; i < 3; i++)
		{
			vertical.from.X++;
			vertical.to.X++;
			this->corridors.Add(vertical);
		}

		this->corridors.Add(horizontal);

		for (int i = 0; i < 3; i++)
		{
			horizontal.from.Y++;
			horizontal.to.Y++;
			this->corridors.Add(horizontal);
		}

		return;
	}
}

void UWorldGenerator::ChooseRoomTypes()
{
	int startIndex = FMath::RandRange(0, this->rooms.Num() - 1);
	this->rooms[startIndex].roomType = ERoomType::Spawn;
	
	int bossIndex = 0;

	while (true)
	{
		bossIndex = FMath::RandRange(0, this->rooms.Num() - 1);
		if (bossIndex != startIndex)
			break;
	}

	this->rooms[bossIndex].roomType = ERoomType::Boss;

	for (int i = 0; i < this->rooms.Num(); i++)
	{
		if (i == startIndex || i == bossIndex)
		{
			continue;
		}

		this->rooms[i].roomType = ERoomType::Normal;
		this->rooms[i].numberOfEnemies = FMath::RandRange(1, this->maxEnemiesRoom);
	}
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

void UWorldGenerator::TryPlaceRoom()
{
	FRoomStruct newRoom = UWorldGenerator::GenerateRoom();

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

// Checks if there are too many rooms or tries
bool UWorldGenerator::TooManyTries()
{
	if ((this->rooms.Num() != this->maxNumberOfRooms) && (this->countTriesplacing < this->maxNumberOfRetries))
	{
		return false;
	}

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
		FRoomConnection connection = UWorldGenerator::FindMinimalDistance(rest, done);

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

void UWorldGenerator::SpawnRooms()
{
	while (!UWorldGenerator::TooManyTries())
	{
		UWorldGenerator::TryPlaceRoom();
	}

	UWorldGenerator::CreateSpanningTree();
	UWorldGenerator::CreateCorridors();
	UWorldGenerator::ChooseRoomTypes();
}
