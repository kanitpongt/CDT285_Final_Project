#pragma once
#include "Mesh.hpp"

namespace Graphic
{
	class CubeMesh : public Mesh
	{
	public:
		void Render() override;
		CubeMesh();
	};
}