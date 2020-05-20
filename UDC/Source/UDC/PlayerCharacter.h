// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//	Custom includes
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Blueprint/UserWidget.h"

// Required last
#include "PlayerCharacter.generated.h"

UCLASS()
class UDC_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float JumpVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HenkPoints;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float HP_Max;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float HP_Heal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float HP_Decrease;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float ManaPoints;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MP_Max;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MP_Recharge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Coins;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = Player)
		void Heal();

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Player_HUD_Class;

	UUserWidget* Player_HUD;

	void RestartGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
