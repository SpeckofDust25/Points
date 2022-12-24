#pragma once

namespace Orange {
	class Color {
	private:
		int r;
		int g;
		int b;
		int Clamp(int min, int max, int num);

	public:
		Color(int _r, int _g, int _b);

		//Getters
		int GetR();
		int GetG();
		int GetB();

		//Setters
		void SetRGB(int _r, int _g, int _b);
	};
}