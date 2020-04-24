#pragma once
#include <string>
#include "Shader.hpp"
#include "Mesh.hpp"

//Forward Declaration

namespace Graphic
{
	class Renderer
	{
	public:
		Renderer(std::string vertShader, std::string fragShader);
		bool Init(std::string vertShader, std::string fragShader);
		void RenderMesh(Mesh* mesh, glm::mat4 mat);
		void RenderMesh(Mesh* mesh, unsigned int textureID, glm::mat4 mat);
	private:
		Shader* m_shader;
	};
}


