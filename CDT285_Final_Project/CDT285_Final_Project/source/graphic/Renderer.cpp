#include "Renderer.hpp"
#include "core/EC/Component/MeshRenderer.hpp"
#include <GL/glew.h>

namespace Graphic
{
	Renderer::Renderer(std::string vertShader, std::string fragShader)
	{
		Init(vertShader, fragShader);
	}

	bool Renderer::Init(std::string vertShader, std::string fragShader)
	{
		m_shader = new Shader(vertShader.c_str(), fragShader.c_str());

		return (m_shader);
	}

	void Renderer::RenderMesh(Mesh* mesh, unsigned int textureID, glm::mat4 mat)
	{
		m_shader->use();

		mesh->Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		m_shader->setBool("renderTexture", true);
		m_shader->setMat4("globalMat", mat);
		mesh->Render();

		m_shader->unUse();
	}

	void Renderer::RenderMesh(Mesh* mesh, glm::mat4 mat)
	{
		m_shader->use();

		//Set Mode to render color
		mesh->Bind();
		m_shader->setBool("renderTexture", false);
		m_shader->setVec3("renderColor", glm::vec3(1.0f, 0.0f, 0.0f));
		m_shader->setMat4("globalMat", mat);
		mesh->Render();

		m_shader->unUse();
	}



}

