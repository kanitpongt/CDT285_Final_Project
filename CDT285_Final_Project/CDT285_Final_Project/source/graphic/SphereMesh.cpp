#include "SphereMesh.hpp"
#include <vector>
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace Graphic
{
	struct VertexFormat
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texture;

		VertexFormat(const glm::vec3& iPos, const glm::vec4& iColor, const glm::vec2& iTex)
		{
			position = iPos;
			color = iColor;
			texture = iTex;
		}
	};

	SphereMesh::SphereMesh()
	{

		GLuint vao;
		GLuint vbo;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		std::vector<VertexFormat> vertices;

		glm::vec4 blue = glm::vec4(0, 0, 1, 1);

		int n = 1;
		unsigned int rings = 24 * n;
		unsigned int sectors = 48 * n;

		float const R = 1.0f / (float)(rings - 1);
		float const S = 1.0f / (float)(sectors - 1);

		float pi = 3.14159265358979323846f;

		for (unsigned int r = 0; r < rings; r++) {
			for (unsigned int s = 0; s < sectors; s++) {

				float const y = sin(-pi / 2.0f + pi * r * R);
				float const x = cos(2 * pi * s * S) * sin(pi * r * R);
				float const z = sin(2 * pi * s * S) * sin(pi * r * R);

				glm::vec2 texCoord = glm::vec2(s * S, r * R);
				glm::vec3 vxs = glm::vec3(x, y, z);

				vertices.push_back(VertexFormat(vxs, blue, texCoord));
			}
		}

		indices.resize(rings * sectors * 6);
		std::vector<GLushort>::iterator i = indices.begin();
		for (unsigned int r = 0; r < rings - 1; r++) {
			for (unsigned int s = 0; s < sectors - 1; s++) {
				*i++ = r * sectors + s;
				*i++ = r * sectors + (s + 1);
				*i++ = (r + 1) * sectors + (s + 1);

				*i++ = (r + 1) * sectors + (s + 1);
				*i++ = (r + 1) * sectors + s;
				*i++ = r * sectors + s;
			}
		}

		m_vertNum = vertices.size();

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_vertNum, &vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));

		glBindVertexArray(0);

		m_vaoID = vao;
		m_vboID = vbo;

	}

	SphereMesh::~SphereMesh()
	{
        if (m_vboID) 
        {
            glDeleteBuffers(1, &m_vboID);
        }
        if (m_vaoID) 
        {
            glDeleteVertexArrays(1, &m_vaoID);
        }

        m_vaoID = 0;
        m_vboID = 0;
	}

	void SphereMesh::Render()
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
	}

}

