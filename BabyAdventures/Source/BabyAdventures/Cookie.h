// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Actor.h"
#include "Cookie.generated.h"

UCLASS()
class BABYADVENTURES_API ACookie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACookie();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
		class USoundCue* cookieAudioCue;
	UAudioComponent* cookieAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Score")
	int32 PointValue = 1;
};
