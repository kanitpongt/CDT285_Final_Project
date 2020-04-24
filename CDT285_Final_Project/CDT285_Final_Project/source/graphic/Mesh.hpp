#pragma once
#include <GL/glew.h>

namespace Graphic
{
	class Mesh
	{
	public:
		void Bind();
		void UnBind();
		virtual void Render() = 0;
	protected:
		void GenVBO();
		void GenVAO();
		GLuint m_vaoID = -1;
		GLuint m_vboID = -1;
		unsigned int m_vertNum = 0;
		/*struct VBO
		{
			GLuint m_texID = -1;
			GLuint m_posID = -1;
		} m_vbo;*/
	};

	inline void Mesh::Bind()
	{
		if (m_vaoID == -1 || m_vboID == -1)
			return;

		glBindVertexArray(m_vaoID);
	}

	inline void Mesh::UnBind()
	{
		glBindVertexArray(0);
	}

	inline void Mesh::GenVBO()
	{
		glGenBuffers(1, &m_vboID);
	}

	inline void Mesh::GenVAO()
	{
		glGenVertexArrays(1, &m_vaoID);
	}
}