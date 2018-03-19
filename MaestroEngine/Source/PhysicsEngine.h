#ifndef _MAESTRO_PHYSICS_ENGINE_
#define _MAESTRO_PHYSICS_ENGINE_

#include "Engine.h"
#include <gmtk/gmtk.h>
#include "RigidBody.h"
#include <map>
#include <list>

class RigidBody;

namespace mae
{
class PhysicsEngine: public System
{
public:
	PhysicsEngine(Engine *const engine);

	virtual Component *const OnComponentCreate(EntityHandle srcEnt, std::type_index cmpType) override;

	virtual bool OnComponentDestroy(EntityHandle srcEnt, Component * const srcCmp) override;
	
private:
	float groundedTol = 0.1f;

public:

public:
	class CollisionPair
	{
	public:
		RigidBody * rigidBodyA;
		RigidBody *rigidBodyB;
		virtual ~CollisionPair()
		{
			delete rigidBodyA;
			delete rigidBodyB;
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
	void AddRigibodies(RigidBody *rigidBody);
	void IntegrateBodies(float dt);

	bool IsGrounded(RigidBody *rigidBody);
	void CheckCollision();
	void ResolveCollisions();
	void PositionalCorrection(CollisionPair c);
	void UpdatePhysics();
	void OnFixedUpdate() override;


};

//once integrated. The engine will call 'UpdatePhysics' so that the physics engine will work.

}

#endif _MAESTRO_PHYSICS_ENGINE_
