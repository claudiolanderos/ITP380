//
//  Checkpoint.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/17/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "Mesh.h"

class Checkpoint : public Actor
{
    DECL_ACTOR(Checkpoint, Actor);
public:
    Checkpoint(Game& game);
    
private:
    MeshPtr mMesh;
};
DECL_PTR(Checkpoint);
