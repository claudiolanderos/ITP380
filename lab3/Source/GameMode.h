#pragma once
#include "Actor.h"
#include "Tile.h"
#include "AudioComponent.h"
#include "Spawner.h"

class GameMode : public Actor
{
	DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

	void BeginPlay() override;
	void EndPlay() override;

    // Get the position that enemies should spawn from
	const Vector3& GetSpawnPos() const;

    // Handle mouse click selection
	void HandleSelect();

    // Return the requested tile at the (x, y) index
    // in the grid of tiles
	TilePtr GetTile(const Vector2& gridPos);
private:
    // Create the tiles
	void CreateTiles();

    // All of the tiles in the grid
	std::vector<std::vector<TilePtr>> mTiles;
    // Current selected tile, or nullptr if none
	TilePtr mSelectedTile;
    
    SpawnerPtr mSpawner;
    
    void SpawnFrostTower();
    void SpawnCannonTower();
};

DECL_PTR(GameMode);
