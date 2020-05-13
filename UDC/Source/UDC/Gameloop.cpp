// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameloop.h"

// Sets default values
UGameloop::UGameloop()
{
	Count = 6;
}

void UGameloop::Decrease(int Amount)
{
	Count -= Amount;
	UE_LOG(LogTemp, Log, TEXT("Decreased by %d -> %d"), Amount, Count);
}
