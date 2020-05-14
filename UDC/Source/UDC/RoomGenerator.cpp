// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomGenerator.h"

// Sets default values for this component's properties
URoomGenerator::URoomGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Size of the room (plane is 100)
	this->roomSize = 100, 0;
	this->maxRoomScale = 10, 0;
	this->minRoomScale = 10, 0;
	this->numberOfRetryPlacingRoom = 1000;
	this->maxNumberOfRooms = 10;
	// Maximum size of the entire grid
	this->maxGridSize = 100, 0;
	this->distanceBetweenRooms = 15, 0;

	// Level names
	this->StreamingLevelNames.Add(FName(TEXT("Procedural01")));
	this->StreamingLevelNames.Add(FName(TEXT("Procedural02")));
	this->StreamingLevelNames.Add(FName(TEXT("Procedural03")));
}


FName URoomGenerator::GetStreamingLevelName()
{
	FName* data = StreamingLevelNames.GetData();

	int r = FMath::RandRange(0, StreamingLevelNames.Num() - 1);

	return data[r];
}

float URoomGenerator::GetRandomRotation()
{
	int r = FMath::RandRange(0, 4);

	return r * 90;
}

void URoomGenerator::TryPlaceRoom()
{
	TArray<FVector> arr = GenerateRoom();

	FVector pos = arr[0];
	FVector size = arr[1];

	int counter = 0;

	for (FRoomData roomData : this->roomsData)
	{
		if (isRoomOverlapping(pos, size, roomData.roomPosition, roomData.roomSize))
		{
			this->countTriesPlacing++;
			return;
		}
		counter++;
	}

	FRoomData roomdata = FRoomData();
	roomdata.roomNumber = this->roomsData.Num();
	roomdata.roomPosition = pos;
	roomdata.roomSize = size;

	this->roomsData.Add(roomdata);

}

bool URoomGenerator::tooManyTries() const
{
	if ((this->roomPositions.Num() != this->maxNumberOfRooms) && (this->countTriesPlacing < this->numberOfRetryPlacingRoom))
	{
		return false;
	}
	return true;
}

TArray<FVector> URoomGenerator::GenerateRoom() const
{
	FVector position;
	FVector size;
	TArray<FVector> retArr;

	int x = FMath::RandRange(this->minRoomScale, this->maxRoomScale);
	int y = FMath::RandRange(this->minRoomScale, this->maxRoomScale);

	size = FVector(x, y, 0);

	int xMax = maxGridSize - size.X;
	int yMax = maxGridSize - size.Y;

	x = FMath::RandRange(0, xMax);
	y = FMath::RandRange(0, yMax);

	position = FVector(x, y, 0);

	retArr.Add(position);
	retArr.Add(size);

	return retArr;
}

bool URoomGenerator::isRoomOverlapping(FVector Room1Pos, FVector Room1Size, FVector Room2Pos, FVector Room2Size) const
{
	if (Room1Pos.X >= (Room2Pos.X + Room2Size.X + distanceBetweenRooms) || Room2Pos.X >= (Room1Pos.X + Room1Size.X + distanceBetweenRooms))
		return false;
	if ((Room1Pos.Y + Room1Size.Y + distanceBetweenRooms) <= Room2Pos.Y || (Room2Pos.Y + Room2Size.Y + distanceBetweenRooms) <= Room1Pos.Y)
		return false;

	return true;
}


void URoomGenerator::SetEntrances(int roomIndex, FTransform entranceTransform)
{

	FVector roomPos = this->roomsData[roomIndex].roomPosition;
	FVector loc = entranceTransform.GetLocation();
	
	FVector entrance = roomPos + loc;


	this->roomsData[roomIndex].entrancePositions.Add(entrance);
}


