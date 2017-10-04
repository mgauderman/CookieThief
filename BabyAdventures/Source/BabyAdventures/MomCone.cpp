// Fill out your copyright notice in the Description page of Project Settings.

#include "BabyAdventures.h"
#include "MomCone.h"
#include "BabyAdventuresCharacter.h"
#include "Mom2.h"


// Sets default values
AMomCone::AMomCone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMomCone::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMomCone::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (baby != nullptr && mom != nullptr) {
		if (IsOverlappingActor(baby)) {
			static FName LaserFireTag = FName(TEXT("LaserTrace"));
			static FName MuzzleSocket = FName(TEXT("eyeSocket"));

			//start from the muzzle's position
			FVector StartPos = mom->GetMesh()->GetSocketLocation(MuzzleSocket);
			FVector Forward = baby->GetActorLocation() - mom->GetActorLocation();
			Forward.Normalize();
			FVector EndPos = StartPos + Forward * mom->GetRangeOfSight();

			//Perform trace to retrieve hit info
			FCollisionQueryParams TraceParams(LaserFireTag, true, Instigator);
			if (coner != nullptr) {
				TraceParams.AddIgnoredActor(coner);
			}
			
			TraceParams.bTraceAsyncScene = true;
			TraceParams.bReturnPhysicalMaterial = true;


			//this fires the ray and checks against all objects w/ collision
			FHitResult Hit(ForceInit);
			
			//GetWorld()->DebugDrawTraceTag = LaserFireTag; //debug lines
			GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECollisionChannel::ECC_GameTraceChannel1);
			
			//Did this hit anything?
			if (Hit.bBlockingHit)
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, mom->GetHitParticlesEffect(), Hit.ImpactPoint);

				if (Hit.GetActor()->IsA(ABabyAdventuresCharacter::StaticClass())) {
					ABabyAdventuresCharacter* character = Cast<ABabyAdventuresCharacter>(Hit.GetActor());
					if (character) {
						if (baby->GetSuspicion() < 100.0f) {
							baby->Damage(40.0f * DeltaTime);
							mom->Track(baby->GetActorLocation());
						}
					}
				}
			}
		}
	}
	
}

