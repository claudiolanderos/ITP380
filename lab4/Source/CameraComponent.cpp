//
//  CameraComponent.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "CameraComponent.h"
#include "Game.h"
#include "Actor.h"
#include "Renderer.h"


IMPL_COMPONENT(CameraComponent, Component);

CameraComponent::CameraComponent(Actor& owner)
    :Component(owner)
{
}

void CameraComponent::Tick(float deltaTime)
{
    float fSpringConstant = 128.0f;
    float fDampConstant = 2.0f * sqrt(fSpringConstant);
    Vector3 vIdealPosition = GetIdealPosition();
    Vector3 vDisplacement = mActualPosition - vIdealPosition;
    Vector3 vSpringAccel = (-fSpringConstant * vDisplacement) - (fDampConstant * mVelocity);
    mVelocity += vSpringAccel * deltaTime;
    mActualPosition += mVelocity * deltaTime;
    
    Vector3 vShipPosition = mOwner.GetPosition();
    Vector3 vShipForward = mOwner.GetWorldTransform().GetXAxis();
    vShipForward.Normalize();
    Vector3 vTargetPosition = vShipPosition + vShipForward*150.0f;
    Vector3 vShipUp = mOwner.GetWorldTransform().GetZAxis();
    vShipUp.Normalize();
    Vector3 vCameraForward = vTargetPosition - vIdealPosition;
    vCameraForward.Normalize();
    Vector3 vCameraLeft = vShipUp * vCameraForward;
    vCameraLeft.Normalize();
    Vector3 vCameraUp = vCameraForward * vCameraLeft;
    vCameraUp.Normalize();
    Matrix4 cameraMatrix = Matrix4::CreateLookAt(mActualPosition, vTargetPosition, vCameraUp);
    mOwner.GetGame().GetRenderer().UpdateViewMatrix(cameraMatrix);
}

Vector3 CameraComponent::GetIdealPosition()
{
    Vector3 vShipPosition = mOwner.GetPosition();
    Vector3 vShipForward = mOwner.GetWorldTransform().GetXAxis();
    vShipForward.Normalize();
    Vector3 vShipUp = mOwner.GetWorldTransform().GetZAxis();
    vShipUp.Normalize();
    Vector3 vCameraPosition = vShipPosition - vShipForward*Math::Lerp(300.0f, 350.0f, mMoveComponent->GetLinearAxis()) + vShipUp*100.0f;
    
    return vCameraPosition;
}

void CameraComponent::SnapToIdealPosition()
{
    mActualPosition = GetIdealPosition();
}
