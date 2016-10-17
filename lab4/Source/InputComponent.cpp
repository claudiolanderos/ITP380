//
//  InputComponent.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "InputComponent.h"
#include "Actor.h"
#include "Game.h"

IMPL_COMPONENT(InputComponent, MoveComponent);

InputComponent::InputComponent(Actor& owner)
    : MoveComponent(owner)
{
}

void InputComponent::BindLinearAxis(const std::string &name)
{
    mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnLinearAxis);
}

void InputComponent::BindYawAxis(const std::string &name)
{
    mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnYawAxis);
}

void InputComponent::OnLinearAxis(float value)
{
    SetLinearAxis(value);
}

void InputComponent::OnYawAxis(float value)
{
    SetYawAxis(value);
}

void InputComponent::BindPitchAxis(const std::string &name)
{
    mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnPitchAxis);
}

void InputComponent::OnPitchAxis(float value)
{
    SetPitchAxis(value);
}
