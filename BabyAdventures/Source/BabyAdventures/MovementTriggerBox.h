// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerBox.h"
#include "Engine/StaticMeshActor.h"
#include "MovementTriggerBox.generated.h"


/**
 * 
 */
UCLASS()
class BABYADVENTURES_API AMovementTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TArray<AStaticMeshActor*> AppearWalls;

	UPROPERTY(EditAnywhere)
	TArray<AStaticMeshActor*> HideWalls;

	UPROPERTY(EditAnywhere)
	bool MoveForward;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:


public:
	AMovementTriggerBox();
	
};
