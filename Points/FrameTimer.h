#pragma once
#include <chrono>

namespace Orange {
	class FrameTimer
	{
	public:
		FrameTimer();

	private:
		int frame_rate = 20;
		float current_frame_rate;
		double time_step = 1.0 / frame_rate;
		std::chrono::steady_clock::time_point start_time;
		std::chrono::duration<double> elapsed_time;

	public:
		void StartFrameTimer();
		bool UpdateFrameRate();
		float GetFrameRate();
	};
}

