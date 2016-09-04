//
//  Asteroid.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "Texture.h"

class Asteroid : public Actor
{
    DECL_ACTOR(Asteroid, Actor);
public:
    Asteroid(Game& game);
private:
    TexturePtr tex;
};
DECL_PTR(Asteroid);
