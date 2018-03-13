#include "RigidBody.h"

#include "Maestro.h"

namespace mae
{
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
		grounded = static_cast<PhysicsEngine*>(system)->IsGrounded(this); //instance of the physics engine
		return grounded;
	}

	void RigidBody::SetAABB()
	{
		//needs work
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
		gm::vec2f temp = transform.GetPosition().xy ;
		temp += currentVelocity * dt;
		transform.SetPosition(gm::vec3f(temp));
		SetAABB();
		totalForces = gm::vec2f::zero();
	}

	bool RigidBody::operator!=(const RigidBody rb)
	{
		return (this->mass != rb.mass || this->bounciness != rb.bounciness || this->UseGravity != rb.UseGravity || this->grounded);
		//couldn't compare gravity, currentVelocity, maxmimumVelocity, transform, or totalForces as there is no overload i nthe math library
	}
}
