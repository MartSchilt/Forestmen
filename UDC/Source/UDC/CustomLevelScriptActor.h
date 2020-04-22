// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CustomLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class UDC_API ACustomLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int GridSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		TArray<FName> StreamingLevelNames;

	ACustomLevelScriptActor();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		float GetLocation(int i);

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		float GetMapSize();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		FName GetStreamingLevelName();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		float GetRandomRotation();

};
