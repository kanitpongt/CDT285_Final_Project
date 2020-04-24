#pragma once

#include <chrono>

namespace Core
{
	//Max framerate
	constexpr float c_MAX_FRAMERATE = 60.0f;
	constexpr float c_target_dt = 1.0f / c_MAX_FRAMERATE;

	using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
	using FloatDuration = std::chrono::duration<float>;

	struct ProgramInfo
	{
	public:
		//Methods
		static ProgramInfo& GetInstance(void);
		void StartFrame(void);
		void EndFrame(void);
		void close(void);
		bool shouldClose(void);
		float deltaTime();

		//Members
		float m_deltaTime = 1 / c_MAX_FRAMERATE;
		float m_frameRate = 1.0f / m_deltaTime;
		float m_maxFramerate = c_MAX_FRAMERATE;
		Time m_frameStartTime;
		FloatDuration m_expectedDeltaTime = FloatDuration(1.0f / m_maxFramerate);
		bool m_shouldClose = false;
	};

	
}
