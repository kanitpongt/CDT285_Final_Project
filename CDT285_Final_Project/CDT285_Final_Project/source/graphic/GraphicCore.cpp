#include "GraphicCore.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "core/Factory.h"
#include "core/EC/Component/MeshRenderer.hpp"
#include "core/EC/Component/Skybox.hpp"
#include "core/EC/CoreEC.hpp"
#include "core/EC/GameObject.hpp"
#include "graphic/camera.h"

namespace Graphic
{
	Renderer* g_renderer;

	void Init()
	{
		//Init Window
		Window::Init("Labyrinth", Window::WindowMode::WINDOWED);
		
		//Init Renderer
		g_renderer = new Renderer("source/graphic/Shader/vert.vs", "source/graphic/Shader/frag.fs");
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}

	void Update(Camera& cam)
	{
		if (!Window::ShouldClose())
		{
			// Clear color buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_BLEND);

			//Loop through mesh renderer and render with renderer
			for (auto meshRenderer : Factory<EC::MeshRenderer>::getCollection())
			{
				auto modelMat = meshRenderer->GetGameObject()->m_transform->GetModelMatrix();
				auto globalMat = cam.GetProjectionMatrix() * cam.GetViewMatrix() * modelMat;

				if (meshRenderer->TextureLoaded())
					g_renderer->RenderMesh(meshRenderer->GetMesh(), meshRenderer->GetTexture(), globalMat);
				else
					g_renderer->RenderMesh(meshRenderer->GetMesh(), globalMat);
			}

			for (auto Skybox : Factory<EC::Skybox>::getCollection())
			{
				Skybox->Render(cam);
			}

			Window::SwapBuffer();
			Window::PollEvents();
		}
	}

	void Terminate()
	{
		//Terminate Window
		Window::Terminate();
		//Terminate Renderer

	}
}