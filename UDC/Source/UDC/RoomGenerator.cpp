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


void URoomGenerator::CreateSpanningTreeV2()
{
	TArray<FVector> rest;
	TArray<FVector> completed;

	for (int i = 0; i < this->roomsData.Num(); i++)
	{
		this->roomsData[i].middle = (FVector(this->roomsData[i].roomPosition.X + this->roomsData[i].roomSize.X / 2, this->roomsData[i].roomPosition.Y + this->roomsData[i].roomSize.Y / 2, 0));

		FVector middle = this->roomsData[i].middle;
		middle.Z = this->roomsData[i].roomNumber;

		rest.Add(middle);

	
	}

	completed.Add(rest[0]);
	rest.RemoveAt(0);

	while (rest.Num() != 0)
	{
		TArray<int> indexes = FindMinimalDistanceV2(rest, completed);

		int doneIndex = indexes[0];
		int restIndex = indexes[1];

		FCorridor cor = FCorridor();
		cor.from = completed[doneIndex].Z;
		cor.to = rest[restIndex].Z;

		completed.Add(rest[restIndex]);
		rest.RemoveAt(restIndex);

		this->Corridors.Add(cor);
	}

	for (FCorridor corridor : this->Corridors)
	{
		CreateCorridor(corridor);
	}


}


void URoomGenerator::CreateCorridor(FCorridor corridor)
{

	FRoomData from = this->roomsData[corridor.from];
	FRoomData to = this->roomsData[corridor.to];


	FVector Room1Pos = from.roomPosition;
	FVector Room1Size = from.roomSize;

	FVector Room2Pos = to.roomPosition;
	FVector Room2Size = to.roomSize;

	int ax1 = Room1Pos.X;
	int ax2 = Room1Pos.X + Room1Size.X;

	int ay1 = Room1Pos.Y;
	int ay2 = Room1Pos.Y + Room1Size.Y;

	int bx1 = Room2Pos.X;
	int bx2 = Room2Pos.X + Room2Size.X;

	int by1 = Room2Pos.Y;
	int by2 = Room2Pos.Y + Room2Size.Y;

	int max = FGenericPlatformMath::Max(ax1, bx1);
	int min = FGenericPlatformMath::Min(ax2, bx2);


	// Overlap in X
	if (max <= min)
	{

		int rnd = FMath::RandRange(max, min);


		// Room b is higher
		if (ay1 <= by1)
		{
			this->RoomStart.Add(FVector(rnd, ay2 + 5, 0));
			this->RoomEnd.Add(FVector(rnd, by1- 5, 0));
		}
		else
		{
			this->RoomStart.Add(FVector(rnd, by2 + 5, 0));
			this->RoomEnd.Add(FVector(rnd, ay1 - 5, 0));
		}

		return;


	}


	max = FMath::Max(ay1, by1);
	min = FMath::Min(ay2, by2);


	// Overlap in Y
	if (max <= min)
	{
		int rnd = FMath::RandRange(max, min);

		if (ax1 < bx1)
		{

			this->RoomStart.Add(FVector(ax2 + 5, rnd, 0));
			this->RoomEnd.Add(FVector(bx1 - 5, rnd, 0));
		}
		else
		{
			this->RoomStart.Add(FVector(bx2 + 5, rnd, 0));
			this->RoomEnd.Add(FVector(ax1 - 5, rnd, 0));
		}

		return;
	}


	// No overlap
	int y = FMath::RandRange(ay1, ay2);
	int x = FMath::RandRange(bx1, bx2);

	FVector path1 = FVector(ax2, y, 0);
	FVector path2 = FVector(x, by1, 0);
	FVector path3 = FVector(x, y, 0);


	this->RoomCorridorStart.Add(path1);
	this->RoomCorridorStart.Add(path2);

	this->RoomCorridorEnd.Add(path3);
	this->RoomCorridorEnd.Add(path3);





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

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      