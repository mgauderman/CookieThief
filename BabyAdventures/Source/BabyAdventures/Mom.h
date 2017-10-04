// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Mom.generated.h"

UCLASS()
class BABYADVENTURES_API AMom : public ACharacter
{
	GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AMom();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    /* UPROPERTY(Transient)
     class UAudioComponent* FireAC;
    
    UPROPERTY(EditDefaultsOnly, Category = Effects)
    class UParticleSystem* MuzzleFX;
    
    UPROPERTY(Transient)
    class UParticleSystemComponent* MuzzleComp;*/
    
    UPROPERTY(EditAnywhere)
    float FireRate;
    
    UPROPERTY(EditAnywhere)
    float RangeOfSight;
    
    UPROPERTY(EditDefaultsOnly, Category = Effecs)
    UParticleSystem* hitParticlesEffect;
    
    UPROPERTY(EditAnywhere, Category = Damage)
    float Damage = 4.0f;
    
    
    void LaserTrace ();
    void OnStartFire ();
    void OnStopFire();
    
    
private:
    
    FTimerHandle WeaponTimer;
protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mom)
    USkeletalMeshComponent* MomMesh;
    
    


	
	
};
