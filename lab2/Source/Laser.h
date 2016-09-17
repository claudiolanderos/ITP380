//
//  Laser.h
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "Texture.h"
#include "AudioComponent.h"

class Laser : public Actor
{
    DECL_ACTOR(Laser, Actor);
public:
    Laser(Game& game);
    
    void Tick(float deltaTime) override;
    
    void BeginTouch(Actor& other) override;
    
    void OnDieTimer();
    
    void BeginPlay() override;
    
private:
    TexturePtr tex;
    AudioComponentPtr mAudioComponent;
};
DECL_PTR(Laser);