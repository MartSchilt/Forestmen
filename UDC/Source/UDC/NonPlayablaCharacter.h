// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Engine/World.h"
#include "TimerManager.h"

#include "NonPlayablaCharacter.generated.h"

UCLASS()
class UDC_API ANonPlayablaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANonPlayablaCharacter();

	bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HenkPoints;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float HP_Max;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float HP_Heal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ManaPoints;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MP_Max;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MP_Recharge;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Is_Attacked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Coins;

	UFUNCTION()
		void onTimerEnd();

	UFUNCTION(BlueprintCallable, Category = EnemyFunctions)
		bool TakeDamage(float Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle _loopTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
