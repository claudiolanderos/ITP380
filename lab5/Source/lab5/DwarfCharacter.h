// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DwarfCharacter.generated.h"

UCLASS()
class LAB5_API ADwarfCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADwarfCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    void StartAttack();
    void StopAttack();
    
    UPROPERTY(EditDefaultsOnly)
    class UAnimMontage* AttackAnim;
	
    UPROPERTY(EditDefaultsOnly)
    class UAnimMontage* DeathAnim;
    
    UPROPERTY(EditAnywhere, Category = Damage)
    float Health = 20.0f;
    
    UPROPERTY(EditAnywhere, Category = Damage)
    float MDamage = 10.0f;
    
private:
    void Finish();
    void Attack();
    
    FTimerHandle AttackTimer;
};
