//
//  Ship.h
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "Texture.h"
#include "SpriteComponent.h"

class Ship : public Actor
{
    DECL_ACTOR(Ship, Actor);
public:
    Ship(Game& game);
    
    MoveComponentPtr GetMoveComponent() const { return mMoveComponentPtr; }
    
    void Tick(float deltaTime) override;
    
    void FireMissile();
private:
    MoveComponentPtr mMoveComponentPtr;
    TexturePtr mThrusterTexture;
    TexturePtr mNoThrusterTexture;
    SpriteComponentPtr mSpriteComponentPtr;
};
DECL_PTR(Ship);
