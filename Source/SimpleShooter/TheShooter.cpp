// Fill out your copyright notice in the Description page of Project Settings.


#include "TheShooter.h"
#include "Engine/World.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameMode.h"
// Sets default values
ATheShooter::ATheShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATheShooter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	CurrentGun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	CurrentGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform , TEXT("WeaponSocket") );
	CurrentGun->SetOwner(this);
}

bool ATheShooter::IsDead() const
{
	return Health <= 0;
}

float ATheShooter::GetHealthPercent() const
{
	
	return Health / MaxHealth;
}

// Called every frame
void ATheShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATheShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &ATheShooter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATheShooter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ATheShooter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ATheShooter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &ATheShooter::Shoot);


}

float ATheShooter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	// UE_LOG(LogTemp , Warning , TEXT("Health left %f"), Health);
	if (IsDead())
	{
		ASimpleShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameMode>(); 
		if (GameMode)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
		
	}
	return DamageToApply;
}

void ATheShooter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ATheShooter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ATheShooter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
	// UE_LOG(LogTemp, Display, TEXT("Your message: %f"), ( RotationRate *GetWorld()->GetDeltaSeconds()));
}

void ATheShooter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ATheShooter::Shoot()
{
	CurrentGun->PullTrigger();
}

