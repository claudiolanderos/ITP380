//
//  CannonBall.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "Mesh.h"
#include "SphereCollision.h"

class CannonBall : public Actor
{
    DECL_ACTOR(CannonBall, Actor);

public:
    CannonBall(Game& game);
    
    void OnDieTimer();
    
    void BeginPlay() override;
private:
    MoveComponentPtr mMoveComponent;
    MeshPtr mMesh;
    SphereCollisionPtr mSphereCollision;
};
DECL_PTR(CannonBall);
