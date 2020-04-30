#pragma once

#include <btBulletCollisionCommon.h>
#include "core/Math.hpp"

namespace Physic
{
	class Collider
	{
	public:
		Collider() {}
		btCollisionShape* GetShape();
		virtual btCollisionShape* CreateShape() = 0;
	protected:
		btCollisionShape* m_shape;
	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(Math::Vec3 size);
		virtual btCollisionShape* CreateShape();
	private:
		Math::Vec3 m_size;
	};

	class SphereCollider : public Collider
	{
	public:
		SphereCollider(float radius);
		virtual btCollisionShape* CreateShape();
	private:
		float m_radius;
	};
}