#include "TimerManager.h"

namespace Orange {

	std::vector<Timer>TimerManager::timers;

	Timer::Timer(double _duration, void(*_func)()) {
		start_time = std::chrono::steady_clock::now();
		duration = _duration;
		func = _func;
	}

	void TimerManager::UpdateTimers() { 
		for (int i = 0; i < TimerManager::timers.size(); i++) {
			std::chrono::duration<double> elapsed_time = std::chrono::steady_clock::now() - timers[i].start_time;

			if (elapsed_time.count() >= timers[i].duration) {
				if (timers[i].func != nullptr) {
					timers[i].func();
				}

				timers.erase(timers.begin() + i);
			}
		}
	}

	void TimerManager::AddTimer(double duration, void(*func)()) {
		timers.push_back(Timer(duration, func));
	}

}