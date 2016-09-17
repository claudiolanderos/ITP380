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
#include "MeshComponent.h"
#include "Mesh.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game)
    :Actor(game)
{
    mMeshComponent = MeshComponent::Create(*this);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/PlayerShip.itpmesh2");
    mMeshComponent->SetMesh(mMesh);
    SetScale(0.5f);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    //Load sound
    mSoundPtr = game.GetAssetCache().Load<Sound>("Sounds/Laser.wav");
    mSoundCue = mAudioComponent->PlaySound(game.GetAssetCache().Load<Sound>("Sounds/ShipEngine.wav"), true);
    
    mInputComponent = InputComponent::Create(*this, Component::PreTick);
    mInputComponent->SetAngularSpeed(Math::TwoPi);
    mInputComponent->SetLinearSpeed(400.0f);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromMesh(mMesh);
    coll->SetScale(0.75f);
}

void Ship::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    if(Math::IsZero(mInputComponent->GetLinearAxis()))
    {
        mSoundCue.Pause();
    }
    else
    {
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
        mMeshComponent->SetIsVisible(false);
        TimerHandle handle;
        mGame.GetGameTimers().SetTimer(handle, this, &Ship::OnRespawnShip, 1.0f);
    }
}

void Ship::OnRespawnShip()
{
    SetIsPaused(false);
    mMeshComponent->SetIsVisible(true);
    SetPosition(Vector3::Zero);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
}