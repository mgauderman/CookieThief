// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BabyAdventures.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "BabyAdventuresCharacter.h"

//////////////////////////////////////////////////////////////////////////
// ABabyAdventuresCharacter

ABabyAdventuresCharacter::ABabyAdventuresCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->AirControl = 1.0f;	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABabyAdventuresCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABabyAdventuresCharacter::BabyCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ABabyAdventuresCharacter::StopCrouching);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABabyAdventuresCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABabyAdventuresCharacter::MoveRight);

}


void ABabyAdventuresCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABabyAdventuresCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABabyAdventuresCharacter::MoveForward(float Value)
{
	if (CanMoveForward) {
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value/6); //hacky way to make character move slower
		}
	}
}

void ABabyAdventuresCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value/6);
	}
}

void ABabyAdventuresCharacter::BabyCrouch() {
	this->ACharacter::Crouch();
}
void ABabyAdventuresCharacter::StopCrouching() {
	this->ACharacter::UnCrouch();
}

void ABabyAdventuresCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	//sloooowly lose suspicion
	if (suspicion < 100.0f && suspicion > 0.0f) {
		suspicion -= 5.0f * DeltaSeconds;
		if (suspicion < 0.0f) {
			suspicion = 0.0f;
		}
	}
	
	//update camera position
	if (Camera != nullptr && Point != nullptr) {
		FVector cameraLocation = GetActorLocation() - Point->GetActorLocation();
		cameraLocation.Normalize();
		FVector NewLocation = Point->GetActorLocation() + cameraLocation * (CameraDistance - GetActorLocation().X);
		

		FVector direction = Point->GetActorLocation() - Camera->GetActorLocation();
		direction.Normalize();
		FVector axis = FVector::CrossProduct(FVector(1, 0, 0), direction);
		axis.Normalize();
		float angle = acos(FVector::DotProduct(FVector(1, 0, 0), direction));

		
		if (angle < -20.0f) {
			angle = -20.0f;
			NewLocation.Y = 1400.0f;
		}
		else if (angle > 20.0f) {
			angle = 20.0f;
			NewLocation.Y = -1400.0f;
		}
		FQuat cameraRotation(axis, angle);
		Camera->SetActorLocation(FVector(NewLocation.X, NewLocation.Y, GetActorLocation().Z));
		Camera->SetActorRotation(cameraRotation);
	}
}

void ABabyAdventuresCharacter::GivePoints(int amount) {
	Points += amount;
	if (Points >= 6) {
		IsVictorious = true;
		DisableInput(Cast<APlayerController>(GetController()));
		//TODO: more satisfying win procedure
		FVector TowardsCamera = Camera->GetActorLocation() - GetActorLocation();
		SetActorRotation(FRotator(0.0f, TowardsCamera.Y, TowardsCamera.Z));
        UGameplayStatics::OpenLevel(GetWorld(), "WinGame");
	}
}

void ABabyAdventuresCharacter::Damage(float damage) {
	if (!IsVictorious && suspicion < 100.0f) {
		suspicion += damage;
		if (suspicion >= 100.0f) {
			//TODO: more  satisfying lose procedure
            UGameplayStatics::OpenLevel(GetWorld(), "EndGame");
		}
	}
}

