// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BabyAdventuresCharacter.generated.h"

UCLASS(config=Game)
class ABabyAdventuresCharacter : public ACharacter
{
	GENERATED_BODY()

	///** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	///** Follow camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* FollowCamera;

	///* Single plane camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* FixedCamera;

public:
	ABabyAdventuresCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMoveForward = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsVictorious = false;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/* Crouching */
	void BabyCrouch();
	void StopCrouching();

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class AActor* Camera;
	UPROPERTY(EditAnywhere, Category = "Camera")
		float CameraDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class AActor* Point;

	UPROPERTY(BlueprintReadOnly)
		float suspicion = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	int Points = 0;


public:
	///** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	///** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	///* Returns FixedCamera subobject */
	//FORCEINLINE class UCameraComponent* GetFixedCamera() const { return FixedCamera; }

	virtual void Tick(float DeltaSeconds) override;

	void SetCanMoveForward(bool canMove) { CanMoveForward = canMove; }

	void GivePoints(int amount);
	int GetPoints() { return Points; }
	float GetSuspicion() { return suspicion; }
	void Damage(float damage);

};

