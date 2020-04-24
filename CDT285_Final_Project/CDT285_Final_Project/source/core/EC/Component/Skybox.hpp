#pragma once
#include "graphic/Cubemap.hpp"
#include "graphic/Shader.hpp"
#include "graphic/camera.h"
#include "Component.hpp"

namespace EC
{
	class Skybox : public Component
	{
	public:
		void Init(std::string vert, std::string frag, std::vector<std::string>& cubemapTexture);
		void Render(Camera& cam);
	private:
		Graphic::Cubemap m_cubemap;
		Graphic::Shader* m_shader;
	};
}