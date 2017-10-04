// Fill out your copyright notice in the Description page of Project Settings.

#include "BabyAdventures.h"
#include "BabyAdventuresCharacter.h"
#include "Cookie.h"


// Sets default values
ACookie::ACookie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACookie::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACookie::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FRotator rotation = GetActorRotation();
	rotation.Roll = rotation.Roll + 0.8f;
	SetActorRotation(rotation);
}

void ACookie::NotifyActorBeginOverlap(AActor* OtherActor) {
	if (OtherActor->IsA(ABabyAdventuresCharacter::StaticClass())) {
		ABabyAdventuresCharacter* Player = Cast<ABabyAdventuresCharacter>(OtherActor);
		Player->GivePoints(PointValue);
		this->Destroy();
	}
	
}