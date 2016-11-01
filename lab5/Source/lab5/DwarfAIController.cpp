// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "DwarfAIController.h"
#include "DwarfCharacter.h"

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
        APawn* dwarf = GetPawn();
        if(mPlayer == nullptr || dwarf == nullptr)
        {
            return;
        }
        if(mRange < FVector::Dist(mPlayer->GetActorLocation(), dwarf->GetActorLocation()))
        {
            ChasePlayer();
        }
        else {
        }
    }
    
}

void ADwarfAIController::ChasePlayer()
{
    Cast<ADwarfCharacter>(GetPawn())->StopAttack();
    MoveToActor(mPlayer);
    mState = Chase;
}

void ADwarfAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if(Result.IsSuccess())
    {
        mState = Attack;
        (Cast<ADwarfCharacter>(GetPawn()))->StartAttack();
    }
    else
    {
        mState = Chase;
        (Cast<ADwarfCharacter>(GetPawn()))->StopAttack();
    }
}
