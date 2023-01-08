#pragma once
#include <chrono>
#include <vector>

namespace Orange {
	struct Timer {
		Timer(double _duration, void(*_func)());
		std::chrono::steady_clock::time_point start_time;
		double duration;
		void (*func)() = nullptr;
	};

	class TimerManager
	{
	private:
		static std::vector<Timer> timers;

	public:
		static void AddTimer(double duration, void(*func)());
		static void UpdateTimers();
		
	};
}

