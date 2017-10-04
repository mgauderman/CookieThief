// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MomCone.generated.h"

UCLASS()
class BABYADVENTURES_API AMomCone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMomCone();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UPROPERTY(EditAnywhere)
	class ABabyAdventuresCharacter* baby;

	UPROPERTY(EditAnywhere)
	class AMom2* mom;

	UPROPERTY(EditAnywhere)
	class AActor* coner;
};
