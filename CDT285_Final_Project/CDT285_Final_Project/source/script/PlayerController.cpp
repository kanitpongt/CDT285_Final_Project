#include "PlayerController.hpp"
#include <iostream>


void PlayerController::OnStart()
{
	m_ballRigid->SetKinematic(true);
}

void PlayerController::OnFixedUpdate(float dt)
{
	if (Input::GetMouseHold(Input::MouseKeyCode::MOUSE_LEFT) && m_planeToTransform)
	{
		//std::cout << "Rotate\n";
		auto mousePos = Input::GetMouseOffset();
		float rDT = dt * m_rotSpeed;
		Math::Vec3 rot;
		rot.x = 1 / mousePos.x;
		rot.z = 1 / mousePos.y;
		//std::cout << "Mouse dt: " << mousePos.x << ", " << mousePos.y << std::endl;
		//std::cout << "rDT: " << rDT << std::endl;
		//m_planeToTransform->Rotate(dt * m_rotSpeed, Math::Vec3(1.0f, 0.0f, 0.0f));
		m_planeToTransform->Rotate(Math::Vec3(rDT * mousePos.x, 0.0f, rDT * mousePos.y));
	}

	
}

void PlayerController::OnUpdate(float dt)
{
	if (!m_ballRigid || !m_ballTransform)
		return;

	if (Input::GetKeyDown(Input::KeyCode::KEY_R))
	{
		m_ballRigid->SetKinematic(true);
		m_ballTransform->SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));
	}

	if (Input::GetKeyDown(Input::KeyCode::KEY_SPACE))
	{
		m_ballRigid->SetKinematic(false);
		m_ballRigid->SetMass(30.0f);
	}
}

