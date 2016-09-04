//
//  Ship.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "MoveComponent.h"
#include "Laser.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game)
    :Actor(game)
{
    mSpriteComponentPtr = SpriteComponent::Create(*this);
    mNoThrusterTexture = game.GetAssetCache().Load<Texture>("Textures/Spaceship.png");
    mThrusterTexture = game.GetAssetCache().Load<Texture>("Textures/SpaceshipWithThrust.png");
    mSpriteComponentPtr->SetTexture(mNoThrusterTexture);
    
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    
    mMoveComponentPtr = MoveComponent::Create(*this, Component::PreTick);
    mMoveComponentPtr->SetAngularSpeed(Math::TwoPi);
    mMoveComponentPtr->SetLinearSpeed(400.0f);
}

void Ship::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    if(Math::IsZero(mMoveComponentPtr->GetLinearAxis()))
    {
        mSpriteComponentPtr->SetTexture(mNoThrusterTexture);
    }
    else
    {
        mSpriteComponentPtr->SetTexture(mThrusterTexture);
    }
}

void Ship::FireMissile()
{
    auto laser = Laser::Spawn(mGame);
    laser->SetPosition(this->GetPosition());
    laser->SetRotation(this->GetRotation());
}