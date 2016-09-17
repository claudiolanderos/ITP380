#include "SphereCollision.h"
#include "Actor.h"

IMPL_COMPONENT(SphereCollision, CollisionComponent);

SphereCollision::SphereCollision(Actor& owner)
	:CollisionComponent(owner)
	,mOriginalRadius(1.0f)
	,mActualRadius(1.0f)
	,mScale(1.0f)
{

}

void SphereCollision::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	// Update the radius/center from our owning component

    // Scale the radius by the world transform scale
    // (It’s safe to assume the scale is uniform, because
    // actors don't allow non-uniform scaling)
    Vector3 scaleVec = mOwner.GetWorldTransform().GetScale();
    mActualRadius = mOriginalRadius * mScale * scaleVec.x;
    mCenter = mOwner.GetWorldTransform().GetTranslation();
}

bool SphereCollision::Intersects(CollisionComponentPtr other)
{
	// TODO
    if (IsA<SphereCollision>(other))
    {
        return IntersectsSphere(Cast<SphereCollision>(other));
    }
	return false;
}

void SphereCollision::RadiusFromTexture(TexturePtr texture)
{
	mOriginalRadius = static_cast<float>(Math::Max(texture->GetHeight() / 2, 
		texture->GetHeight() / 2));
}

void SphereCollision::RadiusFromMesh(MeshPtr mesh)
{
    mOriginalRadius = mesh->GetRadius();
}
bool SphereCollision::IntersectsSphere(SphereCollisionPtr other)
{
    // Calculate the difference vector between the centers
    Vector3 diff = other->mCenter - mCenter;
    // Calculate the distance squared
    float distSq = diff.LengthSq();
    // Calculate the sum of radii squared
    float sumRadiiSq = (mActualRadius + other->mActualRadius) *
    (mActualRadius + other->mActualRadius);
    
    // Did they collide?
    return (distSq <= sumRadiiSq);
}
