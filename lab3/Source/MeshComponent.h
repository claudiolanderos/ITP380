//
//  MeshComponent.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "DrawComponent.h"
#include "Mesh.h"

class MeshComponent : public DrawComponent
{
    DECL_COMPONENT(MeshComponent, DrawComponent);

public:
    MeshComponent(Actor& owner);
    
    void Draw(class Renderer& render) override;
    
    void SetMesh(MeshPtr mesh) { mMesh = mesh; }
    
    MeshPtr GetMesh() const { return mMesh; }
    
    void SetTextureIndex(int textureIndex) { mTextureIndex = textureIndex; }
private:
    MeshPtr mMesh;
    int mTextureIndex;
    
};
DECL_PTR(MeshComponent);
