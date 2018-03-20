#ifndef _MAESTRO_PHYSICS_ENGINE_
#define _MAESTRO_PHYSICS_ENGINE_

#include "Engine.h"
#include <gmtk/gmtk.h>
#include "RigidBody.h"
#include <map>
#include <list>

namespace mae
{
class Physics: public System
{

	friend class RigidBody;
public:
	Physics(Engine *const engine);

	virtual Component *const OnComponentCreate(EntityHandle srcEnt, std::type_index cmpType) override;

	virtual bool OnComponentDestroy(EntityHandle srcEnt, Component * const srcCmp) override;
	
private:
	float groundedTol = 0.1f;

public:

public:
	struct CollisionPair
	{
		RigidBody *rigidBodyA;
		RigidBody *rigidBodyB;
		friend bool operator<(const CollisionPair& l, const CollisionPair& r)
		{
			return std::tie(l.rigidBodyA, l.rigidBodyB)
				< std::tie(r.rigidBodyA, r.rigidBodyB); // keep the same order
		}
	};

	struct CollisionInfo
	{
		gm::vec2f collisionNormal;
		float penetration;
	};

private:
	std::map<CollisionPair, CollisionInfo> collisions;
	std::vector<RigidBody*> rigidBodies;

public:
	void IntegrateBodies(float dt);

	bool IsGrounded(RigidBody *rigidBody);
	void CheckCollision();
	void ResolveCollisions();
	void PositionalCorrection(CollisionPair c);
	virtual void OnFixedUpdate() override;


};

}

#endif _MAESTRO_PHYSICS_ENGINE_
