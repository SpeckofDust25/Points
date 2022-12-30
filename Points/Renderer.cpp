#include "Renderer.h"

namespace Orange {

	Renderer::Renderer() {
	
	}

	//Re-calculate drawing layout when the size of the window changes
	void Renderer::CalculateLayout() {
		if (r_render_target != NULL) {
			D2D1_SIZE_F size = r_render_target->GetSize();
			const float x = size.width / 2;
			const float y = size.height / 2;
			const float radius = min(x, y);
		}
	}

	//Create Resources
	HRESULT Renderer::CreateFactory() {
		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &r_factory);
		return hr;
	}

	HRESULT Renderer::CreateGraphicsResource(HWND hwnd) {
		HRESULT hr = S_OK;
		if (r_render_target == NULL) {
			RECT rc;
			GetClientRect(hwnd, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

			hr = r_factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(hwnd, size),
				&r_render_target);

			if (SUCCEEDED(hr)) {
				const D2D1_COLOR_F color = D2D1::ColorF(0.0f, 0.0f, 0.0f);
				hr = r_render_target->CreateSolidColorBrush(color, &r_brush);
				
				if (SUCCEEDED(hr)) {
					CalculateLayout();
				}
			}
		}

		return hr;
	}

	//Free Resources
	void Renderer::DiscardGraphicsResources() {
		if (r_render_target != NULL) {
			r_render_target->Release();
			r_render_target = NULL;
		}

		if (r_brush != NULL) {
			r_brush->Release();
			r_brush = NULL;
		}
	}

	void Renderer::ReleaseFactory() {
		if (r_factory != NULL) {
			r_factory->Release();
			r_factory = NULL;
		}
	}

	//Draw onto the Screen
	void Renderer::OnPaint(HWND hwnd) {
		HRESULT hr = CreateGraphicsResource(hwnd);
		if (SUCCEEDED(hr)) {
			r_render_target->BeginDraw();

			r_render_target->Clear(D2D1::ColorF(D2D1::ColorF::White));
			r_render_target->FillEllipse(ellipse, r_brush);

			hr = r_render_target->EndDraw();
			if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
				DiscardGraphicsResources();
			}
		}
	}

	void Renderer::Resize(HWND hwnd) {
		if (r_render_target != NULL) {
			RECT rc;
			GetClientRect(hwnd, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
			r_render_target->Resize(size);
			CalculateLayout();
			InvalidateRect(hwnd, NULL, FALSE);
		}
	}
}