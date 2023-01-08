#include "Input.h"

namespace Orange {

	bool Input::UpdateInput(UINT uMsg, LPARAM lParam) {
		bool result = false;
		bool is_mouse = UpdateMouse(uMsg, lParam);
		bool is_keyboard = false;

		if (!is_mouse) {
			is_keyboard = UpdateKeyboard(uMsg, lParam);
		}

		result = (is_mouse || is_keyboard);

		return result;
	}

	bool Input::UpdateMouse(UINT uMsg, LPARAM lParam) {
		switch (uMsg) {
		case WM_MOUSEMOVE:		//Mouse Move
		{
			mouse_position.x = GET_X_LPARAM(lParam);
			mouse_position.y = GET_Y_LPARAM(lParam);
			return true;
		}

		case WM_LBUTTONDOWN:	//Left Mouse Button
			return true;

		case WM_LBUTTONUP:
			return true;

		case WM_MBUTTONDOWN:	//Middle Mouse Button
			return true;

		case WM_MBUTTONUP:
			return true;

		case WM_RBUTTONDOWN:	//Right Mouse Button
			return true;

		case WM_RBUTTONUP:
			return true;
		}

		return false;
	}

	bool Input::UpdateKeyboard(UINT uMsg, LPARAM lParam) {
		return false;
	}


	//Getters
	POINT Input::GetMousePosition() {
		return mouse_position;
	}

}