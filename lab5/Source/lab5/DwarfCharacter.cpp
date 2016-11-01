// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "DwarfCharacter.h"
#include "DwarfAIController.h"

// Sets default values
ADwarfCharacter::ADwarfCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    AIControllerClass = ADwarfAIController::StaticClass();
}

// Called when the game starts or when spawned
void ADwarfCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADwarfCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADwarfCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ADwarfCharacter::StartAttack()
{
    PlayAnimMontage(AttackAnim);
}

void ADwarfCharacter::StopAttack()
{
    StopAnimMontage(AttackAnim);
}

float ADwarfCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    if (ActualDamage > 0.0f)
    {
        Health -= ActualDamage;
        if (Health <= 0.0f)
        { // We're dead, don't allow further damage
            bCanBeDamaged = false;
            StopAttack();
            float time = PlayAnimMontage(DeathAnim);
            time -= 0.25f;
            FTimerHandle handle;
            GetWorldTimerManager().SetTimer(handle, this, &ADwarfCharacter::Finish, time, false);
            GetController()->UnPossess();
        }
    }
    return ActualDamage;
}

void ADwarfCharacter::Finish()
{
    Destroy();
}
