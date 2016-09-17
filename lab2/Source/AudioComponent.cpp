//
//  AudioComponent.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "AudioComponent.h"
#include "Actor.h"
#include <SDL/SDL_mixer.h>

IMPL_COMPONENT(AudioComponent, Component);

SoundCue::SoundCue()
{
    mChannel = -1;
}

SoundCue::SoundCue(int channel)
{
    mChannel = channel;
}

void SoundCue::Pause()
{
    if(mChannel != -1)
    {
        Mix_Pause(mChannel);
    }
}

void SoundCue::Resume()
{
    if(mChannel != -1)
    {
        Mix_Resume(mChannel);
    }
}

void SoundCue::Stop()
{
    if(mChannel != -1)
    {
        Mix_HaltChannel(mChannel);
    }
}

bool SoundCue::IsPlaying()
{
    if(mChannel != -1)
    {
        return Mix_Playing(mChannel);
    }
    
    return false;
}

bool SoundCue::IsPaused()
{
    if(mChannel != -1)
    {
        return !Mix_Playing(mChannel);
    }
    
    return false;
}

AudioComponent::AudioComponent(Actor& owner)
    :Component(owner)
{
    
}

SoundCue AudioComponent::PlaySound(SoundPtr sound, bool looping)
{
    int channel;
    if(looping == true)
    {
        channel = Mix_PlayChannel(-1, sound->GetData(), -1);
    }
    else
    {
        channel = Mix_PlayChannel(-1, sound->GetData(), 0);
    }
    
    return SoundCue(channel);
}