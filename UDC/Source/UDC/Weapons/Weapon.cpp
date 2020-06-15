// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
//#include "WeaponRarity.h"

using namespace std;

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float AWeapon::GetDamage(Rarity rarity, int weaponType) {
	

	switch (weaponType) {
	case 0:
		val1 = (rarity / 4) + 1;
		val2 = rarity * 4;
		return (20 * val1) + val2;
		break;

	case 1:
		val1 = (rarity / 4) + 1;
		val2 = rarity * 4;
		return (23 * val1) + val2;
		break;

	case 2:
		val1 = (rarity / 4) + 1;
		val2 = rarity * 4;
		return (26 * val1) + val2;
		break;

	default:
		val1 = (rarity / 4) + 1;
		val2 = rarity * 4;
		return (20 * val1) + val2;
		break;
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

