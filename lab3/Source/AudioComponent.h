//
//  AudioComponent.h
//  Game-mac
//
//  Created by Claudio Landeros on 9/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Component.h"
#include "Sound.h"

class SoundCue
{
public:
    SoundCue();
    
    SoundCue(int);
    
    void Pause();
    
    void Resume();
    
    void Stop();
    
    bool IsPlaying();
    
    bool IsPaused();
    
private:
    int mChannel;
};

class AudioComponent : public Component
{
    DECL_COMPONENT(AudioComponent, Component);
    
public:
    AudioComponent(Actor& owner);
    
    SoundCue PlaySound(SoundPtr sound, bool looping = false);
    
};
DECL_PTR(AudioComponent);
