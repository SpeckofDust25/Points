#pragma once
#include <Windows.h>
#include <string>
#include <tchar.h>
#include "Color.h"

namespace Orange {
	struct StateInfo;	//Forward Declaration

	class Window
	{
	public:		//Constructor and Destructor
		Window(std::wstring _title, std::wstring _class_name, HINSTANCE _h_instance, int _n_cmd_show);
		~Window();
		static Window* w_main;

	protected:	//Member Variables
		HMENU w_hmenu_bar;
		bool exit = false;
		bool is_main_window = false;//Main Window? Close this window and it quits the program
		HBRUSH w_background_color;	//Background Color
		int w_cmd_show;				//Startup Info: Command Line Arguments
		HINSTANCE w_h_instance;		//Stored instance handle for use in Win32 API calls such as FindResource
		std::wstring w_class_name;	//Window Class Name
		std::wstring w_title;		//Window Title Bar Name
		HWND w_hwnd;				//Window Handle
		HWND w_parent_hwnd;			//Window Handle of Parent Window
		WNDCLASSEX w_cex;			//Window Data Struct
		StateInfo* w_state = nullptr;//Window State Information
		int w_width, w_height;		//Window width and height

	public:		//Window Creation
		bool CreateMainWindow(int _width, int _height, int start_x, int start_y);
		void CreateChildWindow(HWND hwnd, int _width, int _height, int start_x, int start_y);

	public:		//Individual Window Procedure
		virtual LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	private:	//Window Procedure
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//Window Setup
		void SetupWindowClassEx();
		void RegisterWindow();
		void InstanceWindow(int start_x, int start_y);

	public:
		//Getters
		StateInfo* GetAppState();
		HWND GetHWND();

		//Setters
		void SetTitle(LPCWSTR _title);
		void SetBackgroundColor(Color color);
		bool GetExit();
	};

	struct StateInfo {
		Window* window;
	};
}

