#pragma once
#include <memory>
#include "Core/EC/Component/Component.hpp"


//Forward Declaration
namespace Physic{ struct Collision; }

namespace EC
{
	class BehaviourScript :public Component {
	public:
		BehaviourScript();
		virtual void Init();
		virtual void OnAwake();
		virtual void OnEnable();
		virtual void OnStart();
		virtual void OnUpdate(float dt);
		virtual void OnFixedUpdate(float dt);
		virtual void OnDisable();
		/*virtual void OnTriggerEnter(const Physic::Collision col);
		virtual void OnTriggerStay(const Physic::Collision col);
		virtual void OnTriggerExit(const Physic::Collision col);
		virtual void OnCollisionEnter(const Physic::Collision col);
		virtual void OnCollisionStay(const Physic::Collision col);
		virtual void OnCollisionExit(const Physic::Collision col);*/
		virtual ~BehaviourScript() = 0;

	};

	inline BehaviourScript::BehaviourScript()
	{
		Factory<BehaviourScript>::Add(this);
	}

	inline BehaviourScript::~BehaviourScript() { }

	inline void BehaviourScript::Init() { }

	inline void BehaviourScript::OnAwake() { }
	inline void BehaviourScript::OnEnable() { }
	inline void BehaviourScript::OnDisable() { }

	inline void BehaviourScript::OnStart() { }
	inline void BehaviourScript::OnUpdate(float dt) { }
	inline void BehaviourScript::OnFixedUpdate(float dt) { }

	/*inline void BehaviourScript::OnTriggerEnter(const Physic::Collision col) { }
	inline void BehaviourScript::OnTriggerStay(const Physic::Collision col) { }
	inline void BehaviourScript::OnTriggerExit(const Physic::Collision col) { }

	inline void BehaviourScript::OnCollisionEnter(const Physic::Collision col) { }
	inline void BehaviourScript::OnCollisionStay(const Physic::Collision col) { }
	inline void BehaviourScript::OnCollisionExit(const Physic::Collision col) { }*/
}
