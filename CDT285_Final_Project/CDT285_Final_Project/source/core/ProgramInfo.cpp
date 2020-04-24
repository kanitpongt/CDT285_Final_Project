#include "core/ProgramInfo.h"
#include "graphic/Window.hpp"

namespace Core
{
	using Clock = std::chrono::high_resolution_clock;

	ProgramInfo& ProgramInfo::GetInstance(void)
	{
		static ProgramInfo info;
		return info;
	}

	void ProgramInfo::StartFrame(void)
	{
		m_frameStartTime = Clock::now();
	}

	void ProgramInfo::EndFrame(void)
	{
		//Check if the time taken in this frame is less that the expected time for each frame. (Time in this context is ms per frame)
		FloatDuration delayTime = m_expectedDeltaTime - (Clock::now() - m_frameStartTime);

		//If the delay time is negative then the frame took longer that it should
		//but if not then we delay until this frame time reach the expected time.
		while (delayTime.count() > 0.0f)
		{
			 delayTime = m_expectedDeltaTime - (Clock::now() - m_frameStartTime);
		}

		//Assign the delta time for this frame
		m_deltaTime = FloatDuration(Clock::now() - m_frameStartTime).count();
		//Set the framerate
		m_frameRate = 1.0f / m_deltaTime;
		
	}

	bool ProgramInfo::shouldClose()
	{
		return m_shouldClose;
	}

	float Core::ProgramInfo::deltaTime()
	{
		return m_deltaTime;
	}

	void ProgramInfo::close()
	{
		m_shouldClose = true;
	}
}