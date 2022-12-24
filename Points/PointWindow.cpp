#include "PointWindow.h"

namespace Orange {

    //Constructor and Destructor
    PointWindow::PointWindow(std::wstring _title, std::wstring _class_name, HINSTANCE _h_instance, int _n_cmd_show): Window(_title, _class_name, _h_instance, _n_cmd_show) {
        SetupMenu();
    }

    //Setup Menu
    void PointWindow::SetupMenu() {
        w_hmenu_bar = CreateMenu();
        HMENU hFile = CreateMenu();
        HMENU hEdit = CreateMenu();
        HMENU hView = CreateMenu();
        HMENU hHelp = CreateMenu();

        AppendMenu(w_hmenu_bar, MF_POPUP, (UINT_PTR)hFile, L"File");
        AppendMenu(w_hmenu_bar, MF_POPUP, (UINT_PTR)hEdit, L"Edit");
        AppendMenu(w_hmenu_bar, MF_POPUP, (UINT_PTR)hView, L"View");
        AppendMenu(w_hmenu_bar, MF_POPUP, (UINT_PTR)hHelp, L"Help");

        AppendMenu(hFile, MF_STRING, ID_NEW, L"New");
        AppendMenu(hFile, MF_STRING, ID_OPEN, L"Open");
        AppendMenu(hFile, MF_STRING, ID_SAVE, L"Save");
        AppendMenu(hFile, MF_STRING, ID_SAVE_AS, L"Save As");
        AppendMenu(hFile, MF_STRING, ID_EXIT, L"Exit");

        AppendMenu(hEdit, MF_STRING, ID_UNDO, L"Undo");
        AppendMenu(hEdit, MF_STRING, ID_REDO, L"Redo");
        AppendMenu(hEdit, MF_STRING, ID_CUT, L"Cut");
        AppendMenu(hEdit, MF_STRING, ID_COPY, L"Copy");
        AppendMenu(hEdit, MF_STRING, ID_PASTE, L"Paste");

        AppendMenu(hView, MF_UNCHECKED, ID_SHOW_GRID, L"Show Grid");

        AppendMenu(hHelp, MF_STRING, ID_ABOUT, L"About");
        AppendMenu(hHelp, MF_STRING, ID_HOW_TO, L"How To");

        SetMenu(w_hwnd, w_hmenu_bar);
    }

    //Window Procedure
    LRESULT PointWindow::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg)
        {
        case WM_COMMAND:
        {
            if (LOWORD(wParam) == ID_NEW) {

            }

            if (LOWORD(wParam) == ID_EXIT) {
                PostQuitMessage(0);
            }

            return 0;
        }

        case WM_DESTROY:
            if (is_main_window) {
                PostQuitMessage(0);
            }
            exit = true;
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, w_background_color);
            EndPaint(hwnd, &ps);
            return 0;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return TRUE;
    }




}