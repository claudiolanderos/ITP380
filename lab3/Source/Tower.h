//
//  Tower.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "Mesh.h"

class Tower : public Actor
{
    DECL_ACTOR(Tower, Actor);
public:
    Tower(Game& game);
    
private:
    MeshPtr mMesh;
};
DECL_PTR(Tower);
