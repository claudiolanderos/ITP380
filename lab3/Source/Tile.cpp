#include "Tile.h"
#include "Game.h"

IMPL_ACTOR(Tile, Actor);

Tile::Tile(Game& game)
	:Actor(game)
	,mState(Default)
	,mIsOnPath(false)
{
    mTower = nullptr;
	mMesh = MeshComponent::Create(*this);
	auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Tile.itpmesh2");
	mMesh->SetMesh(mesh);
}

void Tile::SetState(State state)
{
	mState = state;
	int value = static_cast<int>(mState);
	if (mIsOnPath)
	{
		value += 4;
	}
	mMesh->SetTextureIndex(value);
}


void Tile::SetOnPath(bool value)
{
	mIsOnPath = value;
	SetState(mState);
}
