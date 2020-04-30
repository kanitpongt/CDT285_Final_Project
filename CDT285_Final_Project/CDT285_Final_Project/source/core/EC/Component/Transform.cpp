#include "Transform.hpp"
#include <iostream>
#include <memory>
#include <glm/gtx/quaternion.hpp>
#include <GLM/gtx/euler_angles.hpp>
using namespace glm;

namespace EC
{
	Transform::Transform() {
		//m_position = vec3(0, 0, 0);
		this->SetLocalPosition(glm::vec3(0.0f));
		this->SetLocalScale(glm::vec3(100.0f));
		//this->SetLocalRotation(0, );
		//m_scale = vec3(1, 1, 1);
		/*m_rotation = 0;
		m_localRotation = 0;*/

		//parent is null

		Factory<Transform>::Add(this);
	}

	glm::vec3 Transform::GetPosition() 
	{
		return m_position;
	}

	glm::vec3 Transform::GetLocalPosition() 
	{
		return m_localPosition;
	}

	glm::vec3 Transform::GetScale() 
	{
		return m_scale;
	}

	glm::quat Transform::GetRotation()
	{
		return m_rotation;
	}

	glm::quat Transform::GetLocalRotation() 
	{
		return m_localRotation;
	}

	glm::vec3 Transform::Up() 
	{
		float x = 2 * (m_rotation.x * m_rotation.y - m_rotation.w * m_rotation.z);
		float y = 1 - 2 * (m_rotation.x * m_rotation.x + m_rotation.z * m_rotation.z);
		float z = 2 * (m_rotation.y * m_rotation.z + m_rotation.w * m_rotation.x);
		return glm::vec3(x, y, z);
		//return vec3(cos(radians(m_rotation + 90)), sin(radians(m_rotation + 90)), 0);
	}

	glm::vec3 Transform::Right() 
	{
		float x = 1 - 2 * (m_rotation.y * m_rotation.y + m_rotation.z * m_rotation.z);
		float y = 2 * (m_rotation.x * m_rotation.y + m_rotation.w * m_rotation.z);
		float z = 2 * (m_rotation.x * m_rotation.z - m_rotation.w * m_rotation.y);
		return glm::vec3(x, y, z);
		//m_rotation = glm::quat()
		//return vec3(cos(radians(m_rotation)), sin(radians(m_rotation)), 0);
	}

	glm::mat4 Transform::GetModelMatrix() 
	{
		glm::mat4 rMat = glm::toMat4(m_localRotation);//glm::rotate(glm::mat4(1.0f), radians(m_localRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 sMat = glm::scale(glm::mat4(1.0f), m_localScale);
		glm::mat4 tMat = glm::translate(glm::mat4(1.0f), m_localPosition);
		glm::mat4 transformMat = tMat * rMat * sMat;

		if (parent) 
		{
			transformMat = parent->GetModelMatrix() * transformMat;
		}

		return transformMat;
	}

	void Transform::SetParent(Transform* newParent) 
	{
		parent = newParent;
		parent->children.push_back(this);
		parent->m_childCount++;
	}

	Transform* Transform::GetChild(int index) 
	{
		return (children.at(index));
	}

	unsigned int Transform::GetChildCount()
	{
		return m_childCount;
	}

	/*
	 *update world position according to parent rotation and local position
	 */
	void Transform::UpdateWorldPosition() 
	{
		//update world position
		if (parent) 
		{
			float x = m_localPosition.x;
			float y = m_localPosition.y;
			//float angle = radians(parent->GetRotation());

			glm::vec3 worldPosDirection = parent->GetRotation() * m_localPosition;
			//vec3 worldPosDirection((x * cos(angle)) - (y * sin(angle)), (x * sin(angle)) + (y * cos(angle)), 0);

			m_position = parent->GetPosition() + worldPosDirection;
		}
		else 
		{
			m_position = m_localPosition;
		}

		//update children position
		for (auto child : children) 
		{
			child->UpdateWorldPosition();
		}
	}

	/*
	 *update world scale according to parent, local scale and local rotation
	 */
	void Transform::UpdateScale() 
	{
		//update world scale
		if (parent) 
		{
			m_scale = parent->m_scale * m_localScale;
		}
		else 
		{
			m_scale = m_localScale;
		}

		//update child scale
		for (auto child : children) 
		{
			child->UpdateScale();
		}
	}

	/**
	*update world rotation according to parent and local rotation
	*/
	void Transform::UpdateRotation() 
	{

		if (parent) 
		{
			m_rotation = m_localRotation * parent->GetRotation();
		}
		else 
		{
			m_rotation = m_localRotation;
		}

		//update children rotation and position
		for (auto child : children) {
			child->UpdateRotation();
			child->UpdateWorldPosition();
		}
	}

	void Transform::SetPosition(glm::vec3 position) 
	{
		m_position = position;

		//update local position
		if (parent)
		{
			vec3 relativePosition = m_position - parent->m_position;
			//float revParentRotation = radians(-parent->GetRotation());

			m_localPosition = parent->GetRotation() * relativePosition;
			//m_localPosition = vec3(cos(revParentRotation) * relativePosition.x, sin(revParentRotation) * relativePosition.y, relativePosition.z);
		}
		else 
		{
			m_localPosition = position;
		}

		//update children position
		for (auto child : children) 
		{
			child->UpdateWorldPosition();
		}
	}

	void Transform::SetLocalPosition(glm::vec3 localposition) {
		m_localPosition = localposition;

		//update world position and child position
		UpdateWorldPosition();
	}

	void Transform::Translate(glm::vec3 translation) 
	{
		SetPosition(m_position + translation);
	}

	void Transform::SetScale(glm::vec3 scale) {

		m_scale = scale;

		//update local scale
		if (parent) {
			m_localScale = m_scale / parent->m_scale;
		}
		else {
			m_localScale = scale;
		}

		//update child scale
		for (auto child : children) {
			child->UpdateScale();
		}
	}

	void Transform::SetLocalScale(glm::vec3 localScale) {
		m_localScale = localScale;

		//update world scale and child scale
		UpdateScale();
	}

	void Transform::SetRotation(float angle, glm::vec3 axis)
	{
		
		m_rotation = glm::angleAxis(glm::radians(angle), axis);

		if (parent)
		{
			m_localRotation = m_rotation * glm::inverse(parent->m_rotation);
		}
		else
		{
			m_localRotation = m_rotation;
		}

		//update children roataion and position
		for (auto child : children)
		{
			child->UpdateRotation();
			child->UpdateWorldPosition();
		}
	}
	
	void Transform::SetRotation(glm::quat rot)
	{
		m_rotation = rot;

		if (parent)
		{
			m_localRotation = m_rotation * glm::inverse(parent->m_rotation);
		}
		else
		{
			m_localRotation = m_rotation;
		}

		//update children roataion and position
		for (auto child : children)
		{
			child->UpdateRotation();
			child->UpdateWorldPosition();
		}
	}

	void Transform::SetLocalRotation(float angle, glm::vec3 axis) 
	{

		m_localRotation = glm::angleAxis(glm::radians(angle), axis);

		//update world rotation
		UpdateRotation();
	}

	void Transform::Rotate(float angle, glm::vec3 axis)
	{
		SetRotation(glm::rotate(m_rotation, angle, axis));
	}

	void Transform::Rotate(glm::vec3 angle)
	{
		m_localRotation = m_localRotation * glm::toQuat(glm::eulerAngleYXZ(angle.y, angle.x, angle.z));

		UpdateRotation();
	}

	

	void Transform::RotateAround(float angle, const glm::vec3 axis)
	{
		SetRotation(glm::angleAxis(angle, axis) * m_rotation);
		m_angle = glm::eulerAngles(m_rotation);
	}

	glm::mat4 Transform::CalculateModelMatrix(const glm::vec3& translation
		, const glm::quat& rotation, const glm::vec3& scale)
	{
		const float& qx = rotation.x;
		const float& qy = rotation.y;
		const float& qz = rotation.z;
		const float& qw = rotation.w;
		float qx2 = 2 * qx * qx;
		float qy2 = 2 * qy * qy;
		float qz2 = 2 * qz * qz;
		float qwqz = qw * qz;
		float qxqy = qx * qy;
		float qwqy = qw * qy;
		float qxqz = qx * qz;
		float qwqx = qw * qx;
		float qyqz = qy * qz;

		return glm::mat4(
			-(qy2 + qz2 - 1) * scale.x, 2 * (qwqz + qxqy) * scale.x,
			-2 * (qwqy - qxqz) * scale.x, 0,
			-2 * (qwqz - qxqy) * scale.y, -(qx2 + qz2 - 1) * scale.y,
			2 * (qwqx + qyqz) * scale.y, 0,
			2 * (qwqy + qxqz) * scale.z, -2 * (qwqx - qyqz) * scale.z,
			-(qx2 + qy2 - 1) * scale.z, 0,
			translation.x, translation.y,
			translation.z, 1);
	}
}

