//
//  Laser.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Laser.h"
#include "Game.h"
#include "SphereCollision.h"
#include "Asteroid.h"
#include "SpriteComponent.h"

IMPL_ACTOR(Laser, Actor);

Laser::Laser(Game& game)
    :Actor(game)
{
    auto sprite = SpriteComponent::Create(*this);
    tex = game.GetAssetCache().Load<Texture>("Textures/Laser.png");
    sprite->SetTexture(tex);
    
    auto move = MoveComponent::Create(*this, Component::PreTick);
    move->SetLinearSpeed(600.0f);
    move->SetLinearAxis(1.0f);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromTexture(tex);
    coll->SetScale(0.9f);
}

void Laser::Tick(float deltaTime)
{

}

void Laser::BeginPlay()
{
    TimerHandle handle;
    mGame.GetGameTimers().SetTimer(handle, this, &Laser::OnDieTimer, 1.0f);
}
void Laser::OnDieTimer()
{
    SetIsAlive(false);
}

void Laser::BeginTouch(Actor &other)
{
    Super::BeginTouch(other);
    
    if(this->IsAlive() && IsA<Asteroid>(other))
    {
        this->SetIsAlive(false);
        other.SetIsAlive(false);
        
        mAudioComponent->PlaySound(mGame.GetAssetCache().Load<Sound>("Sounds/AsteroidDie.wav"));
        if(other.GetScale() == 0.75f)
        {
            for(int i = 0; i < 4; i++)
            {
                auto asteroid = Asteroid::Spawn(mGame);
                asteroid->SetPosition(this->GetPosition());
                asteroid ->SetScale(0.25f);
            }
        }
    }
}