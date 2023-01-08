#pragma once
#include <vector>
#include "Shapes.h"
#include "Renderer.h"

namespace Orange {
	class Grid: public Renderer
	{
	public:
		Grid(int _width = 32, int _height = 32);

	protected:
		D2D1_COLOR_F line_color;
		D2D1_COLOR_F point_color;
		D2D1_COLOR_F background_color;		
		std::vector<Line> lines;
		std::vector<Circle> points;

	protected:
		void AddLine(Line line);
		void ClearGrid();

	public:
		void GenerateGrid(int grid_width, int grid_height);
		void OnPaint(HWND hwnd) override;
		void AddPoint(Circle circle);
		void RemovePoint(int index);
		void ClearPoints();
	};
}

