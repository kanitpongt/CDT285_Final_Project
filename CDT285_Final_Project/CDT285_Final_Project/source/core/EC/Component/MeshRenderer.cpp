#include <GL/glew.h>
#include <SDL_surface.h>
#include <SDL_image.h>
#include <iostream>

#include "MeshRenderer.hpp"
#include "graphic/CubeMesh.hpp"
#include "graphic/PlaneMesh.hpp"
#include "graphic/SphereMesh.hpp"


namespace EC
{
	MeshRenderer::MeshRenderer() : m_isTexLoaded(false)
	{

	}

	void MeshRenderer::Init(MESH_TYPE type)
	{
		this->CreateMesh(type);
	}

	void MeshRenderer::Init(MESH_TYPE type, std::string texturePath)
	{
		this->CreateMesh(type);
		m_texture = LoadTexture(texturePath);
		if (m_texture != -1)
			m_isTexLoaded = true;
	}

	Graphic::Mesh* MeshRenderer::GetMesh()
	{
		return m_mesh;
	}

	GLuint MeshRenderer::GetTexture()
	{
		return m_texture;
	}

	bool MeshRenderer::TextureLoaded()
	{
		return m_isTexLoaded;
	}

	void MeshRenderer::CreateMesh(MESH_TYPE type)
	{
		switch (type)
		{
		case MESH_TYPE::CUBE :
			m_mesh = new Graphic::CubeMesh();
			break;
		case MESH_TYPE::PLANE :
			m_mesh = new Graphic::PlaneMesh();
			break;
		case MESH_TYPE::SPHERE:
			m_mesh = new Graphic::SphereMesh();
			break;
		default:
			m_mesh = new Graphic::CubeMesh();
			break;
		}
	}
	
	GLuint MeshRenderer::LoadTexture(std::string path)
	{
		glActiveTexture(GL_TEXTURE0);
		SDL_Surface* image = IMG_Load(path.c_str());


		if (image == NULL)
		{
			std::cout << "IMG_Load: " << SDL_GetError() << std::endl;
			return -1;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		int Mode = GL_RGB;
		if (image->format->BytesPerPixel == 4)
		{
			Mode = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode, GL_UNSIGNED_BYTE, image->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		SDL_FreeSurface(image);

		return texture;
	}
}

