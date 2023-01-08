#pragma once
#include "Window.h"
#include "Grid.h"
#include "Input.h"

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
		Grid grid;
		Input input;
		int paint = 0;


	public:	//Called Every Frame
		void Update();
		void Draw();

	public:	//Messages
		LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam) override;
		LRESULT OnInput(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		LRESULT OnSize(HWND hwnd, WPARAM wParam, LPARAM lParam) override;
		LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam) override;
		LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam) override;
		LRESULT OnDestory(HWND hwnd, WPARAM wParam, LPARAM lParam) override;

	private:
		void SetupMenu(HWND hwnd);	//Called Before the Window gets created: Needs Window Handle to be passed

		//Registers Commands
		void RegisterCommands(WPARAM wParam);

		//User Commands
		void NewProject();
		void OpenFile();
		void SaveFile();
		void SaveFileAs();
		void Undo();
		void Redo();
		void Cut();
		void Copy();
		void Paste();
		void Exit();
	};
}
