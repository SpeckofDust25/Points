#pragma once
#include <Windows.h>
#include <d2d1.h>

//Direct 2D Renderer
namespace Orange {
	class Renderer
	{
		//Constructor and Destructor
	public:
		Renderer();

	protected:
		ID2D1Factory* r_factory;
		ID2D1HwndRenderTarget* r_render_target = NULL;
		ID2D1SolidColorBrush* r_brush = NULL;
		D2D1_ELLIPSE ellipse;
		int screen_width, screen_height;

	public:	//Methods
		void CalculateLayout();
		HRESULT CreateGraphicsResource(HWND hwnd);
		void DiscardGraphicsResources();
		virtual void OnPaint(HWND hwnd);
		void Resize(HWND hwnd);
		HRESULT CreateFactory();
		void ReleaseFactory();
	};
}

