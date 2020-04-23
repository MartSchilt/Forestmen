// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLevelScriptActor.h"
#include "DrawDebugHelpers.h"

ACustomLevelScriptActor::ACustomLevelScriptActor() {
	// Size of the room (plane is 100)
	this->roomSize = 100,0;
	this->maxRoomScale = 10,0;
	this->minRoomScale = 10,0;
	this->numberOfRetryPlacingRoom = 1000;
	this->maxNumberOfRooms = 10;
	// Maximum size of the entire grid
	this->maxGridSize = 100,0;

	// Level names
	this->StreamingLevelNames.Add(FName(TEXT("Procedural01")));
	this->StreamingLevelNames.Add(FName(TEXT("Procedural02")));
	this->StreamingLevelNames.Add(FName(TEXT("Procedural03")));
}

FName ACustomLevelScriptActor::GetStreamingLevelName()
{
	FName* data = StreamingLevelNames.GetData();

	int r = FMath::RandRange(0, StreamingLevelNames.Num() - 1);

	return data[r];
}

float ACustomLevelScriptActor::GetRandomRotation()
{
	int r = FMath::RandRange(0, 4);

	return r * 90;
}

// Generates a random room location and size 
TArray<FVector> ACustomLevelScriptActor::GenerateRoom() const
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

bool ACustomLevelScriptActor::isRoomOverlapping(FVector Room1Pos, FVector Room1Size, FVector Room2Pos, FVector Room2Size) const
{
	if (Room1Pos.X >= (Room2Pos.X + Room2Size.X) || Room2Pos.X >= (Room1Pos.X + Room1Size.X))
		return false;
	if ((Room1Pos.Y + Room1Size.Y) <= Room2Pos.Y || (Room2Pos.Y + Room2Size.Y) <= Room1Pos.Y)
		return false;

	return true;
}

// Tries to place the room 
void ACustomLevelScriptActor::TryPlaceRoom()
{
	TArray<FVector> arr = GenerateRoom();

	FVector pos = arr[0];
	FVector size = arr[1];

	int counter = 0;
	for (FVector pos2 : this->roomPositions)
	{
		FVector size2 = this->roomSizes[counter];

		if (isRoomOverlapping(pos, size, pos2, size2))
		{
			this->countTriesPlacing++;
			return;
		}
		counter++;
	}

	this->roomPositions.Add(pos);
	this->roomSizes.Add(size);
}

bool ACustomLevelScriptActor::tooManyTries() const
{
	if ((this->roomPositions.Num() != this->maxNumberOfRooms) && (this->countTriesPlacing < this->numberOfRetryPlacingRoom))
	{
		return false;
	}
	return true;
}
