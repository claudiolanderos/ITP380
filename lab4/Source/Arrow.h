//
//  Arrow.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/17/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "Mesh.h"

class Arrow : public Actor
{
    DECL_ACTOR(Arrow, Actor);
public:
    Arrow(Game& game);
    
    void SetActor(ActorPtr actor) { mActor = actor; }
    
    void SetLocation(const Vector3& pos) { mLocation = pos; }
    
    void UpdatePosition();
    
    void BeginPlay() override;
    
    void Tick(float deltaTime) override;
private:
    MeshPtr mMesh;
    
    ActorPtr mActor;
    
    Vector3 mLocation;
};
DECL_PTR(Arrow);
