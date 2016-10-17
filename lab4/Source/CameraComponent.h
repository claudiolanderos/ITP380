//
//  CameraComponent.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Component.h"

class CameraComponent : public Component
{
    DECL_COMPONENT(CameraComponent, Component);
public:
    CameraComponent(Actor& owner);
    
    void Tick(float deltaTime) override;
private:
    
};
DECL_PTR(CameraComponent);
