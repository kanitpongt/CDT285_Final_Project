#include "PhysicScene.hpp"
#include <iostream>
#include "core/EC/Component/Rigidbody.hpp"
#include "core/EC/Component/Transform.hpp"

namespace Physic
{

	PhysicScene::PhysicScene()
	{
		m_collisionConfiguration = new btDefaultCollisionConfiguration();
		m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
		m_broadphase = new btDbvtBroadphase();
		m_solver = new btSequentialImpulseConstraintSolver;
		m_debugDrawer = new PhysicDebugDrawer();
		m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
		m_world->setDebugDrawer(m_debugDrawer);
		m_world->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	}

	void PhysicScene::SetGravity(Math::Vec3 value)
	{
		m_world->setGravity(btVector3(value.x, value.y, value.z));
	}

	void PhysicScene::AddRigidbody(EC::Rigidbody* rigid)
	{
		m_world->addRigidBody(rigid->m_body);
		m_rigidbodies.push_back(rigid);
	}

	void PhysicScene::AddShape(btCollisionShape* shape)
	{
		m_collisionShapes.push_back(shape);
	}

	void PhysicScene::Update(float dt)
	{
		for (auto rigid : m_rigidbodies)
		{
			rigid->UpdateTransform();
		}

		m_world->stepSimulation(dt, 10);

		//Update object position
		UpdatePosition();

		//Update Collision Map

		//Debug Draw
		m_world->debugDrawWorld();
	}

	void PhysicScene::UpdatePosition()
	{
		//Update Position
		for (int i = 0; i < m_rigidbodies.size(); i++)
		{
			EC::Rigidbody* rigidbody = m_rigidbodies[i];
			btMotionState* motionState = rigidbody->m_motionState;

			if (!rigidbody->m_static && motionState)
			{
				btTransform trans;
				motionState->getWorldTransform(trans);

				EC::Transform* transform = rigidbody->GetTransform();
				
				if (transform)
				{
					btVector3 pos = trans.getOrigin();
					btQuaternion rot = trans.getRotation();
					transform->SetPosition(Math::Vec3(pos.getX(), pos.getY(), pos.getZ()));
					transform->SetRotation(Math::Quat(rot.getX(), rot.getY(), rot.getZ(), rot.getW()));
				}
				else
				{
					std::cout << "Gameobject is null\n";
				}
			}
		}
	}

	void PhysicScene::UpdateCollision()
	{
		int manifoldSize = m_dispatcher->getNumManifolds();

		for (int i = 0; i < manifoldSize; i++)
		{

		}
	}

	PhysicScene::~PhysicScene(void)
	{
		//Remove all rigidbodies from world
		for (int j = m_world->getNumCollisionObjects() - 1; j > -1; --j)
		{
			btCollisionObject* obj = m_world->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			auto motionState = body->getMotionState();
			if (body != nullptr && motionState != nullptr)
			{
				delete motionState;
			}
			m_world->removeCollisionObject(obj);
			delete obj;
		}

		//Simply Clear RigidBody Pointers
		m_rigidbodies.clear();

		//Delete Collision Shapes
		for (int i = 0; i < m_collisionShapes.size(); ++i)
		{
			btCollisionShape* shape = m_collisionShapes[i];
			m_collisionShapes[i] = nullptr;
			delete shape;
		}

		//Delete Physics Scene
		delete m_debugDrawer;
		delete m_world;
		delete m_solver;
		delete m_broadphase;
		delete m_dispatcher;
		delete m_collisionConfiguration;
	}
}

