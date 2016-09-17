//
//  Asteroid.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Asteroid.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "MoveComponent.h"
#include "SphereCollision.h"

IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game)
    :Actor(game)
{
    auto sprite = SpriteComponent::Create(*this);
    tex = game.GetAssetCache().Load<Texture>("Textures/Asteroid.png");
    sprite->SetTexture(tex);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    
    auto move = MoveComponent::Create(*this, Component::PreTick);
    move->SetLinearSpeed(150.0f);
    move->SetLinearAxis(1.0f);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromTexture(tex);
    coll->SetScale(0.9f);
}