// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	bDead = false;
	JumpVelocity = 400.0f;
	HenkPoints = 100.0f;
	HP_Max = 100.0f;
	HP_Min = 0.0f;
	HP_Heal = 20.0f;
	HP_Decrease = 4.0f;
	ManaPoints = 80.0f;
	MP_Max = 80.0f;
	MP_Recharge = 10.0f;
	Coins = 0;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Rotate the character to the direction it is headed
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	// Jump Height
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;
	// How much you can move in the air
	GetCharacterMovement()->AirControl = 0.2f;

	// Attach the camera with a boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	// Length from the player to the camera
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);

	if (Player_HUD_Class != nullptr) {
		Player_HUD = CreateWidget(GetWorld(), Player_HUD_Class);
		Player_HUD->AddToViewport();
	}

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (ManaPoints > 0) ManaPoints -= DeltaTime * 1.0f;

	//if (HenkPoints > 0) HenkPoints -= DeltaTime * HP_Decrease;

	if (HenkPoints <= 0) {
		if (!bDead) {
			bDead = true;

			GetMesh()->SetSimulatePhysics(true);

			FTimerHandle UnusedHandle;
			// Don't worry about the red line, it works
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayerCharacter::RestartGame, 3.0f, false);
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding the standard input module "Turn" to this
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
}

// Custom functions
// Movement controls
void APlayerCharacter::MoveForward(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacter::MoveRight(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacter::RestartGame()
{
	// Reload this world
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* HitComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Pickable item has the tag "Recharge"
	if (OtherActor->ActorHasTag("Recharge")) {
		UE_LOG(LogTemp, Warning, TEXT("Collided with"));

		ManaPoints += MP_Recharge;
		if (ManaPoints > MP_Max) ManaPoints = MP_Max;

		OtherActor->Destroy();
	}
}

void APlayerCharacter::Heal()
{
	HenkPoints += HP_Heal;
	Coins += 5;

	if (HenkPoints > HP_Max) HenkPoints = HP_Max;
}

void APlayerCharacter::TakeDamage(float d) 
{
	HenkPoints -= d;

	if (HenkPoints < HP_Min) HenkPoints = HP_Min;
}

