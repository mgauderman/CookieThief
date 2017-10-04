// Fill out your copyright notice in the Description page of Project Settings.

#include "BabyAdventures.h"
#include "Mom.h"
#include "MomAIController.h"
#include "BabyAdventuresCharacter.h"


// Sets default values
AMom::AMom()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    AIControllerClass = AMomAIController::StaticClass();
    FireRate = 0.1f;
    RangeOfSight = 10000.0f;
    
}

// Called when the game starts or when spawned
void AMom::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AMom::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
}

// Called to bind functionality to input
void AMom::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
    
}

void AMom::LaserTrace () {
    
    
    static FName LaserFireTag = FName (TEXT("LaserTrace"));
    static FName EyeSocket = FName(TEXT("eyeSocket"));
    
    //start from the muzzle's position
    FVector StartPos = GetMesh() -> GetSocketLocation(EyeSocket);
    FVector Forward = GetActorForwardVector();
    FVector EndPos = StartPos + Forward * RangeOfSight;
    
    //Perform trace to retrieve hit info
    FCollisionQueryParams TraceParams (LaserFireTag, true, Instigator);
    TraceParams.bTraceAsyncScene = true;
    TraceParams.bReturnPhysicalMaterial = true;
    
    
    //this fires the ray and checks against all objects w/ collision
    FHitResult Hit (ForceInit);
    GetWorld()->DebugDrawTraceTag = LaserFireTag;
    GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos, FCollisionObjectQueryParams::AllObjects, TraceParams);
    
    //Did this hit anything?
    if (Hit.bBlockingHit)
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, hitParticlesEffect, Hit.ImpactPoint);
        
        if (Hit.GetActor()->IsA(ABabyAdventuresCharacter::StaticClass())) {
            ABabyAdventuresCharacter* character = Cast<ABabyAdventuresCharacter>(Hit.GetActor());
            if (character) {
                character->Damage(5.0f);
            }
        }
    }
}
void AMom::OnStartFire () {
    //MuzzleComp = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, GetMesh(), TEXT("eyeSocket"));
    LaserTrace();
}

void AMom::OnStopFire() {
    
   /* if (!MuzzleComp) {
        return;
    }
    MuzzleComp->DeactivateSystem();*/
    GetWorldTimerManager().ClearTimer(WeaponTimer);
}

