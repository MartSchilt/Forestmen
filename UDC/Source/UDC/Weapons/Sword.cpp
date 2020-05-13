// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Sword = CreateDefaultSubobject<UStaticMeshComponent>("SM_Sword");
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Sword.SM_Sword'"));
	UStaticMesh* Asset = MeshAsset.Object;
	SM_Sword->SetStaticMesh(Asset);
	SM_Sword->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Bruh"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("XDDDDDDDDDDD"));
}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

