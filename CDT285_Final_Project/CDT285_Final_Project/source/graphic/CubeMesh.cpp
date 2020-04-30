#include "CubeMesh.hpp"
#include <GL/glew.h>

namespace Graphic
{
	CubeMesh::CubeMesh()
	{
        m_vertNum = 36;
        float cubeVertices[] = {
            // positions          // texture Coords
            -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
             1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
            -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
             
            -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
             1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
            -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
            
            -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
            -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
            -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
            
             1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
             1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
             1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
             1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
             1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
            
            -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
             1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
             1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
             1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
            -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
            -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
            
            -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
             1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
             1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
            -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
            -1.0f,  1.0f, -1.0f,  0.0f, 1.0f
        };

		GenVAO();
		GenVBO();
		glBindVertexArray(m_vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

    void CubeMesh::Render()
    {
        glDrawArrays(GL_TRIANGLES, 0, m_vertNum);
    }
}

