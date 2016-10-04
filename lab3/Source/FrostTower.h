//
//  FrostTower.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Tower.h"
#include "Mesh.h"

class FrostTower : public Tower
{
    DECL_ACTOR(FrostTower, Tower);
public:
    FrostTower(Game& game);
    
private:
    void FreezeEnemies();

    MeshPtr mMesh;
    ActorPtr mChild;
};
DECL_PTR(FrostTower);
