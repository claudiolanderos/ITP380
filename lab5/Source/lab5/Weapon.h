// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class LAB5_API AWeapon : public AActor
{
    GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    USkeletalMeshComponent* GetWeaponMesh();
    
    void OnStartFire();
    void OnStopFire();
    
    UAudioComponent* PlayWeaponSound(class USoundCue* Sound);
    
protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
    USkeletalMeshComponent* WeaponMesh;
    
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* FireLoopSound;
    
    UPROPERTY(EditDefaultsOnly, Category = Sound)
    class USoundCue* FireFinishSound;
    
    UPROPERTY(Transient)
    class UAudioComponent* FireAC;
    
    UPROPERTY(EditDefaultsOnly, Category = Effects)
    class UParticleSystem* MuzzleFX;
    
    UPROPERTY(Transient)
    class UParticleSystemComponent* MuzzleSC;
};
