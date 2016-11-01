// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DwarfAIController.generated.h"

/**
 * 
 */
UCLASS()
class LAB5_API ADwarfAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    
    void BeginPlay() override;
	
    void Tick(float DeltaSeconds) override;
    
    void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
    
private:
    void ChasePlayer();
    
    enum State { Start, Chase, Attack, Dead } mState;
    
    APawn* mPlayer;
    
    float mRange = 150.0f;
};
