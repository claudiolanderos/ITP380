// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "Weapon.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AWeapon::OnStartFire()
{
    FireAC = PlayWeaponSound(FireLoopSound);
    MuzzleSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, WeaponMesh, TEXT("MuzzleFlashSocket"));
}

void AWeapon::OnStopFire()
{
    if(MuzzleSC != nullptr)
    {
        MuzzleSC->DeactivateSystem();
    }
    if(FireAC != nullptr)
    {
        FireAC->Stop();
    }
    FireAC = PlayWeaponSound(FireFinishSound);
}

UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* Sound)
{
    UAudioComponent* AC = NULL;
    if (Sound)
    {
        AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
    }
    return AC;
}
