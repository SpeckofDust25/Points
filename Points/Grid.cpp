#include "Grid.h"

namespace Orange {

	//Constructor and Destructor
	Grid::Grid(int _width, int _height) {
		line_color.r = 0.0f;
		line_color.g = 0.0f;
		line_color.b = 0.0f;
		line_color.a = 1.0f;

		point_color.r = 1.0f;
		point_color.g = 0.0f;
		point_color.b = 0.0f;
		point_color.a = 1.0f;

		background_color.r = 1.0f;
		background_color.g = 1.0f;
		background_color.b = 1.0f;
		background_color.a = 1.0f;
	}

	//Draw Method
	void Grid::OnPaint(HWND hwnd) {
		HRESULT hr = CreateGraphicsResource(hwnd);
		if (SUCCEEDED(hr)) {
			r_render_target->BeginDraw();
			r_render_target->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
			r_render_target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			r_render_target->Clear(D2D1::ColorF(D2D1::ColorF::White));
			GenerateGrid(32, 32);

			r_render_target->CreateSolidColorBrush(line_color, &r_brush);

			for (int i = 0; i < lines.size(); i++) {
				r_render_target->DrawLine(lines[i].start_position, lines[i].end_position, r_brush, lines[i].thickness);
			}
			//r_brush->Release();
			r_brush->Release();
			r_brush = NULL;

			//r_render_target->CreateSolidColorBrush(point_color, &r_brush);

			for (int i = 0; i < points.size(); i++) {
				r_render_target->DrawEllipse(points[i].ellipse, r_brush, 1.0f);
			}

			hr = r_render_target->EndDraw();

			if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
				DiscardGraphicsResources();
			}
		}
	}

	//Add Line and Point
	void Grid::AddLine(Line line) {
		lines.push_back(line);
	}

	void Grid::AddPoint(Circle circle) {
		points.push_back(circle);
	}

	//Generates Grid: Should Be Called Every WM_PAINT and Whenever The Matrix is Translated
	void Grid::GenerateGrid(int grid_width, int grid_height) {
		if (r_render_target != nullptr) {
			D2D1_SIZE_F size = r_render_target->GetSize();
			screen_width = size.width;
			screen_height = size.height;

			if (grid_width != 0 && grid_height != 0 && screen_width != 0 && screen_height != 0) {
				int lines_horizontal = screen_height / grid_width;
				int lines_vertical = screen_width / grid_height;

				ClearGrid();

				for (int i = 0; i < lines_horizontal; i++) {	//Horizontal
					AddLine(Line{ 1, D2D_POINT_2F {0, (float)(grid_width * (i + 1))}, D2D_POINT_2F {(float)screen_width, (float)(grid_width * (i + 1))} });
				}

				for (int i = 0; i < lines_vertical; i++) {	//Vertical
					AddLine(Line{ 1, D2D_POINT_2F {(float)(grid_height * (i + 1)), 0}, D2D_POINT_2F {(float)(grid_height * (i + 1)), (float)screen_height} });
				}
			}
		}
	}

	void Grid::ClearGrid() {
		lines.clear();
	}
}