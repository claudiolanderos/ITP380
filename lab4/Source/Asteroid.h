//
//  Asteroid.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "Mesh.h"

class Asteroid : public Actor
{
    DECL_ACTOR(Asteroid, Actor);
public:
    Asteroid(Game& game);
private:
    MeshPtr mesh;
};
DECL_PTR(Asteroid);
