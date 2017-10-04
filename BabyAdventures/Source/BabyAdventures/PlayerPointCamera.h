// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "PlayerPointCamera.generated.h"

/**
 * 
 */
UCLASS()
class BABYADVENTURES_API APlayerPointCamera : public ACameraActor
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class AActor* Point;
	
};
