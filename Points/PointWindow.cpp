#include "PointWindow.h"

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
        switch (uMsg)
        {

        case WM_CREATE:
            SetupMenu(hwnd);
            if (FAILED(grid.CreateFactory())) {
                return -1;  //Fail CreateWindowEx
            }
            return 0;

        case WM_COMMAND:
        {
            RegisterCommands(wParam);    //Register Button Presses
            return 0;
        }

        case WM_DESTROY:
            grid.DiscardGraphicsResources();
            grid.ReleaseFactory();
            if (is_main_window) {
                PostQuitMessage(0);
            }
            exit = true;
            return 0;

        case WM_SIZE:
            w_width = LOWORD(lParam);
            w_height = HIWORD(lParam);
            grid.Resize(hwnd);
            return 0;

        case WM_PAINT:
        {
            RECT rc;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            TEXTMETRIC text_metric;
            GetTextMetrics(hdc, &text_metric);
            SetRect(&rc, 0, w_height - text_metric.tmHeight, w_width, w_height);
            FillRect(hdc, &ps.rcPaint, w_background_color);
            grid.OnPaint(hwnd);
            DrawText(hdc, L"Mouse Position: ", 16, &rc, DT_LEFT);
            EndPaint(hwnd, &ps);
            return 0;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return TRUE;
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