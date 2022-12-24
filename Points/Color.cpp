#include "Color.h"

namespace Orange {

	//Constructor
	Color::Color(int _r, int _g, int _b) {
		SetRGB(_r, _g, _b);
	}

	int Color::Clamp(int min, int max, int num) {
		if (num >= min && num <= max) {
			return num;
		}
		else {
			if (num < min) {
				return min;
			}
			else {
				return max;
			}
		}
	}

	//Getters
	int Color::GetR() {
		return r;
	}

	int Color::GetG() {
		return g;
	}

	int Color::GetB() {
		return b;
	}

	//Setters
	void Color::SetRGB(int _r, int _g, int _b) {
		r = Clamp(0, 255, _r);
		g = Clamp(0, 255, _g);
		b = Clamp(0, 255, _b);
	}
}