#pragma once
#include "Mesh.hpp"

namespace Graphic
{
	class PlaneMesh : public Mesh
	{
	public:
		void Render() override;
		PlaneMesh();
	};
}