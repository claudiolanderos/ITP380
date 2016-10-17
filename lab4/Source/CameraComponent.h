//
//  CameraComponent.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "MoveComponent.h"

class CameraComponent : public Component
{
    DECL_COMPONENT(CameraComponent, Component);
public:
    CameraComponent(Actor& owner);
    
    void Tick(float deltaTime) override;
    
    void SetMoveComponent(MoveComponentPtr moveComponent) { mMoveComponent = moveComponent; }
    
    Vector3 GetIdealPosition();
    
    void SnapToIdealPosition();

private:
    MoveComponentPtr mMoveComponent;
    
    Vector3 mActualPosition;
    
    Vector3 mVelocity;
};
DECL_PTR(CameraComponent);
