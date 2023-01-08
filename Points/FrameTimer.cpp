#include "FrameTimer.h"

namespace Orange {
	

	//Constructor and Destructor
	FrameTimer::FrameTimer() { }

	void FrameTimer::StartFrameTimer() {
		start_time = std::chrono::steady_clock::now();
	}

	bool FrameTimer::UpdateFrameRate() {
		elapsed_time = std::chrono::steady_clock::now() - start_time;

		if (elapsed_time.count() >= time_step) {
			start_time = std::chrono::steady_clock::now();
			current_frame_rate = 1.0 / elapsed_time.count();
			return true;
		} else {
			return false;
		}
	}

	//Getters
	float FrameTimer::GetFrameRate() {
		return 0;
	}

}