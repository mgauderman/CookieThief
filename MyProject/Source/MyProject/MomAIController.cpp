// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "MomAIController.h"
#include "Mom.h"




void AMomAIController::BeginPlay () {
    Super::BeginPlay();
    
    PrimaryActorTick.bCanEverTick = true;
    clockwise = true;
    angle = 0;
    GetPawn()->SetActorRotation(FRotator (0, 0, 0));
    performingRightScan = true;
    performingLeftScan = false;
    CurrentState = StartRightScan;
}


void AMomAIController::Tick (float deltaTime) {
    
    if (CurrentState == Idle) {
        return;
    }
    
    if(CurrentState == StartRightScan) {
        
        if (clockwise) {
            int rand = FMath::RandRange(20, 90);
            angle = (float) rand;
            resultRotation = FRotator(0, angle, 0);
        }
        
        else {
            
            angle = 0;
            resultRotation = FRotator(0, angle, 0);
        }
        
        
        GetWorldTimerManager().SetTimer(scanTimer, this, &AMomAIController::OnScanTimer, 3.0f, false);
        CurrentState = Idle;
    }
    
    else if (CurrentState == StartLeftScan) {
        if (!clockwise) {
            int rand = FMath::RandRange(20, 90);
            angle = (float) rand;
            angle = -angle;
            resultRotation = FRotator(0, angle, 0);
        }
        
        else {
            
            angle = 0;
            resultRotation = FRotator(0, 0, 0);
        }
        
        
        GetWorldTimerManager().SetTimer(scanTimer, this, &AMomAIController::OnScanTimer, 3.0f, false);
        CurrentState = Idle;
        
    }
    
    else if (CurrentState == Scan) {
        AMom* mom = Cast<AMom>(GetPawn());
        mom->OnStartFire();
        
        if (clockwise) {
            mom->AddActorLocalRotation(FRotator(0, 1, 0));
        }
        
        else {
            mom->AddActorLocalRotation(FRotator(0, -1, 0));
        }
        
        if (mom->GetActorRotation().Equals(resultRotation)) {
            
            if (performingRightScan) {
                if (angle > 0) {
                    CurrentState = StartRightScan;
                    clockwise = false;
                }
            }
            else  {
                CurrentState = StartLeftScan;
                if (angle < 0) {
                    clockwise = true;
                }
            }
            if (angle == 0) {
                int rand = FMath::RandRange(1, 10);
                if (rand <=5) {
                    CurrentState = StartLeftScan;
                    performingRightScan = false;
                    clockwise = false;
                }
                else {
                    CurrentState = StartRightScan;
                    performingRightScan = true;
                    clockwise = true;
                }
                
            }
            
        }
    }
}

void AMomAIController::OnScanTimer () {
    GetWorldTimerManager().ClearTimer(scanTimer);
    CurrentState = Scan;
    
}





