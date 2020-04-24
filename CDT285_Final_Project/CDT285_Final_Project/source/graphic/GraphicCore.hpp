#pragma once
#include <glm/glm.hpp>
#include "graphic/camera.h"

namespace Graphic
{
	void Init();

	void Update(Camera& cam);

	void Terminate();
}