// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnimInstance.h"

#include "GameFramework/Actor.h" 

#include "MyPlayer.h"
#include "Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"

UMyPlayerAnimInstance::UMyPlayerAnimInstance()
{
	
	
}


void UMyPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	
	
	if(Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		
	}
}

void UMyPlayerAnimInstance::UpdateAnimationProperties()
{
	
	if(Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		
	}

	if(Pawn)
	{
		if(Pawn)
		{
			 
			//Jumping
			bIsFalling = Pawn->GetMovementComponent()->IsFalling();
			//Movement
			FVector Speed = Pawn->GetVelocity();
			FVector lateralSpeed = FVector(Speed.X,Speed.Y, 0.0f); // Z for jump
			MovementSpeed = lateralSpeed.Size();
			//Switching to combat mode when the player is overlapping
			AWeapon* CombatStance = Cast<AWeapon>(//add here);
			
				if(CombatStance)
				{
					CombatStance->bInCombat = true;
				}
		}
	}
		
		
		
		
		
		
}
	



