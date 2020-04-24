#include "World.hpp"
#include "core/EC/CoreEC.hpp"
#include "core/ProgramInfo.h"
#include "core/Factory.h"
#include "core/Input.hpp"
#include "graphic/GraphicCore.hpp"
#include "graphic/camera.h"

#include <iostream>

#define WALL_NUM 10

namespace World
{
	using namespace EC;
	Core::ProgramInfo* g_program;
	Camera g_cam(glm::vec3(-10.0f, 10.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);
	GameObject* plane;
	GameObject* ball;
	GameObject* wall[WALL_NUM];
	GameObject* skybox;

	bool firstMouse = true;
	void processInput(float dt)
	{
		auto window = Graphic::Window::GetWindow();
		
		if (Input::GetKeyDown(Input::KeyCode::KEY_ESCAPE))
			g_program->close();
		
		if (Input::GetKeyHold(Input::KeyCode::KEY_W))
			g_cam.ProcessKeyboard(FORWARD, dt);

		if (Input::GetKeyHold(Input::KeyCode::KEY_S))
			g_cam.ProcessKeyboard(BACKWARD, dt);
		if (Input::GetKeyHold(Input::KeyCode::KEY_A))
			g_cam.ProcessKeyboard(LEFT, dt);
		if (Input::GetKeyHold(Input::KeyCode::KEY_D))
			g_cam.ProcessKeyboard(RIGHT, dt);

		if (Input::GetKeyHold(Input::KeyCode::KEY_LEFT))
			plane->m_transform->Translate(glm::vec3(0.0f, 0.0f, -1.0f * dt));

		g_cam.ProcessMouseMovement(Input::GetMouseOffset().x, -Input::GetMouseOffset().y);

	}

	void Init()
	{
		//Init System
		g_program = &Core::ProgramInfo::GetInstance();
		Graphic::Init();
		Input::Init(false);
		g_cam.MovementSpeed = 10;
		//Init GameObject
		plane = Factory<GameObject>::Create();
		ball = Factory<GameObject>::Create();
		skybox = Factory<GameObject>::Create();
		for (int i = 0; i < WALL_NUM; i++)
		{
			wall[i] = Factory<GameObject>::Create();
			wall[i]->m_transform->SetParent(plane->m_transform);
		}
		
		MeshRenderer* mesh;

		//Outside wall
		plane->m_transform->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
		plane->m_transform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		mesh = plane->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::PLANE, "assets/metal.jpg");

		wall[0]->m_transform->SetScale(glm::vec3(10.0f, 1.0f, 0.5f));
		wall[0]->m_transform->SetPosition(glm::vec3(0.0f, 0.20f, -5.0f));
		mesh = wall[0]->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");

		wall[1]->m_transform->SetScale(glm::vec3(10.0f, 1.0f, 0.5f));
		wall[1]->m_transform->SetPosition(glm::vec3(0.0f, 0.20f, 5.0f));
		mesh = wall[1]->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");

		wall[2]->m_transform->SetScale(glm::vec3(0.5f, 1.0f, 10.0f));
		wall[2]->m_transform->SetPosition(glm::vec3(5.0f, 0.20f, 0.0f));
		mesh = wall[2]->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");

		wall[3]->m_transform->SetScale(glm::vec3(0.5f, 1.0f, 10.0f));
		wall[3]->m_transform->SetPosition(glm::vec3(-5.0f, 0.20f, 0.0f));
		mesh = wall[3]->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");

		//Inside wall
		wall[4]->m_transform->SetScale(glm::vec3(0.3f, 1.0f, 9.0f));
		wall[4]->m_transform->SetPosition(glm::vec3(-3.0f, 0.20f, -0.8f));
		mesh = wall[4]->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");

		wall[5]->m_transform->SetScale(glm::vec3(0.3f, 1.0f, 9.0f));
		wall[5]->m_transform->SetPosition(glm::vec3(-1.0f, 0.20f, 0.8f));
		mesh = wall[5]->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");

		wall[6]->m_transform->SetScale(glm::vec3(0.3f, 1.0f, 9.0f));
		wall[6]->m_transform->SetPosition(glm::vec3(1.0f, 0.20f, -0.8f));
		mesh = wall[6]->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");

		wall[7]->m_transform->SetScale(glm::vec3(0.3f, 1.0f, 9.0f));
		wall[7]->m_transform->SetPosition(glm::vec3(3.0f, 0.20f, 0.8f));
		mesh = wall[7]->AddComponent<EC::MeshRenderer>();
		mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");

		//Ball
		ball->m_transform->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
		mesh = ball->AddComponent<MeshRenderer>();
		mesh->Init(MESH_TYPE::SPHERE);

		//Skybox
		auto sb = skybox->AddComponent<Skybox>();
		std::vector<std::string> skyboxTexture
		{
			"assets/skybox/right.jpg",
			"assets/skybox/left.jpg",
			"assets/skybox/top.jpg",
			"assets/skybox/bottom.jpg",
			"assets/skybox/front.jpg",
			"assets/skybox/back.jpg"
		};
		
		sb->Init("source/graphic/Shader/cubemap_vert.vs", "source/graphic/Shader/cubemap_frag.fs", skyboxTexture);

		//Initialize all script
		ScriptManager::GetInstance().Start();
	}

	void Update(float dt)
	{
		//Update Input
		Input::Update();
		//Update Cam
		processInput(dt);
		//std::cout << "Cam Pos: " << g_cam.Position.x << ", " << g_cam.Position.y << ", " << g_cam.Position.z << std::endl;
		//Update Script
		ScriptManager::GetInstance().Update(dt);
		//Render Graphic
		
		//glm::mat4 projection = glm::perspective(glm::radians(g_cam.Zoom), (float)width / (float)height, 1.0f, 100.0f);
		Graphic::Update(g_cam);
	}

	void FixedUpdate(float dt)
	{
		static float accumulator = 0.0f;
		accumulator += dt;

		while (accumulator >= Core::c_target_dt)
		{
			//Update Components
			ScriptManager::GetInstance().FixedUpdate(dt);
			//Update Physic

			accumulator -= Core::c_target_dt;
		}
	}

	void Loop()
	{
		while (!g_program->shouldClose())
		{
			g_program->StartFrame();
			//Update
			Update(g_program->deltaTime());
			FixedUpdate(g_program->deltaTime());
			g_program->EndFrame();
		}
	}

	void Terminate()
	{
		Graphic::Terminate();
		Input::Terminate();
	}
}
