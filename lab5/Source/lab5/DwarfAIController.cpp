// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "DwarfAIController.h"


void ADwarfAIController::BeginPlay()
{
    Super::BeginPlay();
    mPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
    mState = Start;
}

void ADwarfAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if(mState == Start)
    {
        ChasePlayer();
    }
    else if(mState == Attack)
    {
        if(mRange < FVector::Dist(mPlayer->GetActorLocation(), GetPawn()->GetActorLocation()))
        {
            ChasePlayer();
        }
    }
}

void ADwarfAIController::ChasePlayer()
{
    MoveToActor(mPlayer);
    mState = Chase;
}

void ADwarfAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if(Result.IsSuccess())
    {
        mState = Attack;
    }
    else
    {
        mState = Chase;
    }
}
