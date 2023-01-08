#include "Window.h"
#include <functional>

namespace Orange {

    //Static Window
    Window* Window::w_main = nullptr;

    //Constructor and Destructor
    Window::Window(std::wstring _title, std::wstring _class_name, HINSTANCE _h_instance, int _n_cmd_show) {
        w_state = new StateInfo;
        w_state->window = this;
        w_title = _title;
        w_class_name = _class_name;
        w_h_instance = _h_instance;
        w_cmd_show = _n_cmd_show;
    }

    Window::~Window() {
        delete w_state;
    }

    //Window Types

    //True: Success, False: Failed
    bool Window::CreateMainWindow(int _width, int _height, int start_x, int start_y) {
        w_width = _width;
        w_height = _height;
        is_main_window = true;

        if (w_main == nullptr) {
            Orange::Window::w_main = this;
        }
        else {
            return false;
        }

        SetupWindowClassEx();
        RegisterWindow();
        InstanceWindow(start_x, start_y);

        return true;
    }

    void Window::CreateChildWindow(HWND hwnd, int _width, int _height, int _start_x, int _start_y) {
        w_width = _width;
        w_height = _height;
        w_parent_hwnd = hwnd;

        SetupWindowClassEx();
        RegisterWindow();
        InstanceWindow(_start_x, _start_y);
    }

    //TODO: GET THE WINDOW WIDTH AND HEIGHT VALUES
    //TODO: HOOK UP GRID TO THE WIDTH AND HEIGHT VALUES 

    //Window Procedure
    LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        StateInfo* pThis = NULL;
        LRESULT result = 1;

        if (uMsg != WM_CREATE) {    //Gives us Access to the current window
            pThis = reinterpret_cast<StateInfo*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        //Handle Window Messages
        switch (uMsg) {
            case WM_CREATE:
            {
                UpdateWindow(hwnd);
                CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;                  //Contains info about the creation of the window
                pThis = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);  //Casting lpCreateParams to type StateInfo: The struct we passed to the window when we called CreateWindowEx
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);     //Setting a Pointer to our StateInfo struct
                pThis->window->WindowMessage(hwnd, uMsg, wParam, lParam);   //Window Backend Message Handling
                result = pThis->window->OnCreate(hwnd, wParam, lParam);     //PointWindow Message Handling
                break;
            }
            
            
            case WM_INPUT:
            {
                result = pThis->window->OnInput(hwnd, uMsg, wParam, lParam);
                break;
            }

            case WM_COMMAND:
            {
                result = pThis->window->OnCommand(hwnd, wParam, lParam);
                break;
            }

            case WM_PAINT:
            {
                result = pThis->window->OnPaint(hwnd, wParam, lParam);
                break;
            }

            case WM_SIZE:
            {
                pThis->window->w_width = LOWORD(lParam);
                pThis->window->w_height = HIWORD(lParam);
                pThis->window->OnSize(hwnd, wParam, lParam);
                break;
            }

            case WM_DESTROY:
            {
                result = pThis->window->OnDestory(hwnd, wParam, lParam);
                break;
            }
        }

        if (result) {   //Didn't Handle the Message
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    //Current Window Procedure
    void Window::WindowMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (uMsg == WM_CREATE) {
            //Screen Width and Height
            int screen_width = GetSystemMetrics(SM_CXSCREEN);
            int screen_height = GetSystemMetrics(SM_CYSCREEN);

            // Create the double buffer when the window is created
            w_hdc_1 = CreateCompatibleDC(NULL);
            w_hdc_2 = CreateCompatibleDC(NULL);
            w_hbm_1 = CreateCompatibleBitmap(w_hdc_1, screen_width, screen_height);
            w_hbm_2 = CreateCompatibleBitmap(w_hdc_2, screen_width, screen_height);
        }
    }

    //Window Setup
    void Window::SetupWindowClassEx() {
        w_cex.cbSize = sizeof(WNDCLASSEX);
        w_cex.style = CS_HREDRAW | CS_VREDRAW;
        w_cex.lpfnWndProc = WndProc;
        w_cex.cbClsExtra = 0;
        w_cex.cbWndExtra = 0;
        w_cex.hInstance = w_h_instance;
        w_cex.hIcon = LoadIcon(w_cex.hInstance, IDI_APPLICATION);
        w_cex.hCursor = LoadCursor(NULL, IDC_ARROW);
        w_cex.hbrBackground = w_background_color;
        w_cex.lpszMenuName = NULL;
        w_cex.lpszClassName = w_class_name.c_str();
        w_cex.hIconSm = LoadIcon(w_cex.hInstance, IDI_APPLICATION);
    }

    void Window::RegisterWindow() {
        if (!RegisterClassEx(&w_cex))
        {
            MessageBox(NULL,
                _T("Call to RegisterClassEx failed!"),
                _T("Windows Desktop Guided Tour"),
                NULL);

            return;
        }
    }

    void Window::InstanceWindow(int start_x, int start_y) {
        HWND temp_hwnd = NULL;

        if (w_parent_hwnd != NULL) { //
            temp_hwnd = w_parent_hwnd;
        }

        w_hwnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            w_class_name.c_str(),
            w_title.c_str(),
            WS_OVERLAPPEDWINDOW,
            w_width, w_height,
            start_x, start_y,
            temp_hwnd,
            NULL,
            w_cex.hInstance,
            w_state);

        if (!w_hwnd)
        {
            MessageBox(NULL,
                _T("Call to CreateWindow failed!"),
                _T("Windows Desktop Guided Tour"),
                NULL);

            return;
        }

        ShowWindow(w_hwnd, w_cmd_show);
        UpdateWindow(w_hwnd);
    }

    //Getters
    StateInfo* Window::GetAppState() {
        LONG_PTR ptr = GetWindowLongPtr(w_hwnd, GWLP_USERDATA);
        StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
        return pState;
    }

    HWND Window::GetHWND() {
        return w_hwnd;
    }

    bool Window::GetExit() {
        return exit;
    }

    //Setters
    void Window::SetTitle(LPCWSTR newTitle) {	//Param: Should be a Wide Character when passed
        SetWindowTextW(w_hwnd, newTitle);
    }

    void Window::SetBackgroundColor(COLORREF color) {
        PAINTSTRUCT ps;
        w_background_color = (HBRUSH)CreateSolidBrush(color);
        InvalidateRect(w_hwnd, &ps.rcPaint, true);
        UpdateWindow(w_hwnd);
    }
}