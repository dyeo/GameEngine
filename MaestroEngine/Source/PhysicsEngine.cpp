#include "PhysicsEngine.h"

#include "Maestro.h"

namespace mae
{
	

	void PhysicsEngine::AddRigibodies(RigidBody rigidBody)
	{
		rigidBodies.push_back(rigidBody);
	}

	void PhysicsEngine::IntegrateBodies(float dt)
	{
		for (RigidBody rb : rigidBodies)
		{
			rb.Integrate(dt);
		}
	}

	bool PhysicsEngine::IsGrounded(RigidBody rigidBody)
	{
		for (RigidBody rb : rigidBodies)
		{
			if (rb != rigidBody) 
			{
				if (rigidBody.aabb.bLeft.x < rb.aabb.tRight.x
					&& rigidBody.aabb.tRight.x > rb.aabb.bLeft.x
					&& abs(rigidBody.aabb.bLeft.y - rb.aabb.tRight.y) <= groundedTol)
				{
					if (abs(rigidBody.currentVelocity.y) < groundedTol)
					{
						return true;
					}
				}
			}
			return false;
		}
	}

	void PhysicsEngine::CheckCollision()
	{
	}

	void PhysicsEngine::ResolveCollisions()
	{
		//would we use a lambda to iterate through all keys?
		for (auto it = collisions.begin(); it != collisions.end(); ++it) // it->first is CollisionPair, it->second is CollisionInfo
		{

		}
	}

	void PhysicsEngine::PositionalCorrection(CollisionPair c)
	{
		const float percent = 0.2f;
		float invMassA, invMassB;

		if (c.rigidBodyA.mass == 0)
		{
			invMassA = 0;
		}
		else
		{
			invMassA = 1 / c.rigidBodyA.mass;
		}

		if (c.rigidBodyB.mass == 0)
		{
			invMassB = 0;
		}
		else
		{
			invMassB = 1 / c.rigidBodyB.mass;
		}
	}

	void PhysicsEngine::UpdatePhysics()
	{
		CheckCollision();

		ResolveCollisions();

		IntegrateBodies(Maestro::GetEngine()->DELTATIME_FIXED); //needs deltaTime from engine
	}

	void PhysicsEngine::OnFixedUpdate() //hopefully this is integrated in with the engine by doing this
	{
		UpdatePhysics();
	}
}
