//
//  InputComponent.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
    DECL_COMPONENT(InputComponent, Component);

public:
    InputComponent(Actor &owner);
    
    void BindLinearAxis(const std::string& name);
    
    void BindYawAxis(const std::string& name);
    
    void BindPitchAxis(const std::string& name);
    
    void OnPitchAxis(float value);
    
    void OnLinearAxis(float value);
    
    void OnYawAxis(float value);
};
DECL_PTR(InputComponent);
