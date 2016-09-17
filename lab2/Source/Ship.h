//
//  Ship.h
//  Game-mac
//
//  Created by Claudio Landeros on 9/3/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "InputComponent.h"
#include "Texture.h"
#include "MeshComponent.h"
#include "AudioComponent.h"

class Ship : public Actor
{
    DECL_ACTOR(Ship, Actor);
public:
    Ship(Game& game);
    
    InputComponentPtr GetMoveComponent() const { return mInputComponent; }
    
    void Tick(float deltaTime) override;
    
    void FireMissile();
    
    void OnRespawnShip();
    
    void BeginPlay() override;
    
    void BeginTouch(Actor& other) override;
private:
    InputComponentPtr mInputComponent;
    MeshComponentPtr mMeshComponent;
    AudioComponentPtr mAudioComponent;
    SoundPtr mSoundPtr;
    SoundCue mSoundCue;
    MeshPtr mMesh;
};
DECL_PTR(Ship);
