// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include  "Weapon.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAMERA_ADVANCEDANIM_API UMyPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
		UMyPlayerAnimInstance();
	
		virtual void NativeInitializeAnimation() override;
	
		UFUNCTION(BlueprintCallable, Category = "Animation")
		void UpdateAnimationProperties();
	
		UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Movement")
		float MovementSpeed;

		

		UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Jumping")
		bool bIsFalling;
	
		UPROPERTY(EditAnywhere,BlueprintReadOnly,  Category = "Movement")
		class APawn* Pawn;


	
	
};
