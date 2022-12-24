#pragma once
#include "Window.h"

//File
#define ID_NEW 1
#define ID_OPEN 2
#define ID_SAVE 3
#define ID_SAVE_AS 4
#define ID_EXIT 5

//Edit
#define ID_UNDO 6
#define ID_REDO 7
#define ID_CUT 8
#define ID_COPY 9
#define ID_PASTE 10

//View
#define ID_SHOW_GRID 11

//Help
#define ID_ABOUT 12
#define ID_HOW_TO 13

namespace Orange {
	class PointWindow : public Window
	{
	public: 
		PointWindow(std::wstring _title, std::wstring _class_name, HINSTANCE _h_instance, int _n_cmd_show);
		//~PointWindow();
		LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	private:
		void SetupMenu();
	};
}
