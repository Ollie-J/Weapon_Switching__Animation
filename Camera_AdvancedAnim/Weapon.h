// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "MyPlayer.h"
#include "Weapon.generated.h"

UCLASS()
class CAMERA_ADVANCEDANIM_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "skeletal Mesh")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Collision")
	class USphereComponent* CollisionVolume;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* Muzzle;
	
  	 UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Movement")
   	 bool bInCombat;
	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Equip(class AMyPlayer* Char);

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Weapon Properties")
	bool bIsGun;

	

	

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
