#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Component/Transform.hpp"
#include "Component/BehaviourScript.hpp"
#include "Core/Factory.h"

//Forward Declaration
namespace Physic { struct Collision; }

namespace EC
{
	class GameObject
	{
	protected:
		friend class BehaviourScript;

		std::string m_objectName = "GameObject";
		bool isActive = true;

		static int s_IDCounter;
		int m_objectID;

		std::vector<Component*> m_components;
		std::vector<BehaviourScript*> m_scripts;

		//Collision function
		/*void CollisionEnter(const Physic::Collision);
		void CollisionStay(const Physic::Collision);
		void CollisionExit(const Physic::Collision);
		void TriggerEnter(const Physic::Collision);
		void TriggerStay(const Physic::Collision);
		void TriggerExit(const Physic::Collision);*/
	public:
		GameObject();
		~GameObject() {}

		std::string Layer = "Default";

		std::string Name = "GameObj";
		Transform* m_transform;

		void SetActive(bool activestate);
		bool Active();

		std::string GetName();
		void SetName(std::string);

		int GetID();

		//init all member component
		void InitComponents();

		template <class T>
		T* AddComponent();

		template <class T>
		T* GetComponent();
	};

	template<class T>
	inline T* GameObject::AddComponent() {
		auto component = Factory<T>::Create();

		m_components.push_back(component);
		m_components.back()->SetGameObject(this);
		m_components.back()->Init();

		//if is behaviou script, also assign to script collection
		auto behaviour = dynamic_cast<BehaviourScript*>(component);
		if (behaviour) 
			m_scripts.push_back(behaviour);

		return component;
	}

	template<class T>
	inline T* GameObject::GetComponent() {

		for (auto component : m_components)
		{
			T* comp = dynamic_cast<T*>(component);

			if (comp)
				return comp;
		}

		return nullptr;
	}
}


