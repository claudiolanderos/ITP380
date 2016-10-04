#include "World.h"

World::World()
{

}

World::~World()
{

}

void World::AddActor(ActorPtr actor)
{
	mActors.emplace_back(actor);
}

void World::Tick(float deltaTime)
{
	// Tick a copy of the actor pointers, in case any actor adds more actors
	auto actors = mActors;
	for (auto& actor : actors)
	{
		actor->TickInternal(deltaTime);
	}

	// Remove any actors that are dead
	auto iter = mActors.begin();
	while (iter != mActors.end())
	{
		if (!(*iter)->IsAlive())
		{
			(*iter)->EndPlay();
			iter = mActors.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void World::RemoveAllActors()
{
	for (auto& actor : mActors)
	{
		actor->EndPlay();
	}
	mActors.clear();
}

void World::AddEnemy(Enemy& enemy)
{
    mEnemies.insert(&enemy);
}

void World::RemoveEnemy(Enemy& enemy)
{
    mEnemies.erase(&enemy);
}

std::vector<Enemy*> World::GetEnemiesInRange(Vector3 position, float radius)
{
    std::vector<Enemy*> inRange;
    for(auto& iter : mEnemies)
    {
        if((position - iter->GetWorldTransform().GetTranslation()).Length() <= radius)
        {
            inRange.push_back(iter);
        }
    }
    return inRange;
}

Enemy* World::GetClosesEnemy(Vector3 position)
{
    float closest = 150.0f;
    float distance;
    Enemy* closestEnemy = nullptr;
    
    for(auto& iter : mEnemies)
    {
        distance = (position - iter->GetWorldTransform().GetTranslation()).Length();
        if(distance < 150.0f && distance < closest)
        {
            closest = distance;
            closestEnemy = iter;
        }
    }
    return closestEnemy;
}
