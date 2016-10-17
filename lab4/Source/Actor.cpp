#include "Actor.h"
#include "Game.h"

IMPL_ACTOR(Actor, Object);

Actor::Actor(Game& game)
	:mGame(game)
	,mParent(nullptr)
	,mScale(1.0f)
	,mRotation()
	,mIsAlive(true)
    ,mIsPaused(false)
{

}

Actor::~Actor()
{
	RemoveAllChildren();
	RemoveAllComponents();
    mGame.GetGameTimers().ClearAllTimers(this);
}

void Actor::BeginPlay()
{

}

void Actor::Tick(float deltaTime)
{

}

void Actor::EndPlay()
{

}

void Actor::BeginTouch(Actor& other)
{

}

void Actor::AddComponent(ComponentPtr component, Component::UpdateType update)
{
	component->Register();
	if (update == Component::PostTick)
	{
		mPostTickComponents.emplace(component);
	}
	else
	{
		mPreTickComponents.emplace(component);
	}
}

void Actor::RemoveComponent(ComponentPtr component)
{
	component->Unregister();

	// This may be pre-tick or post-tick
	auto iter = mPreTickComponents.find(component);
	if (iter != mPreTickComponents.end())
	{
		mPreTickComponents.erase(component);
	}

	iter = mPostTickComponents.find(component);
	if (iter != mPreTickComponents.end())
	{
		mPostTickComponents.erase(component);
	}
}

void Actor::AddChild(ActorPtr child)
{
	mChildren.emplace(child);
	child->mParent = this;
	// Force the child to compute their transform matrix
	child->ComputeWorldTransform();
}

void Actor::RemoveChild(ActorPtr child)
{
	auto iter = mChildren.find(child);
	if (iter != mChildren.end())
	{
		(*iter)->EndPlay();
		mChildren.erase(iter);
	}
	child->mParent = nullptr;
}

Vector3 Actor::GetForward() const
{
	// Following Unreal coordinate system so X is forward
	return mWorldTransform.GetXAxis();
}

void Actor::ComputeWorldTransform()
{
	// TODO
    Matrix4 scaleMat = Matrix4::CreateScale(this->GetScale());
    Matrix4 rotationMat = Matrix4::CreateFromQuaternion(this->GetRotation());
    Matrix4 translationMat = Matrix4::CreateTranslation(this->GetPosition());
    mWorldTransform = scaleMat*rotationMat*translationMat;
    
    // No parent is the base case
    if (mParent)
    {
        // My transform * Parent's transform
        mWorldTransform *= mParent->GetWorldTransform();
    }
    // Tell my children to recompute their transforms
    for (auto& child : mChildren)
    {
        child->ComputeWorldTransform();
    }
}

void Actor::TickInternal(float deltaTime)
{
    if(mIsPaused == true)
    {
        return;
    }
    for(ComponentPtr component : mPreTickComponents){
        component->Tick(deltaTime);
    }
    
    Tick(deltaTime);
    
    for(ComponentPtr component : mPostTickComponents){
        component->Tick(deltaTime);
    }
    
    for(ActorPtr actor : mChildren){
        actor->TickInternal(deltaTime);
    }
    
}

void Actor::RemoveAllComponents()
{
	// Unregister everything first
	for (auto& comp : mPreTickComponents)
	{
		comp->Unregister();
	}

	for (auto& comp : mPostTickComponents)
	{
		comp->Unregister();
	}

	mPreTickComponents.clear();
	mPostTickComponents.clear();
}

void Actor::RemoveAllChildren()
{
	for (auto& child : mChildren)
	{
		child->EndPlay();
		child->mParent = nullptr;
	}

	mChildren.clear();
}
