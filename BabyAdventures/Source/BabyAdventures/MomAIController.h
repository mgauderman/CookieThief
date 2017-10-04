// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MomAIController.generated.h"

/**
 * 
 */
UCLASS()
class BABYADVENTURES_API AMomAIController : public AAIController
{
	GENERATED_BODY()

    public:
        void BeginPlay () override;
        void Tick (float deltaTime) override;
        void OnIdleTimer();
        
        enum State {
            StartRightScan,
            StartLeftScan,
            Idle,
            Scan,
            Attack,
            EndScan
            
        };
        
        State CurrentState;
        UPROPERTY(EditAnywhere)
        float range = 150.0f;
        
        UPROPERTY(EditAnywhere)
        float ScanTime = 5.0f;
        
        UPROPERTY(EditAnywhere)
        float attackDamage = 10.0f;
        
        float angle = 0;
        
        void OnScanTimer ();
        
        
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
        float turnRate = 0.8;
        
        bool idle;
        
        bool clockwise;
        
        FRotator resultRotation;
        
        FTimerHandle scanTimer;
    
    bool performingRightScan;
    bool performingLeftScan;

	
};
