#include "Game.h"
#include <SDL/SDL.h>
#include "Texture.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "Asteroid.h"
#include <SDL/SDL_mixer.h>

Game::Game()
	:mRenderer(*this)
	,mAssetCache(*this, "Assets/")
	,mShouldQuit(false)
{

}

Game::~Game()
{
    mShipPtr = nullptr;
	mAssetCache.Clear();
	mWorld.RemoveAllActors();
    Mix_CloseAudio();
	SDL_Quit();
}

bool Game::Init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL.");
		return false;
	}

	// Initialize Renderer
	if (!mRenderer.Init(1024, 768))
	{
		SDL_Log("Failed to initialize renderer.");
		return false;
	}

    //Initialize sound
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
    {
        SDL_Log("Failed to initialize sound.");
        return false;
    }
    
	// Initialize RNG
	Random::Init();

	// Start frame timer
	mTimer.Start();
    
    //Add mappings
    AddInputMappings();

	// Run any code at game start
	StartGame();

	return true;
}

void Game::RunLoop()
{
	// TODO
    while (!mShouldQuit)
    {
        // TODO: Code will go here!
        ProcessInput();
        Tick();
        GenerateOutput();
        
    }
}

void Game::Quit()
{
	// TODO
    mShouldQuit = true;
}

void Game::StartGame()
{
	// TODO
    const int NUM_ASTEROIDS = 10;
    Vector3 minVec(-512.0f, -384.0f, 0.0f);
    Vector3 maxVec(512.f, 384.f, 0.0f);
    for (int i = 0; i < NUM_ASTEROIDS; i++)
    {
        auto ast = Asteroid::Spawn(*this);
        ast->SetPosition(Random::GetVector(minVec, maxVec));
        ast->SetScale(0.75f);
    }
    
    mShipPtr = Ship::Spawn(*this);
    mShipPtr->SetRotation(Math::PiOver2);
}

void Game::ProcessInput()
{
	// TODO
    // Poll events from SDL
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mShouldQuit = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.repeat == 0)
                {
                    HandleKeyPressed(event.key.keysym.sym);
                }
                break;
            case SDL_KEYUP:
                HandleKeyReleased(event.key.keysym.sym);
                break;
            default:
                // Ignore other events for now
                break;
        }
    }
}

void Game::HandleKeyPressed(int key)
{
    mInput.HandleKeyPressed(key);
}

void Game::HandleKeyReleased(int key)
{
    mInput.HandleKeyReleased(key);
}

void Game::Tick()
{
    float deltaTime = mTimer.GetFrameTime(0.016666f);
    mGameTimerManager.Tick(deltaTime);
    mWorld.Tick(deltaTime);
    mPhysWorld.Tick(deltaTime);
}

void Game::GenerateOutput()
{
    mRenderer.RenderFrame();
}

void Game::AddInputMappings()
{
    mInput.AddActionMapping("Quit", SDLK_ESCAPE);
    mInput.BindAction("Quit", IE_Released, this, &Game::Quit);
    mInput.AddActionMapping("Fire", SDLK_SPACE);
    mInput.AddAxisMapping("Move", 'w', 's');
    mInput.AddAxisMapping("Rotate", 'a', 'd');
}
