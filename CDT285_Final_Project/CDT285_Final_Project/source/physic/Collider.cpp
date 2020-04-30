#include "Collider.hpp"



namespace Physic
{
	BoxCollider::BoxCollider(Math::Vec3 size) : m_size(size)
	{
	}

	btCollisionShape* BoxCollider::CreateShape()
	{
		m_shape = new btBoxShape(btVector3(m_size.x, m_size.y, m_size.z));
		return m_shape;
	}

	SphereCollider::SphereCollider(float radius)
	{
		m_radius = radius;
	}

	btCollisionShape* SphereCollider::CreateShape()
	{
		m_shape = new btSphereShape(m_radius);
		return m_shape;
	}
	btCollisionShape* Collider::GetShape()
	{
		return m_shape;
	}
}
