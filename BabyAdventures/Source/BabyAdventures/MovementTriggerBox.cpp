// Fill out your copyright notice in the Description page of Project Settings.

#include "BabyAdventures.h"
#include "MovementTriggerBox.h"
#include "BabyAdventuresCharacter.h"

AMovementTriggerBox::AMovementTriggerBox() {
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMovementTriggerBox::OnOverlapBegin);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &AMovementTriggerBox::OnOverlapEnd);
	MoveForward = false;
}

void AMovementTriggerBox::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor->IsA<ABabyAdventuresCharacter>()) {
		for (AStaticMeshActor* iter : HideWalls) {
			iter->SetActorHiddenInGame(true);
		}
		for (AStaticMeshActor* iter : AppearWalls) {
			iter->SetActorHiddenInGame(false);
		}
		if (MoveForward) {
			Cast<ABabyAdventuresCharacter>(OtherActor)->SetCanMoveForward(true);
		}
	}
}

void AMovementTriggerBox::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor->IsA<ABabyAdventuresCharacter>()) {
		/*for (AStaticMeshActor* iter : HideWalls) {
			iter->SetActorHiddenInGame(false);
		}*/

		if( MoveForward )
			Cast<ABabyAdventuresCharacter>(OtherActor)->SetCanMoveForward(false);
	}

	//if( GetCollisionComponent()->overlap)
}
