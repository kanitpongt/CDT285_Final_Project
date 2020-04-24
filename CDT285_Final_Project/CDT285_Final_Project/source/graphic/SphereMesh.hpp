#pragma once

#include "Mesh.hpp"

#include <vector>

namespace Graphic
{
	class SphereMesh : public Mesh
	{
	private:
		std::vector<GLushort> indices;
		GLuint ibo;//Index Buffer Object for indices
	public:
		void Render() override;
		SphereMesh();
		~SphereMesh();
	};
}