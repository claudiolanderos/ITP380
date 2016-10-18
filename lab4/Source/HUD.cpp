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
    mScoreChild = Actor::SpawnAttached(*this);
    mTimeChild = Actor::SpawnAttached(*this);
    mGameOverChild = Actor::SpawnAttached(*this);
    
    mScoreFont = FontComponent::Create(*mScoreChild);
    mTimeFont = FontComponent::Create(*mTimeChild);
    mGameOverFont = FontComponent::Create(*mGameOverChild);
    
    auto font = game.GetAssetCache().Load<Font>("Fonts/Carlito-Regular.ttf");
    mScoreFont->SetFont(font);
    mTimeFont->SetFont(font);
    mGameOverFont->SetFont(font);
    
    mScoreChild->SetPosition(Vector3(300.0f, 300.0f, 0.0f));
    mTimeChild->SetPosition(Vector3(0.0f, 300.0f, 0.0f));
    mGameOverChild->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
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
