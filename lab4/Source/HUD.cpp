//
//  HUD.cpp
//  Game-mac
//
//  Created by Claudio Landeros on 10/16/16.
//  Copyright © 2016 Sanjay Madhav. All rights reserved.
//

#include "HUD.h"
#include "Game.h"

IMPL_ACTOR(HUD, Actor);

HUD::HUD(Game& game)
:Actor(game)
{
    mScoreFont = FontComponent::Create(*this);
    mTimeFont = FontComponent::Create(*this);
    mGameOverFont = FontComponent::Create(*this);
    auto font = game.GetAssetCache().Load<Font>("Fonts/Carlito-Regular.ttf");
    mScoreFont->SetFont(font);
    mTimeFont->SetFont(font);
    mGameOverFont->SetFont(font);
    
    mScoreChild = Actor::SpawnAttached(*this);
    mTimeChild = Actor::SpawnAttached(*this);
    mGameOverChild = Actor::SpawnAttached(*this);
    
    Vector3 pos = Vector3(300.0f, 300.0f, 300.0f);
    mScoreChild->SetPosition(pos);
}

void HUD::Tick(float deltaTime)
{
    if(mGameOver)
    {
        mGameOverFont->SetText("Game Over!", Color::Red);
        mTimeFont->SetText("0", Color::Green);
        return;
    }
    mScoreFont->SetText(std::to_string(mScore), Color::White);
    mTimeFont->SetText(std::to_string((int)mGame.GetGameTimers().GetRemainingTime(mHandle)), Color::Green);
}
