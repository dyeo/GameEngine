#include "RigidBody.h"
#include "Engine.h"
#include "Maestro.h"
#include "Sprite.h"

namespace mae
{
	RigidBody::RigidBody(System * const sys, EntityHandle ent)
		: Component(sys, ent)
	{
		SetAABB();			
	}

	void RigidBody::AddForce(gm::vec2f force)
	{
		totalForces += force;
	}

	void RigidBody::Stop()
	{
		currentVelocity = gm::vec2f::zero();
		totalForces = gm::vec2f::zero();
	}

	bool RigidBody::IsGrounded()
	{
		grounded = static_cast<Physics*>(system)->IsGrounded(this); //instance of the physics engine
		return grounded;
	}

	void RigidBody::SetAABB()
	{
		//needs work
		sf::FloatRect bound = sf::FloatRect(0.0f,0.0f,1.0f,1.0f);//Bounds(gm::vec2f(0.f, 0.f), gm::vec2f(1.0f, 1.0f));

		if (entity->GetComponent<Sprite>() != nullptr)
		{
			bound = entity->GetComponent<Sprite>()->getLocalBounds();
		}

		aabb.bLeft =  gm::vec2f(bound.left, bound.top);
		aabb.tRight =  gm::vec2f(bound.width, bound.height);
	}

	void RigidBody::Integrate(float dt)
	{
		if (UseGravity && !IsGrounded())
		{
			AddForce(gravity);
		}
		else
		{
			if (abs(currentVelocity.y) < 0.05f )
			{
				currentVelocity.y = 0.f;
			}
		}

		gm::vec2 acceleration = totalForces / mass;
		if (mass == 0)
		{
			acceleration = gm::vec2f::zero();
		}
		currentVelocity += acceleration * dt;
		gm::vec2f temp = entity->transform->GetLocalPosition().xy;
		temp += currentVelocity * dt;
		entity->transform->SetPosition(gm::vec3f(temp));
		SetAABB();
		totalForces = gm::vec2f::zero();
	}

	bool RigidBody::operator!=(const RigidBody rb)
	{
		return (this->mass != rb.mass || this->bounciness != rb.bounciness || this->UseGravity != rb.UseGravity || this->grounded);
		//couldn't compare gravity, currentVelocity, maxmimumVelocity, transform, or totalForces as there is no overload in the math library
	}
}
