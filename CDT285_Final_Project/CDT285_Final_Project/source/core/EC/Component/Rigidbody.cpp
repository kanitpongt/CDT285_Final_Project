#include "Rigidbody.hpp"
#include "core/EC/GameObject.hpp"
#include "physic/Collider.hpp"
#include "physic/PhysicScene.hpp"


namespace EC
{
	void Rigidbody::UpdateTransform()
	{
		if (!m_kinematic)
			return;

		auto trans = this->GetTransform();

		if (trans)
		{
			Math::Vec3 pos = trans->GetPosition();
			Math::Quat rot = trans->GetRotation();
			btTransform transform;
			m_body->getMotionState()->getWorldTransform(transform);
			transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
			transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
			m_body->getMotionState()->setWorldTransform(transform);
			//m_body->setCenterOfMassTransform(transform);
		}
	}

	void Rigidbody::SetMass(float mass)
	{
		btVector3 inertia(0.0f, 0.0f, 0.0f);
		m_mass = mass;
		if (!m_static)
			m_collider->GetShape()->calculateLocalInertia(m_mass, inertia); //Calculate inertia from shape data
		m_body->setMassProps(m_mass, inertia);
	}

	Rigidbody::Rigidbody()
	{

	}

	void Rigidbody::Init(Physic::PhysicScene& scene, glm::vec3 startPos, Physic::Collider& collider, float mass)
	{
		//Initialize Collider Info
		m_mass = mass;
		m_static = (m_mass == 0.0f);
		btVector3 inertia(0.0f, 0.0f, 0.0f);
		m_collider = &collider; //Save collider to rigidbody
		btCollisionShape* shape = collider.CreateShape(); //Create shape to store it in the scene
		if (!m_static)
			shape->calculateLocalInertia(m_mass, inertia); //Calculate inertia from shape data
		scene.AddShape(shape);

		//Initialize Transform
		btTransform startTrans;
		startTrans.setIdentity();
		startTrans.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));
		m_motionState = new btDefaultMotionState(startTrans);
		
		btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, m_motionState, shape, inertia);
		m_body = new btRigidBody(rbInfo);
		m_body->setUserIndex(m_componentID);

		if (GetGameObject())
			m_body->setUserIndex2(GetGameObject()->GetID());

		scene.AddRigidbody(this);
	}

	void Rigidbody::SetKinematic(bool kinematic)
	{
		m_kinematic = kinematic;
		if (kinematic)
		{
			m_body->setCollisionFlags(m_body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			m_body->setActivationState(DISABLE_DEACTIVATION);
			m_mass = 0.0f;
		}
		else
		{
			m_body->setCollisionFlags(m_body->getCollisionFlags() & ~(btCollisionObject::CF_KINEMATIC_OBJECT));
			m_body->setActivationState(ACTIVE_TAG);
			m_mass = 1.0f;
		}
	}

	Transform* Rigidbody::GetTransform()
	{
		return (this->GetGameObject()) ? this->GetGameObject()->m_transform : nullptr;
	}
}

