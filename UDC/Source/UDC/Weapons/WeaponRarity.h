// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponRarity.generated.h"

UCLASS()
class UDC_API AWeaponRarity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponRarity();

	UFUNCTION(BlueprintCallable, Category = Rarity)
		float GetCommon();
	UFUNCTION(BlueprintCallable, Category = Rarity)
		float GetRare();
	UFUNCTION(BlueprintCallable, Category = Rarity)
		float GetEpic();
	UFUNCTION(BlueprintCallable, Category = Rarity)
		float GetLegendary();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
