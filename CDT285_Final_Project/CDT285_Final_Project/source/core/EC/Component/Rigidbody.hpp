#pragma once

#include "core/EC/Component/Component.hpp"
#include "physic/Collider.hpp"

//Third Party
#include <btBulletCollisionCommon.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

//Forward Declaration
namespace Physic { class PhysicScene; }
namespace EC
{
	//Forward Declaration
	class Transform;

	class Rigidbody : public Component
	{
		friend class Physic::PhysicScene;
	protected:
		
	public:
		Rigidbody();
		void Init(Physic::PhysicScene& scene, glm::vec3 initPosition, Physic::Collider& collider, float mass = 0.0f);
		void SetKinematic(bool kinematic);
		void UpdateTransform();
		void SetMass(float mass);
		Transform* GetTransform();
	private:
		btRigidBody* m_body = nullptr;
		btMotionState* m_motionState = nullptr;
		Physic::Collider* m_collider = nullptr;
		btScalar m_mass = 0.0f;
		bool m_static = true;
		bool m_kinematic = false;
	};
}