//
//  CannonTower.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "CannonTower.h"
#include "Game.h"
#include "CannonBall.h"

IMPL_ACTOR(CannonTower, Tower);

CannonTower::CannonTower(Game& game)
    :Tower(game)
{
    mChild = Actor::SpawnAttached(*this);
    auto meshComponent = MeshComponent::Create(*mChild);
    mMesh = game.GetAssetCache().Load<Mesh>("Meshes/Cannon.itpmesh2");
    meshComponent->SetMesh(mMesh);
    
    
    TimerHandle handle;
    game.GetGameTimers().SetTimer(handle, this, &CannonTower::Fire, 1.0f, true);
}

void CannonTower::Fire()
{
    Enemy* enemy = mGame.GetWorld().GetClosesEnemy(this->GetWorldTransform().GetTranslation());
    
    if(enemy != nullptr)
    {
        Vector3 vector = enemy->GetWorldTransform().GetTranslation() - this->GetWorldTransform().GetTranslation();
        vector.Normalize();
        float angle = Dot(vector,Vector3::UnitX);
        //angle += Math::Pi;
        Vector3 cross = Cross(Vector3::UnitX, vector);
        if(cross.z < 0)
        {
            angle *= -1;
        }
        angle = Math::Cos(angle);
        auto ball = CannonBall::Spawn(mGame);
        ball->SetPosition(this->GetWorldTransform().GetTranslation());
        mChild->SetRotation(angle);
        ball->SetRotation(mChild->GetRotation());
    }
}
