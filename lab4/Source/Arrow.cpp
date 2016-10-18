//
//  Arrow.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/17/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Arrow.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"

IMPL_ACTOR(Arrow, Actor);

Arrow::Arrow(Game& game)
:Actor(game)
{
    auto sprite = MeshComponent::Create(*this);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/Arrow.itpmesh2");
    sprite->SetMesh(mMesh);
    SetScale(0.5f);
}

void Arrow::UpdatePosition()
{
    Vector3 position = mGame.GetRenderer().Unproject(Vector3(0.0f, 150.0f, 0.6f));
    SetPosition(position);
}

void Arrow::BeginPlay()
{
    UpdatePosition();
}

void Arrow::Tick(float deltaTime)
{
    UpdatePosition();
    Vector3 direction = mLocation - mActor->GetPosition();
    direction.Normalize();
    Vector3 axis = Cross(Vector3::UnitX, direction);
    axis.Normalize();
    if(Math::IsZero(axis.LengthSq()))
    {
        SetRotation(Quaternion::Identity);
        return;
    }
    float angle = Dot(Vector3::UnitX, direction);
    angle = acos(angle);
    SetRotation(Quaternion(axis, angle));
}
