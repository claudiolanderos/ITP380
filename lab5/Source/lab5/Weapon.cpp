// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "Weapon.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "lab5Character.h"
#include "DwarfCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;
    
    FireRate = 0.1f;
    WeaponRange = 10000.0f;
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
    
    GetWorldTimerManager().SetTimer(WeaponTimer, this, &AWeapon::WeaponTrace, FireRate, true);
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
    GetWorldTimerManager().ClearTimer(WeaponTimer);
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

void AWeapon::WeaponTrace()
{
    static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
    static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
    // Start from the muzzle's position
    FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
    // Get forward vector of MyPawn
    FVector Forward = MyOwner->GetActorForwardVector();
    // Calculate end position
    FVector EndPos = StartPos + Forward*WeaponRange;
    // Perform trace to retrieve hit info
    FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
    TraceParams.bTraceAsyncScene = true;
    TraceParams.bReturnPhysicalMaterial = true;
    // This fires the ray and checks against all objects w/ collision
    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos,
                                            FCollisionObjectQueryParams::AllObjects, TraceParams);
    // Did this hit anything?
    if (Hit.bBlockingHit)
    {
        ImpactSC = UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, Hit.ImpactPoint);
        
        ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(Hit.GetActor());
        if (Dwarf)
        {
            Dwarf->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
        }
    }
}
