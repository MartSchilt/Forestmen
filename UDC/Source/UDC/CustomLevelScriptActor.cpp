// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLevelScriptActor.h"

ACustomLevelScriptActor::ACustomLevelScriptActor() {
	GridSize = 9;
	TileSize = 1000,0;
	StreamingLevelNames.Add(FName(TEXT("Procedural01")));
	StreamingLevelNames.Add(FName(TEXT("Procedural02")));
	StreamingLevelNames.Add(FName(TEXT("Procedural03")));
}

float ACustomLevelScriptActor::GetLocation(int index)
{
	// Multiple index times the tilesize and that minus the mapsize will be the x or y location, depending on the given index
	float m = index * TileSize;
	return (m - GetMapSize());
}

float ACustomLevelScriptActor::GetMapSize()
{
	return (GridSize * TileSize) / 2.0f;
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
