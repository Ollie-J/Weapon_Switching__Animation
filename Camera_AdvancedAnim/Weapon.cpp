// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "MyPlayer.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//collision volume is now the root component
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());
	bIsGun = true;

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	Muzzle->SetupAttachment(SkeletalMesh);
	Muzzle->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));


	bInCombat = false;
	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnOverlapEnd);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Equip(AMyPlayer* Char)
{
	if(Char)
	{
		
		
		if(bIsGun)
		{
			if(Char->WeaponIndex.Num() == 0)
			{
				const USkeletalMeshSocket* Socket = Char->GetMesh()->GetSocketByName("RightHandSocket_AK");
				if(Socket)
				{
					Socket->AttachActor(this, Char->GetMesh());
					Char->WeaponIndex.AddUnique(this);
					Char->SetEquippedWeapon(this);
				}
			}
		}
		else 
		{
			const USkeletalMeshSocket* Socket = Char->GetMesh()->GetSocketByName("RightHandSocket_SMG");
			if(Socket)
			{
				Socket->AttachActor(this, Char->GetMesh());
				Char->WeaponIndex.AddUnique(this);
				
				
			}
			
		}
			
	}
}


							///////////////////////
							///// OverLapping///// 
							//////////////////////


void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		AMyPlayer* Char = Cast<AMyPlayer>(OtherActor);
		if(Char)
		{
			Equip(Char);
			bInCombat = true;
			
		}
	}
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}