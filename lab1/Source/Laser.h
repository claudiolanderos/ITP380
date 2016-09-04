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

class Laser : public Actor
{
    DECL_ACTOR(Laser, Actor);
public:
    Laser(Game& game);
    
    void Tick(float deltaTime) override;
    
    void BeginTouch(Actor& other) override;
    
private:
    float mLifeSpan;
    TexturePtr tex;
};
DECL_PTR(Laser);