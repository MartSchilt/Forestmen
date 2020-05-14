// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
//#include "WeaponRarity.h"

using namespace std;

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float ASword::GetDamage(Rarity rarity) {
	return (20 + rarity * 10);
}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
