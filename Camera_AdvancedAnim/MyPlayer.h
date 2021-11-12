// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class CAMERA_ADVANCEDANIM_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** Movement functions */
    void MoveForward(float InputAxis);
	void Turn(float InputAxis);

	/** Running functions */
	void StartRun();
	void EndRun();
	
	/** Jump functions */
	void CheckJump();

	UPROPERTY()
	bool bJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Movement")
	float TurnAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Movement")
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Movement")
	float RunSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY()
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	class AWeapon* EquippedWeapon;

	FORCEINLINE AWeapon* GetEquippedWeapon() {return EquippedWeapon; };
	FORCEINLINE void SetEquippedWeapon(AWeapon* Weapon) { EquippedWeapon = Weapon; };

	UPROPERTY()
	TArray<AWeapon*> WeaponIndex;

	void SwitchPrimary();
	
};

