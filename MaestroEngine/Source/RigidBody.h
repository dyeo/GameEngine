#ifndef _MAESTRO_RIGIDBODY_
#define _MAESTRO_RIGIDBODY_


#include <gmtk/gmtk.h>
#include "PhysicsEngine.h"
#include "Transform.h"

namespace mae
{
class RigidBody //: public Component
{
public:
	/**
	 * \Mass of the RigidBody
	 */
	float mass = 1.0f;
	/**
	 * \The bouncieness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy.
	 */
	float bounciness = 1.0f;
	bool UseGravity = true;
	gm::vec2f gravity = gm::vec2f(0.f, -9.8f);
	gm::vec2 currentVelocity;
	gm::vec2 maximumVelocity;
	bool grounded;
	Transform transform;



private:
	gm::vec2 totalForces;

public:
	struct AABB
	{
		gm::vec2f bLeft;
		gm::vec2f tRight;
	};

	AABB aabb;

public:
	void AddForce(gm::vec2f force);
	void Stop();
	bool IsGrounded();
	void SetAABB();
	void Integrate(float dt);

	bool operator!=(const RigidBody rb);

};


}


#endif _MAESTRO_RIGIDBODY_
