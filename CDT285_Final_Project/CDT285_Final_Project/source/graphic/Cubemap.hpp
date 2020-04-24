#pragma once
#include "graphic/Mesh.hpp"
#include "graphic/Shader.hpp"
#include <vector>
#include <string>

namespace Graphic
{
	class Cubemap : Mesh
	{
	public:
		Cubemap();
		bool LoadTexture(std::vector<std::string> cubeFaces);
		void Render() override;
	private:
		GLuint m_texture = -1;
		Shader* m_shader;
	};
}