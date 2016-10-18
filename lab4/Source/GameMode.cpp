#include "GameMode.h"
#include "Game.h"
#include "Checkpoint.h"
#include "Random.h"
#include "Asteroid.h"

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game)
	:Super(game)
{
}

GameMode::~GameMode()
{
    mShip = nullptr;
}
void GameMode::StartGame()
{
    const int NUM_ASTEROIDS = 500;
    Vector3 minVec(-5000.0f, -5000.0f, -5000.0f);
    Vector3 maxVec(5000.0f, 5000.0f, 5000.0f);
    for (int i = 0; i < NUM_ASTEROIDS; i++)
    {
        auto ast = Asteroid::Spawn(mGame);
        ast->SetPosition(Random::GetVector(minVec, maxVec));
    }
    
    mShip = Ship::Spawn(mGame);
    mArrow = Arrow::Spawn(mGame);
    mArrow->SetActor(mShip);
    mHUD = HUD::Spawn(mGame);
    mGame.GetGameTimers().SetTimer(timeHandle, this, &GameMode::EndGame, 15.0f, false);
    mHUD->SetTime(timeHandle);
    SpawnCheckpoint();
}

void GameMode::EndGame()
{
    mHUD->GameOver();
}
void GameMode::SpawnCheckpoint()
{
    auto checkpoint = Checkpoint::Spawn(mGame);
    Vector3 minVec = mShip->GetPosition();
    minVec.x -= 1000.0f + range;
    minVec.y -= 1000.0f + range;
    minVec.z -= 1000.0f + range;
    
    Vector3 maxVec = mShip->GetPosition();
    maxVec.x += 1000.0f + range;
    maxVec.y += 1000.0f + range;
    maxVec.z += 1000.0f + range;
    
    range += 10;
    
    Vector3 position = Random::GetVector(minVec, maxVec);
    checkpoint->SetPosition(position);
    mArrow->SetLocation(position);
}

void GameMode::CollectCheckPoint()
{
    mGame.GetGameTimers().AddTime(timeHandle, 5.0f);
    mHUD->AddScore(1000);
    mAudioComponent->PlaySound(mGame.GetAssetCache().Load<Sound>("Sounds/Checkpoint.wav"), false);
    SpawnCheckpoint();
}
