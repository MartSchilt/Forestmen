// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"

UENUM(BlueprintType)
enum Rarity {
	Common,
	Rare,
	Epic,
	Legendary
};

UCLASS()
class UDC_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();

	UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<Rarity> Type;

	UFUNCTION(BlueprintCallable, Category = Weapons)
		float GetDamage(Rarity rarity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
