// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//constructor
	WalkSpeed = 400.0f;
	RunSpeed = 600.0f;
	TurnAmount = 0.0f;
	bJumping = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->JumpZVelocity = 350.f;

	//camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 250.0f;
	CameraBoom->TargetOffset = FVector(0.f, 000.f, 100.f);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;
	CameraBoom->bUsePawnControlRotation; //camera will rotate with controller

	//create followed camera to attach to boom
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); //attaching camera to boom
	FollowCamera->bUsePawnControlRotation = false; //camera doesnt rotate relative to the arm
	
	
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bJumping)
	{
		//unreals jump function
		Jump();
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// binding axis functions to map controls to movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &AMyPlayer::Turn);

	// bind action function to map action to movement
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayer::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyPlayer::EndRun);

	//jumping
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &AMyPlayer::CheckJump);
	PlayerInputComponent->BindAction("Jump",IE_Released, this, &AMyPlayer::CheckJump);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AMyPlayer::SwitchPrimary);
	

	
}

void AMyPlayer::SwitchPrimary()
{
	AMyPlayer* Char = this;
	if(WeaponIndex.Num() != 0)
	{
		for(int i = 0; i < WeaponIndex.Num(); i++)
		{
			if(WeaponIndex[i] == GetEquippedWeapon())
			{
				int CurrentWeaponIndex = i;
				int NewWeaponIndex = CurrentWeaponIndex + 1;
				if(NewWeaponIndex >= WeaponIndex.Num())
				{
					NewWeaponIndex = 0;
				}
				SetEquippedWeapon(WeaponIndex[NewWeaponIndex]);
				UE_LOG(LogTemp, Warning, TEXT("Weapon has been changed!"))
				if(WeaponIndex[CurrentWeaponIndex]->bIsGun)
				{
					const USkeletalMeshSocket*  Socket = Char->GetMesh()->GetSocketByName("SpineSocket_AK");
					if (Socket)
					{
						Socket->AttachActor(WeaponIndex[CurrentWeaponIndex], Char->GetMesh());
					}
				}
				else
				{
					const USkeletalMeshSocket*  Socket = Char->GetMesh()->GetSocketByName("SpineSocket_SMG");
					if (Socket)
					{
						Socket->AttachActor(WeaponIndex[CurrentWeaponIndex], Char->GetMesh());
					}
				}
				if(WeaponIndex[NewWeaponIndex]->bIsGun)
				{
					const USkeletalMeshSocket*  Socket = Char->GetMesh()->GetSocketByName("RightHandSocket_AK");
					if (Socket)
					{
						Socket->AttachActor(WeaponIndex[NewWeaponIndex], Char->GetMesh());
					}
				}
				else
				{
					const USkeletalMeshSocket*  Socket = Char->GetMesh()->GetSocketByName("RightHandSocket_SMG");
					if (Socket)
					{
						Socket->AttachActor(WeaponIndex[NewWeaponIndex], Char->GetMesh());
					}
				}
				break;
			}
		}
	}
}



//movement functions

void AMyPlayer::MoveForward(float InputAxis)
{
	if(InputAxis != 0)
	{
		AddMovementInput(GetActorForwardVector(), InputAxis);
	}
	
}

void AMyPlayer::Turn(float InputAxis)
{
	if(InputAxis !=0)
	{
		TurnAmount += InputAxis;
     	 Controller->ClientSetRotation(FRotator(0.f, TurnAmount,0.f));
		
	}
	
}

void AMyPlayer::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed=RunSpeed;
}

void AMyPlayer::EndRun()
{
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
}

//Jump functions

void AMyPlayer::CheckJump()
{
	if(bJumping)
	{
		bJumping = false;
	}
	else
	{
		bJumping = true;
		
	}
}
	
	
	
