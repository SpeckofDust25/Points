#include "PointWindow.h"
#include <sstream>

namespace Orange {

    //Constructor and Destructor
    PointWindow::PointWindow(std::wstring _title, std::wstring _class_name, HINSTANCE _h_instance, int _n_cmd_show): Window(_title, _class_name, _h_instance, _n_cmd_show) {

    }

    //Setup Menu
    void PointWindow::SetupMenu(HWND hwnd) {
        w_hmenu_bar = CreateMenu();

        HMENU hFile = CreateMenu();
        HMENU hEdit = CreateMenu();
        HMENU hView = CreateMenu();
        HMENU hHelp = CreateMenu();

        AppendMenu(w_hmenu_bar, MF_POPUP, (UINT_PTR)hFile, L"File");
        AppendMenu(w_hmenu_bar, MF_POPUP, (UINT_PTR)hEdit, L"Edit");
        AppendMenu(w_hmenu_bar, MF_POPUP, (UINT_PTR)hView, L"View");
        AppendMenu(w_hmenu_bar, MF_POPUP, (UINT_PTR)hHelp, L"Help");

        AppendMenu(hFile, MF_STRING, ID_NEW, L"&New \tCtrl+N");
        AppendMenu(hFile, MF_STRING, ID_OPEN, L"&Open \tCtrl+O");
        AppendMenu(hFile, MF_STRING, ID_SAVE, L"&Save \tCtrl+S");
        AppendMenu(hFile, MF_STRING, ID_SAVE_AS, L"&Save As \tCtrl+Shift+S");
        AppendMenu(hFile, MF_STRING, ID_EXIT, L"&Exit \tCtrl+Q");

        AppendMenu(hEdit, MF_STRING, ID_UNDO, L"&Undo \tCtrl+Z");
        AppendMenu(hEdit, MF_STRING, ID_REDO, L"&Redo \tCtrl+Y");
        AppendMenu(hEdit, MF_STRING, ID_CUT, L"&Cut \tCtrl+X");
        AppendMenu(hEdit, MF_STRING, ID_COPY, L"&Copy \tCtrl+C");
        AppendMenu(hEdit, MF_STRING, ID_PASTE, L"&Paste \tCtrl+V");

        AppendMenu(hView, MF_UNCHECKED, ID_SHOW_GRID, L"Show Grid");

        AppendMenu(hHelp, MF_STRING, ID_ABOUT, L"About");
        AppendMenu(hHelp, MF_STRING, ID_HOW_TO, L"How To");
        
        SetMenu(hwnd, w_hmenu_bar);
    }

    //Window Procedure
    LRESULT PointWindow::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

        if (input.UpdateInput(uMsg, lParam)) {  //Update Keyboard and Mouse Input
            return 0;
        }

        switch (uMsg)
        {

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return TRUE;
    }
    
    //Messages
    LRESULT PointWindow::OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        SetupMenu(hwnd);
        if (FAILED(grid.CreateFactory())) {
            return -1;  //Fail CreateWindowEx
        }
        return 0;
    }
    
    LRESULT PointWindow::OnInput(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (input.UpdateInput(uMsg, lParam)) {
            return 0;
        } else {
            return 1;
        }
    }

    LRESULT PointWindow::OnSize(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        grid.UpdateWindowDimensions(w_width, w_height);
        return 0;
    }

    LRESULT PointWindow::OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        RECT mouse_position_rc;
        RECT fps_rc;
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        TEXTMETRIC text_metric;
        GetTextMetrics(hdc, &text_metric);
        FillRect(hdc, &ps.rcPaint, w_background_color);
        grid.OnPaint(hwnd);

        //Mouse Position: Text
        SetRect(&mouse_position_rc, 0, w_height - text_metric.tmHeight, w_width, w_height);
        std::wstringstream stream;
        //stream << "(" << input.GetMousePosition().x << ", " << input.GetMousePosition().y << ")";
        stream << "Paints: " << paint;
        DrawText(hdc, stream.str().c_str(), stream.str().size(), &mouse_position_rc, DT_LEFT);

        //Fps: Text
        /*SetRect(&fps_rc, w_width, 0, w_width, text_metric.tmHeight);
        std::wstringstream fps_stream;
        fps_stream << "Fps: " << "0";
        DrawText(hdc, fps_stream.str().c_str(), fps_stream.str().size(), &fps_rc, DT_RIGHT);
        */

        EndPaint(hwnd, &ps);
        return 0;
    }
    
    LRESULT PointWindow::OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        RegisterCommands(wParam);    //Register Button Presses
        return 0;
    }
    
    LRESULT PointWindow::OnDestory(HWND hwnd, WPARAM wParam, LPARAM lParam) {
        grid.DiscardGraphicsResources();
        grid.ReleaseFactory();
        if (is_main_window) {
            PostQuitMessage(0);
        }
        exit = true;
        return 0;
    }


    //Commands
    void PointWindow::RegisterCommands(WPARAM wParam) {
        switch (LOWORD(wParam)) {
        case ID_NEW:
            break;
        }
        if (LOWORD(wParam) == ID_NEW) {
            NewProject();
        }

        if (LOWORD(wParam) == ID_EXIT) {
            Exit();
        }
    }

    //Called Every Frame
    void PointWindow::Update() {
    
    }

    void PointWindow::Draw() {
        grid.GenerateGrid(w_width, w_height);
        //RedrawWindow(w_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
        InvalidateRect(w_hwnd, NULL, FALSE);

        paint += 1;
    }

    //New, Open, Save and Save As
    void PointWindow::NewProject() {
    
    }

    void PointWindow::OpenFile() {

    }

    void PointWindow::SaveFile() {

    }

    void PointWindow::SaveFileAs() {

    }

    //Undo and Redo
    void PointWindow::Undo() {
    
    }

    void PointWindow::Redo() {
        
    }

    //Cut, Copy, Paste
    void PointWindow::Cut() {
    
    }

    void PointWindow::Copy() {
    
    }

    void PointWindow::Paste() {
    
    }

    //Other
    void PointWindow::Exit() {
        PostQuitMessage(0);
    }
}