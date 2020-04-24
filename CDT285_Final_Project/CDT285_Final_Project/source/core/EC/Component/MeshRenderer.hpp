#pragma once
#include <GL/glew.h>
#include "Component.hpp"
#include "graphic/Mesh.hpp"

namespace EC
{
	enum MESH_TYPE { CUBE, PLANE, SPHERE};

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		void Init(MESH_TYPE type);
		void Init(MESH_TYPE type, std::string texturePath);
		Graphic::Mesh* GetMesh();
		GLuint GetTexture();
		bool TextureLoaded();
	protected:
		void CreateMesh(MESH_TYPE type);
		GLuint LoadTexture(std::string path);
	private:
		Graphic::Mesh* m_mesh = nullptr;
		bool m_isTexLoaded = false;
		GLuint m_texture = -1;
	};
}