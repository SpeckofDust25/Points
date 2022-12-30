#pragma once
#include <d2d1.h>

namespace Orange {
	struct Circle {
	public:
		D2D1_ELLIPSE ellipse;
	};

	struct Line {
	public:
		double thickness;
		D2D1_POINT_2F start_position;
		D2D1_POINT_2F end_position;
	};
}