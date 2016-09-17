//
//  MeshComponent.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "MeshComponent.h"
#include "Renderer.h"
#include "Actor.h"

IMPL_COMPONENT(MeshComponent, DrawComponent);

MeshComponent::MeshComponent(Actor& owner)
    : DrawComponent(owner)
{
    
}

void MeshComponent::Draw(class Renderer &render)
{
    if(mMesh != nullptr)
    {
        render.DrawBasicMesh(mMesh->GetVertexArray(), mMesh->GetTexture(0), mOwner.GetWorldTransform());
    }
}