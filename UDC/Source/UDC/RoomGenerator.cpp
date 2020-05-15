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
	this->maxRoomScale = 50, 0;
	this->minRoomScale = 50, 0;
	this->numberOfRetryPlacingRoom = 1000;
	this->maxNumberOfRooms = 20;
	// Maximum size of the entire grid
	this->maxGridSize = 500, 0;
	this->distanceBetweenRooms = 15, 0;

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
	if ((this->roomsData.Num() != this->maxNumberOfRooms) && (this->countTriesPlacing < this->numberOfRetryPlacingRoom))
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

TArray<int> URoomGenerator::findMinimalDistance(TArray<FVector> rest, TArray<FVector> done, TMap<FVector, int> EntranceMap)
{

	int tempDone;
	int tempRest;

	float minDist = MAX_FLT;

	int counterDone = 0;


	for (FVector posDone : done)
	{
		int counterRest = 0;
		for (FVector posRest : rest)
		{

			int* Key1 = EntranceMap.Find(posDone);
			int* Key2 = EntranceMap.Find(posRest);


			if (*Key1 == *Key2)
			{		
				counterRest++;
				continue;
			}


			float tempDist = FVector::Dist(posDone, posRest);

			if (tempDist < minDist)
			{
				minDist = tempDist;
				tempDone = counterDone;
				tempRest = counterRest;
			}
			counterRest++;

		}
		counterDone++;
	}	


	TArray<int> ret;
	ret.Add(tempDone);
	ret.Add(tempRest);

	return ret;




}


void URoomGenerator::SetEntrances(int roomIndex, FTransform entranceTransform)
{

	FVector roomPos = this->roomsData[roomIndex].roomPosition;
	FVector size = this->roomsData[roomIndex].roomSize;
	FVector loc = entranceTransform.GetLocation() / 100;
	
	FVector entrance = roomPos + loc;


	//this->roomsData[roomIndex].middle = FVector(roomPos.X + size.X / 2, roomPos.Y + size.Y / 2, 0);
	this->roomsData[roomIndex].middle = roomPos;

	this->roomsData[roomIndex].entrancePositions.Add(entrance);
}


void URoomGenerator::CreateSpanningTreeV2()
{
	TArray<FVector> rest;
	TArray<FVector> completed;

	for (FRoomData room : this->roomsData)
	{
		rest.Add(room.roomPosition);
	}

	completed.Add(rest[0]);
	rest.RemoveAt(0);

	while (rest.Num() != 0)
	{
		TArray<int> indexes = FindMinimalDistanceV2(rest, completed);

		int doneIndex = indexes[0];
		int restIndex = indexes[1];

		FCorridor cor = FCorridor();
		cor.from = completed[doneIndex];
		cor.to = rest[restIndex];

		completed.Add(rest[restIndex]);
		rest.RemoveAt(restIndex);

		this->Corridors.Add(cor);
	}

}


TArray<int> URoomGenerator::FindMinimalDistanceV2(TArray<FVector> rest, TArray<FVector> completed)
{

	float minDist = MAX_FLT;
	int indexDone;
	int indexRest;

	int counterDone = 0;
	for (FVector posCompleted : completed)
	{
		int counterRest = 0;
		for (FVector posRest : rest)
		{
			float dist = FVector::Dist(posCompleted, posRest);

			if (dist < minDist)
			{
				minDist = dist;
				indexDone = counterDone;
				indexRest = counterRest;	
			}

			counterRest++;

		}

		counterDone++;
	}

	TArray<int> ret;

	ret.Add(indexDone);
	ret.Add(indexRest);

	return ret;

}


void URoomGenerator::CreateSpanningTree()
{
	// Vector is the position for easy look up and the int is the room number
	TMap<FVector, int> entranceMap;
	TArray<FVector> rest;
	TArray<FVector> completed;

	TArray<FCorridor> edges;

	for (FRoomData room : this->roomsData)
	{
		for (FVector entrance : room.entrancePositions)
		{
			rest.Add(entrance);
			entranceMap.Add(entrance, room.roomNumber);
		}
	}




	completed.Add(rest[0]);
	rest.RemoveAt(0);

	while (rest.Num() != 0)
	{
		TArray<int> indexes = findMinimalDistance(rest, completed, entranceMap);

		int indexDone = indexes[0];
		int indexRest = indexes[1];

		FCorridor edge = FCorridor();
		edge.from = completed[indexDone];
		edge.to = rest[indexRest];

		edges.Add(edge);

		completed.Add(rest[indexRest]);
		rest.RemoveAt(indexRest);

	}

	this->Corridors = edges;

}



