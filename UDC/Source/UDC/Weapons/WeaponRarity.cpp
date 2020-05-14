// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponRarity.h"


class WeaponRarity {
public:
	virtual float GetWeaponDamage() = 0;

};

class Common : public WeaponRarity {
public:
	float GetWeaponDamage() {
		return 20;
	}
};

class Rare : public WeaponRarity {
public:
	float GetWeaponDamage() {
		return 30;
	}
};

class Epic : public WeaponRarity {
public:
	float GetWeaponDamage() {
		return 35;
	}
};

class Legendary : public WeaponRarity {
public:
	float GetWeaponDamage() {
		return 50;
	}
};

// Sets default values
AWeaponRarity::AWeaponRarity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AWeaponRarity::GetCommon() {
	Common rarity;
	return rarity.GetWeaponDamage();
}

float AWeaponRarity::GetRare() {
	Rare rarity;
	return rarity.GetWeaponDamage();
}

float AWeaponRarity::GetEpic() {
	Epic rarity;
	return rarity.GetWeaponDamage();
}

float AWeaponRarity::GetLegendary() {
	Legendary rarity;
	return rarity.GetWeaponDamage();
}



// Called when the game starts or when spawned
void AWeaponRarity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponRarity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

