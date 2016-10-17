//
//  Sound.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 9/14/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "Sound.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>

Sound::Sound()
{
    mData = nullptr;
}

Sound::~Sound()
{
    if(mData != nullptr)
    {
        Mix_FreeChunk(mData);
    }
}

bool Sound::Load(const char *fileName, class AssetCache *cache)
{
    mData = Mix_LoadWAV(fileName);
    
    if(mData == nullptr)
    {
        SDL_Log("Could not load sound");
        return false;
    }
    return true;
}