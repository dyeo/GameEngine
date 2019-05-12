#include "Physics.h"
#include <iostream>
#include "Maestro.h"

namespace mae
{
	Physics::Physics(Engine* const engine) : System(engine)
	{
		engine->SetManagingSystem <mae::RigidBody>(this);
	}

	Component* const Physics::OnComponentCreate(EntityHandle srcEnt, std::type_index cmpType)
	{
		if (cmpType == typeid(RigidBody))
		{
			RigidBody *rb = new RigidBody(this, srcEnt);
			rigidBodies.push_back(rb);
			rb->SetAABB();
			return rigidBodies.back();
		}
		return nullptr;

	}

	bool Physics::OnComponentDestroy(EntityHandle srcEnt, Component* const srcCmp)
	{
		std::type_index cmpType = typeid(*srcCmp);
		if (cmpType == typeid(RigidBody))
		{
			RigidBody *const rb = static_cast<RigidBody*>(srcCmp);
			rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), rb), rigidBodies.end());
			delete rb;
			return true;
		}
		return false;
	}

	void Physics::IntegrateBodies(float dt)
	{
		for (auto rb : rigidBodies)
		{
			rb->Integrate(dt);
		}
	}

	bool Physics::IsGrounded(RigidBody *rigidBody)
	{
		for (auto rb : rigidBodies)
		{
			if (rb != rigidBody)
			{
				if (rigidBody->aabb.bLeft.x < rb->aabb.tRight.x
					&& rigidBody->aabb.tRight.x > rb->aabb.bLeft.x
					&& abs(rigidBody->aabb.bLeft.y - rb->aabb.tRight.y) <= groundedTol)
				{
					if (abs(rigidBody->currentVelocity.y) < groundedTol)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	void Physics::CheckCollision()
	{
		//for (auto bodyA : rigidBodies)
		//{
			for (auto ia = rigidBodies.begin(); ia != rigidBodies.end() - 1; ++ia)
			{
				for (auto ib = ia; ib != rigidBodies.end(); ++ib)
				{
					if (ia != ib)
					{
						CollisionPair pair = { *ia, *ib };
						CollisionInfo colInfo;

						gm::vec2f distance = (*ib)->entity->transform->GetLocalPosition().xy - (*ia)->entity->transform->GetLocalPosition().xy;
						gm::vec2f halfSizeA = ((*ia)->aabb.tRight - (*ia)->aabb.bLeft) / 2;
						gm::vec2f halfSizeB = ((*ib)->aabb.tRight - (*ib)->aabb.bLeft) / 2;
						gm::vec2f gap = gm::vec2f(std::abs(distance.x), std::abs(distance.y)) - (halfSizeA + halfSizeB);

						//separating axis theorem test
						if (gap.x < 0 && gap.y < 0)
						{
							LOG_MESSAGE("Collided!");
							if (collisions.find(pair) != collisions.end())
							{
								collisions.erase(pair);
							}
							if (gap.x > gap.y)
							{
								if (distance.x > 0)
								{
									colInfo.collisionNormal = gm::vec2f(1.0f, 0.f);
								}
								else
								{
									colInfo.collisionNormal = gm::vec2f(-1.0f, 0.f);
								}
								colInfo.penetration = gap.x;
							}
							else
							{
								if (distance.y > 0)
								{
									colInfo.collisionNormal = gm::vec2f(0.f, 1.0f);
								}
								else
								{
									colInfo.collisionNormal = gm::vec2f(0.0f, -1.f);
								}
								colInfo.penetration = gap.y;
							}
							
							collisions.emplace(pair, colInfo);
						}
						else if (collisions.find(pair) != collisions.end())
						{
							LOG_MESSAGE("removed");
							collisions.erase(pair);
						}
					}
				}
			}
		//}
	}

	void Physics::ResolveCollisions()
	{
		for (auto it = collisions.begin(); it != collisions.end(); ++it) // it->first is CollisionPair, it->second is CollisionInfo
		{
			float minBounce = std::min(it->first.rigidBodyA->bounciness, it->first.rigidBodyB->bounciness);
			float velAlongNormal = gm::dot(it->first.rigidBodyB->currentVelocity - it->first.rigidBodyA->currentVelocity, collisions[it->first].collisionNormal);
			if (velAlongNormal > 0)
			{
				continue;
			}
			float j = -(1 + minBounce) * velAlongNormal;
			float invMassA, invMassB;
			if (it->first.rigidBodyA->mass == 0)
			{
				invMassA = 0;
			}
			else
			{
				invMassA = 1 / it->first.rigidBodyA->mass;
			}
			if (it->first.rigidBodyB->mass == 0)
			{
				invMassB = 0;
			}
			else
			{
				invMassB = 1 / it->first.rigidBodyB->mass;
			}

			j /= (invMassA + invMassB);

			auto impulse = collisions[it->first].collisionNormal * j;

			it->first.rigidBodyA->AddForce(-impulse / Maestro::GetEngine()->deltaTime);
			it->first.rigidBodyB->AddForce(impulse / Maestro::GetEngine()->deltaTime);

			if (std::abs(collisions[it->first].penetration) > 0.01f)
			{
				PositionalCorrection(it->first);
			}
		}
	}

	void Physics::PositionalCorrection(CollisionPair c)
	{
		const float percent = 0.2f;
		float invMassA, invMassB;

		if (c.rigidBodyA->mass == 0)
		{
			invMassA = 0;
		}
		else
		{
			invMassA = 1 / c.rigidBodyA->mass;
		}

		if (c.rigidBodyB->mass == 0)
		{
			invMassB = 0;
		}
		else
		{
			invMassB = 1 / c.rigidBodyB->mass;
		}

		gm::vec2f correction = -collisions[c].collisionNormal * ((collisions[c].penetration / (invMassA + invMassB)) * percent);
		gm::vec2f temp = c.rigidBodyA->entity->transform->GetLocalPosition().xy;

		temp -= correction * invMassA;
		c.rigidBodyA->entity->transform->SetPosition(gm::vec3(temp));
		temp += correction * invMassB;
		c.rigidBodyB->entity->transform->SetLocalPosition(gm::vec3(temp));

	}

	void Physics::UpdatePhysics()
	{
		CheckCollision();

		ResolveCollisions();

		IntegrateBodies(static_cast<float>(Maestro::GetEngine()->DELTATIME_FIXED)); //should be fixed deltaTime, but because that is too fast I'm using deltaTime
	}

	void Physics::OnFixedUpdate()
	{
		UpdatePhysics();
	}
}
