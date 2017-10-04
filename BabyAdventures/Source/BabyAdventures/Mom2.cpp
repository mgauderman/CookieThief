// Fill out your copyright notice in the Description page of Project Settings.

#include "BabyAdventures.h"
#include "Mom2.h"
//#include "Mom2AIController.h"
#include "BabyAdventuresCharacter.h"


// Sets default values
AMom2::AMom2()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AIControllerClass = AMom2AIController::StaticClass();
	FireRate = 0.1f;
	RangeOfSight = 10000.0f;

}

// Called when the game starts or when spawned
void AMom2::BeginPlay()
{
	Super::BeginPlay();
	Rotate();
}

// Called every frame
void AMom2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), targetRot, DeltaTime, 0.5f));
}

void AMom2::Track(FVector target) {
	FVector towardsTarget = target - GetActorLocation();
	towardsTarget.Normalize();
	FVector axis = FVector::CrossProduct(FVector(-1, 0, 0), towardsTarget);
	axis.Normalize();
	float angle = acos(FVector::DotProduct(FVector(-1, 0, 0), towardsTarget));

	FQuat quat(axis, angle);
	SetActorRotation(quat);
}

// Called to bind functionality to input
void AMom2::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


void AMom2::Rotate() {
	FTimerHandle handle;
	duration = FMath::RandRange(durationMin, durationMax);
	GetWorldTimerManager().SetTimer(handle, this, &AMom2::Rotate, duration);
	//generate random point to turn towards
	float x = FMath::RandRange(pitchMin, pitchMax);
	float y = FMath::RandRange(yawMin, yawMax);
	targetRot = FRotator(x, y, 0);
}