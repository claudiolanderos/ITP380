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
#include "Sound.h"
#include "SphereCollision.h"
#include "Asteroid.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "CameraComponent.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game)
    :Actor(game)
{
    mMeshComponent = MeshComponent::Create(*this);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/PlayerShip.itpmesh2");
    mMeshComponent->SetMesh(mMesh);

    //Load sound
    mSoundCue = mAudioComponent->PlaySound(game.GetAssetCache().Load<Sound>("Sounds/ShipEngine.wav"), true);
    
    mInputComponent = InputComponent::Create(*this, Component::PreTick);
    mInputComponent->SetAngularSpeed(Math::Pi);
    mInputComponent->SetLinearSpeed(400.0f);
    
    mCameraComponent = CameraComponent::Create(*this);
    mCameraComponent->SetMoveComponent(mInputComponent);
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromMesh(mMesh);
    coll->SetScale(1.0f);
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
}

void Ship::BeginPlay()
{
    mGame.GetInput().BindAction("Fire", IE_Pressed, this, &Ship::FireMissile);
    mInputComponent->BindLinearAxis("Move");
    mInputComponent->BindAngularAxis("Rotate");
    mCameraComponent->SnapToIdealPosition();
}

void Ship::BeginTouch(Actor& other)
{
    Super::BeginTouch(other);
}

void Ship::OnRespawnShip()
{
    SetIsPaused(false);
    mMeshComponent->SetIsVisible(true);
    SetPosition(Vector3::Zero);
}
