//
//  Ship.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Ship.h"
#include "Game.h"
#include "Random.h"
#include "MoveComponent.h"
#include "Laser.h"
#include "Sound.h"
#include "SphereCollision.h"
#include "Asteroid.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game)
    :Actor(game)
{
    mSpriteComponentPtr = SpriteComponent::Create(*this);
    mNoThrusterTexture = game.GetAssetCache().Load<Texture>("Textures/Spaceship.png");
    mThrusterTexture = game.GetAssetCache().Load<Texture>("Textures/SpaceshipWithThrust.png");
    mSpriteComponentPtr->SetTexture(mNoThrusterTexture);
    
    //Load sound
    mSoundPtr = game.GetAssetCache().Load<Sound>("Sounds/Laser.wav");
    mSoundCue = mAudioComponent->PlaySound(game.GetAssetCache().Load<Sound>("Sounds/ShipEngine.wav"), true);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    
    mInputComponent = InputComponent::Create(*this, Component::PreTick);
    mInputComponent->SetAngularSpeed(Math::TwoPi);
    mInputComponent->SetLinearSpeed(400.0f);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromTexture(mThrusterTexture);
    coll->SetScale(0.75f);
}

void Ship::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    if(Math::IsZero(mInputComponent->GetLinearAxis()))
    {
        mSpriteComponentPtr->SetTexture(mNoThrusterTexture);
        mSoundCue.Pause();
    }
    else
    {
        mSpriteComponentPtr->SetTexture(mThrusterTexture);
        mSoundCue.Resume();
    }
}

void Ship::FireMissile()
{
    auto laser = Laser::Spawn(mGame);
    laser->SetPosition(this->GetPosition());
    laser->SetRotation(this->GetRotation());
    mAudioComponent->PlaySound(mSoundPtr);
}

void Ship::BeginPlay()
{
    mGame.GetInput().BindAction("Fire", IE_Pressed, this, &Ship::FireMissile);
    mInputComponent->BindLinearAxis("Move");
    mInputComponent->BindAngularAxis("Rotate");
}

void Ship::BeginTouch(Actor& other)
{
    Super::BeginTouch(other);
    
    if(this->IsPaused() == false && IsA<Asteroid>(other))
    {
        mAudioComponent->PlaySound(mGame.GetAssetCache().Load<Sound>("Sounds/ShipDie.wav"));
        this->SetIsPaused(true);
        mSpriteComponentPtr->SetIsVisible(false);
        TimerHandle handle;
        mGame.GetGameTimers().SetTimer(handle, this, &Ship::OnRespawnShip, 1.0f);
    }
}

void Ship::OnRespawnShip()
{
    SetIsPaused(false);
    mSpriteComponentPtr->SetIsVisible(true);
    SetPosition(Vector3::Zero);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
}