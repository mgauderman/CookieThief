// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Mom2.generated.h"

UCLASS()
class BABYADVENTURES_API AMom2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMom2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/* UPROPERTY(Transient)
	class UAudioComponent* FireAC;*/

	UPROPERTY(EditAnywhere)
		float FireRate;

	UPROPERTY(EditAnywhere)
		float RangeOfSight;

	float GetRangeOfSight() { return RangeOfSight; }

	UPROPERTY(EditDefaultsOnly, Category = Effecs)
		UParticleSystem* hitParticlesEffect;

	UParticleSystem* GetHitParticlesEffect() { return hitParticlesEffect; }


	void Track(FVector target);

	void Rotate();
	FRotator targetRot;
	float duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float pitchMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float pitchMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float yawMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float yawMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float durationMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float durationMax;

private:

	FTimerHandle WeaponTimer;
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mom2)
		USkeletalMeshComponent* Mom2Mesh;

	
};
