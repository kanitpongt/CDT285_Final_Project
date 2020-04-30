#pragma once

#include "EngineCore.hpp"
#include "graphic/camera.h"

class PlayerController : public EC::BehaviourScript
{
public:
	float m_rotSpeed;
	EC::Transform* m_planeToTransform;
	EC::Transform* m_ballTransform;
	EC::Rigidbody* m_ballRigid;
	virtual void OnStart() override;
	virtual void OnFixedUpdate(float dt) override;
	virtual void OnUpdate(float dt) override;
};

