#pragma once
//Engine
#include "core/Math.hpp"
#include "physic/PhysicDebugDrawer.hpp"
//Standard Library
#include <vector>
//Third Party
#include <btBulletCollisionCommon.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

namespace EC { class Rigidbody; }
namespace Physic
{
	class PhysicScene
	{
	public:
		PhysicScene();
		~PhysicScene();
		void SetGravity(Math::Vec3 value);
		void AddRigidbody(EC::Rigidbody* rigid);
		void AddShape(btCollisionShape* shape);
		void Update(float dt);
		PhysicDebugDrawer* m_debugDrawer;
	protected:
		void UpdatePosition();
		void UpdateCollision();
	private:
		
		//Scene Setting
		btDefaultCollisionConfiguration* m_collisionConfiguration;
		btCollisionDispatcher* m_dispatcher;
		btBroadphaseInterface* m_broadphase;
		btSequentialImpulseConstraintSolver* m_solver;
		btDiscreteDynamicsWorld* m_world;
		//Container
		btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

		std::vector<EC::Rigidbody*> m_rigidbodies;
	};
}


