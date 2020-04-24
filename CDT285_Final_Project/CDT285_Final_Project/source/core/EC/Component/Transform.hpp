#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>

#include "Component.hpp"

using namespace std;

namespace EC
{
	class Transform : public Component
	{
	private:
		Transform* parent;
		std::vector<Transform*> children;
		unsigned int m_childCount = 0;

		glm::vec3 m_position;
		glm::vec3 m_scale;
		//rotation in degree
		glm::quat m_quatRotation;
		glm::quat m_quatLocalRotation;
		float m_rotation = 0.0f;

		glm::vec3 m_localPosition;
		glm::vec3 m_localScale;
		float m_localRotation = 0.0f;

		//runtime rendering matrix
		glm::mat4 m_modelMatrix;

		void UpdateWorldPosition();
		void UpdateScale();
		void UpdateRotation();
	public:
		Transform();

		glm::vec3 GetPosition();
		glm::vec3 GetLocalPosition();
		glm::vec3 GetScale();
		float GetRotation();
		float GetLocalRotation();
		glm::vec3 Up();
		glm::vec3 Right();

		glm::mat4 GetModelMatrix();

		void SetParent(Transform* newParent);

		Transform* GetChild(int index);
		unsigned int GetChildCount();

		void SetPosition(glm::vec3 position);
		void SetLocalPosition(glm::vec3 localposition);
		void Translate(glm::vec3 translation);
		void SetScale(glm::vec3 scale);
		void SetLocalScale(glm::vec3 localscale);

		void SetRotation(float angle, glm::vec3& axis);

		void SetRotation(float rotation);
		void SetLocalRotation(float localrotation);
		void Rotate(float rotation);
	};
}
