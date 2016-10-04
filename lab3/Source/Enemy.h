//
//  Enemy.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/28/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "SphereCollision.h"

class Enemy : public Actor
{
    DECL_ACTOR(Enemy, Actor);
public:
    Enemy(Game& game);
    
    void BeginTouch(Actor& other) override;
    
    void BeginPlay() override;
    
    void EndPlay() override;
    
    void Slow();
    
    void UnSlow();
private:
    MeshPtr mMesh;
    MeshComponentPtr mMeshComponent;
    MoveComponentPtr mMoveComponent;
    SphereCollisionPtr mSphereCollision;
};
DECL_PTR(Enemy);
