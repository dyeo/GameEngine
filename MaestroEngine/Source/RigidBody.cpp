#include "RigidBody.h"

#include "Maestro.h"

namespace mae
{
	RigidBody::RigidBody(System * const sys, EntityHandle ent)
		: Component(sys, ent)
		, parent(nullptr)
	{
		
	}

	RigidBody::~RigidBody()
	{
		//not sure what to do in destructor
	}

	void RigidBody::OnStart()
	{
		SetAABB();

		//get reference to physics engine
		//add rigidbody to physics engine
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
		grounded = static_cast<PhysicsEngine*>(system)->IsGrounded(this); //instance of the physics engine
		return grounded;
	}

	void RigidBody::SetAABB()
	{
		//needs work
		Bounds bound = Bounds(gm::vec2f(0.f, 0.f), gm::vec2f(1.0f, 1.0f));

		//part where you need to get the renderer component and check to see if it's valid
		//if it is, assign bound to be equal to that, otherwise use default values

		aabb.bLeft =  gm::vec2f(bound.m_center.x - bound.m_Extents.x, bound.m_center.y - bound.m_Extents.y);
		aabb.tRight =  gm::vec2f(bound.m_center.x + bound.m_Extents.x, bound.m_center.y + bound.m_Extents.y);
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
		gm::vec2f temp = transform->GetPosition().xy ; //probably wrong. Would need to get the actual transform
		temp += currentVelocity * dt;
		transform->SetPosition(gm::vec3f(temp));
		SetAABB();
		totalForces = gm::vec2f::zero();
	}

	bool RigidBody::operator!=(const RigidBody rb) const
	{
		return (this->mass != rb.mass || this->bounciness != rb.bounciness || this->UseGravity != rb.UseGravity || this->grounded);
		//couldn't compare gravity, currentVelocity, maxmimumVelocity, transform, or totalForces as there is no overload in the math library
	}
}
