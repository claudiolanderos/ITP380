#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mAngularSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mYawAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
    if(!Math::IsZero(mYawAxis) || !Math::IsZero(mPitchAxis)){
        Quaternion rotation = mOwner.GetRotation();
        float incrementalYaw = mAngularSpeed * mYawAxis * deltaTime;
        float incrementalPitch = mPitchSpeed * mPitchAxis * deltaTime;
        Quaternion incrementalPitchQuaternion(mOwner.GetWorldTransform().GetYAxis(), incrementalPitch);
        Quaternion incrementalYawQuaternion(mOwner.GetWorldTransform().GetZAxis(), incrementalYaw);
        rotation = Concatenate(rotation, incrementalYawQuaternion);
        rotation =  Concatenate(rotation, incrementalPitchQuaternion);
        mOwner.SetRotation(rotation);
    }
    if (!Math::IsZero(mLinearAxis))
    {
        // Update velocity based on current forward
        mVelocity = mOwner.GetForward();
        mVelocity *= mLinearSpeed;
        mVelocity *= mLinearAxis;
        
        // Update position of owner based on velocity
        Vector3 position = mOwner.GetPosition();
        position += mVelocity*deltaTime;
        
        mOwner.SetPosition(position);
    }
}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToYawAxis(float delta)
{
	mYawAxis += delta;
	mYawAxis = Math::Clamp(mYawAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToPitchAxis(float delta)
{
    mYawAxis += delta;
    mYawAxis =  Math::Clamp(mYawAxis, -1.0f, 1.0f);
}

void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetYawAxis(float axis)
{
	mYawAxis = Math::Clamp(axis, -1.0f, 1.0f);
}
