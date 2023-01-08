#pragma once
#include <Windows.h>
#include <windowsx.h>

namespace Orange {
	class Input
	{
	private:
		POINT mouse_position;

	public:
		bool UpdateInput(UINT uMsg, LPARAM lParam);

	private:
		bool UpdateMouse(UINT uMsg, LPARAM lParam);
		bool UpdateKeyboard(UINT uMsg, LPARAM lParam);
		void ResetInput();

	public:		//Getters
		POINT GetMousePosition();
	};
}

