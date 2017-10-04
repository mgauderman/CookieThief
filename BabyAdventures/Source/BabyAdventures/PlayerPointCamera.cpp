// Fill out your copyright notice in the Description page of Project Settings.

#include "BabyAdventures.h"
#include "PlayerPointCamera.h"
#include <iostream>

void APlayerPointCamera::BeginPlay() {
	Super::BeginPlay();
	APawn* player = UGameplayStatics::GetPlayerPawn(this, 0);
	if (player != nullptr && Point != nullptr) {
		FVector cameraLocation = player->GetActorLocation() - Point->GetActorLocation();
		cameraLocation.Normalize();
		this->SetActorLocation(Point->GetActorLocation() + cameraLocation * 2600.0f);
	}
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerPointCamera::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	std::cout << "inside tick" << std::endl;
	APawn* player = UGameplayStatics::GetPlayerPawn(this, 0);
	if (player != nullptr) {
		FVector cameraLocation = player->GetActorLocation() - Point->GetActorLocation();
		//float distance = FVector::Dist(player->GetActorLocation(), Point->GetActorLocation());

		cameraLocation.Normalize();

		FVector finalLocation = Point->GetActorLocation() + cameraLocation * 2600.0f;
		if (finalLocation.Y > 1400.0f)
			finalLocation.Y = 1400.0f;
		else if (finalLocation.Y < -1400.0f)
			finalLocation.Y = -1400.0f;

		this->SetActorLocation(finalLocation);
	}
}


