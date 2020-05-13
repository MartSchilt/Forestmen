// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Gameloop.generated.h"

/**
 *
 */
UCLASS()
class UDC_API UGameloop : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// Sets default values for this actor's properties
	UGameloop();

public:
	
	UFUNCTION(BlueprintCallable, Category = "GAMELOOP")

		void Decrease(int Amount);

	UPROPERTY(BlueprintReadOnly, Category = "GAMELOOP")
		int Count;
};
