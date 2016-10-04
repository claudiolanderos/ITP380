//
//  CannonTower.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Tower.h"
#include "Mesh.h"

class CannonTower : public Tower
{
    DECL_ACTOR(CannonTower, Tower);
public:
    CannonTower(Game& game);
    
private:
    MeshPtr mMesh;
    ActorPtr mChild;
};
DECL_PTR(CannonTower);
