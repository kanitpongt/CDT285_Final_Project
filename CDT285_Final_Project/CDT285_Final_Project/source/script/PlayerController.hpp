#pragma once

#include "EngineCore.hpp"
#include "graphic/camera.h"

class PlayerController : EC::BehaviourScript
{
private:
	
public:
	virtual void OnStart() override;
	virtual void OnUpdate(float dt) override;
};

