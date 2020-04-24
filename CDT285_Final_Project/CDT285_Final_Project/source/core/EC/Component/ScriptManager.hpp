#pragma once
#include "BehaviourScript.hpp"
#include "core/Factory.h"

namespace EC
{
	class ScriptManager
	{
	public:
		static ScriptManager& GetInstance();

		void Start();

		void Update(float dt);

		void FixedUpdate(float dt);

	};

	inline ScriptManager& ScriptManager::GetInstance()
	{
		static ScriptManager inst;
		return inst;
	}

	inline void ScriptManager::Start()
	{
		for (auto behaviour : Factory<BehaviourScript>::getCollection())
		{
			behaviour->OnStart();
		}
	}

	inline void ScriptManager::Update(float dt)
	{
		for (auto behaviour : Factory<BehaviourScript>::getCollection())
		{
			behaviour->OnUpdate(dt);
		}
	}

	inline void ScriptManager::FixedUpdate(float dt)
	{
		for (auto behaviour : Factory<BehaviourScript>::getCollection())
		{
			behaviour->OnFixedUpdate(dt);
		}
	}
}
