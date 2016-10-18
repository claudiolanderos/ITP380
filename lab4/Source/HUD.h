//
//  HUD.hpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "FontComponent.h"
#include "GameTimers.h"

class HUD : public Actor
{
    DECL_ACTOR(HUD, Actor);
    
public:
    HUD(Game& game);
    
    void GameOver() { mGameOver = true; }
    
    void AddScore(int score) { mScore += score; }
    
    void SetTime(TimerHandle handle) { mHandle = handle; }
    
    void Tick(float deltaTime) override;
private:
    FontComponentPtr mScoreFont;
    FontComponentPtr mTimeFont;
    FontComponentPtr mGameOverFont;
    
    ActorPtr mScoreChild;
    ActorPtr mTimeChild;
    ActorPtr mGameOverChild;
    
    int mScore;
    bool mGameOver = false;
    TimerHandle mHandle;
};
DECL_PTR(HUD);
