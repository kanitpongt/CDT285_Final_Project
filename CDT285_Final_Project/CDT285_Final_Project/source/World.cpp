#include "World.hpp"
#include "core/EC/CoreEC.hpp"
#include "core/ProgramInfo.h"
#include "core/Factory.h"
#include "core/Input.hpp"
#include "graphic/GraphicCore.hpp"
#include "graphic/camera.h"
#include "physic/PhysicScene.hpp"
#include "physic/Collider.hpp"

//Script
#include "script/PlayerController.hpp"
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
	GameObject* player;
	Physic::PhysicScene* g_physicScene;

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

		if (Input::GetMouseHold(Input::MouseKeyCode::MOUSE_RIGHT))
			g_cam.ProcessMouseMovement(Input::GetMouseOffset().x, -Input::GetMouseOffset().y);

	}

	void Init()
	{
		//Init System
		g_program = &Core::ProgramInfo::GetInstance();
		Graphic::Init();
		Input::Init(false);
		g_cam.MovementSpeed = 10;
		//Init Physic Scene
		g_physicScene = new Physic::PhysicScene();
		//Init GameObject
		plane = Factory<GameObject>::Create();
		ball = Factory<GameObject>::Create();
		skybox = Factory<GameObject>::Create();
		player = Factory<GameObject>::Create();
		for (int i = 0; i < WALL_NUM; i++)
		{
			wall[i] = Factory<GameObject>::Create();
			wall[i]->m_transform->SetParent(plane->m_transform);
		}
		
		MeshRenderer* mesh;
		Rigidbody* rigid;
		Physic::BoxCollider* boxCollider;

		{
			//Plane
			plane->m_transform->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
			plane->m_transform->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
			mesh = plane->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::PLANE, "assets/metal.jpg");
			rigid = plane->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(glm::vec3(5.0f, 0.1f, 5.0f));
			rigid->Init(*g_physicScene, plane->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			//Outside wall
			wall[0]->m_transform->SetScale(glm::vec3(5.0f, 1.0f, 0.5f));
			wall[0]->m_transform->SetPosition(glm::vec3(0.0f, 0.20f, -5.0f));
			mesh = wall[0]->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");
			rigid = wall[0]->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(wall[0]->m_transform->GetScale());
			rigid->Init(*g_physicScene, wall[0]->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			wall[1]->m_transform->SetScale(glm::vec3(5.0f, 1.0f, 0.5f));
			wall[1]->m_transform->SetPosition(glm::vec3(0.0f, 0.20f, 5.0f));
			mesh = wall[1]->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");
			rigid = wall[1]->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(wall[1]->m_transform->GetScale());
			rigid->Init(*g_physicScene, wall[1]->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			wall[2]->m_transform->SetScale(glm::vec3(0.5f, 1.0f, 5.0f));
			wall[2]->m_transform->SetPosition(glm::vec3(5.0f, 0.20f, 0.0f));
			mesh = wall[2]->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");
			rigid = wall[2]->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(wall[2]->m_transform->GetScale());
			rigid->Init(*g_physicScene, wall[2]->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			wall[3]->m_transform->SetScale(glm::vec3(0.5f, 1.0f, 5.0f));
			wall[3]->m_transform->SetPosition(glm::vec3(-5.0f, 0.20f, 0.0f));
			mesh = wall[3]->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");
			rigid = wall[3]->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(wall[3]->m_transform->GetScale());
			rigid->Init(*g_physicScene, wall[3]->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			//Inside wall
			wall[4]->m_transform->SetScale(glm::vec3(0.3f, 1.0f, 4.5f));
			wall[4]->m_transform->SetPosition(glm::vec3(-3.0f, 0.20f, -0.8f));
			mesh = wall[4]->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");
			rigid = wall[4]->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(wall[4]->m_transform->GetScale());
			rigid->Init(*g_physicScene, wall[4]->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			wall[5]->m_transform->SetScale(glm::vec3(0.3f, 1.0f, 4.5f));
			wall[5]->m_transform->SetPosition(glm::vec3(-1.0f, 0.20f, 0.8f));
			mesh = wall[5]->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");
			rigid = wall[5]->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(wall[5]->m_transform->GetScale());
			rigid->Init(*g_physicScene, wall[5]->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			wall[6]->m_transform->SetScale(glm::vec3(0.3f, 1.0f, 4.5f));
			wall[6]->m_transform->SetPosition(glm::vec3(1.0f, 0.20f, -0.8f));
			mesh = wall[6]->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");
			rigid = wall[6]->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(wall[6]->m_transform->GetScale());
			rigid->Init(*g_physicScene, wall[6]->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			wall[7]->m_transform->SetScale(glm::vec3(0.3f, 1.0f, 4.5f));
			wall[7]->m_transform->SetPosition(glm::vec3(3.0f, 0.20f, 0.8f));
			mesh = wall[7]->AddComponent<EC::MeshRenderer>();
			mesh->Init(MESH_TYPE::CUBE, "assets/metal.png");
			rigid = wall[7]->AddComponent<EC::Rigidbody>();
			boxCollider = new Physic::BoxCollider(wall[7]->m_transform->GetScale());
			rigid->Init(*g_physicScene, wall[7]->m_transform->GetPosition(), *boxCollider);
			rigid->SetKinematic(true);

			//Ball

			ball->m_transform->SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));
			ball->m_transform->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
			mesh = ball->AddComponent<MeshRenderer>();
			mesh->Init(MESH_TYPE::SPHERE);
			rigid = ball->AddComponent<EC::Rigidbody>();
			auto sphereCollider = new Physic::SphereCollider(0.4f);
			rigid->Init(*g_physicScene, ball->m_transform->GetPosition(), *sphereCollider, 40.0f);

			PlayerController* controller = player->AddComponent<PlayerController>();
			controller->m_planeToTransform = plane->m_transform;
			controller->m_ballTransform = ball->m_transform;
			controller->m_ballRigid = rigid;
			controller->m_rotSpeed = 0.1f;
		}

		//Skybox
		auto sb = skybox->AddComponent<Skybox>();
		std::vector<std::string> skyboxTexture
		{
			"assets/skybox/hot_rt.png",
			"assets/skybox/hot_lf.png",
			"assets/skybox/hot_up.png",
			"assets/skybox/hot_dn.png",
			"assets/skybox/hot_ft.png",
			"assets/skybox/hot_bk.png"
		};
		
		sb->Init("source/graphic/Shader/cubemap_vert.vs", "source/graphic/Shader/cubemap_frag.fs", skyboxTexture);

		//Initialize all script
		ScriptManager::GetInstance().Start();
		std::cout << "Initialized All System\n";
	}

	void Update(float dt)
	{
		//Update Input
		Input::Update();
		//Update Cam
		processInput(dt);
		//Update Script
		ScriptManager::GetInstance().Update(dt);
		//Render Graphic
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
			g_physicScene->m_debugDrawer->SetMatrices(g_cam.GetViewMatrix(), g_cam.GetProjectionMatrix());
			g_physicScene->Update(dt);
			
			accumulator -= Core::c_target_dt;
		}
	}

	void Loop()
	{
		while (!g_program->shouldClose())
		{
			g_program->StartFrame();

			FixedUpdate(g_program->deltaTime());
			Update(g_program->deltaTime());
			
			g_program->EndFrame();
		}
	}

	void Terminate()
	{
		Graphic::Terminate();
		Input::Terminate();
	}
}
