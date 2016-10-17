//
//  HUD.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

class HUD : public Actor
{
    DECL_ACTOR(HUD, Actor);
    
public:
    HUD(Game& game);
private:
    
};
DECL_PTR(HUD);
