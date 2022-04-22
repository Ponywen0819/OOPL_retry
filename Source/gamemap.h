#pragma once

namespace game_framework {

	class gamemap {
	
	public:
		gamemap() {
			map_width = 0;
			layer_width = 0;
			_x = 0;
			_y = 0;
		}
		void set(double mw, double lw, int x, int y);
		void set(double mw, double lw, int x, int y, int loop);

		void LoadBitmap(char *qwwq, COLORREF = RGB(0,0,0));
		
		void calShow();
		void onShow();
		void onShow(int a);
	
		void delay();

	private:

		CMovingBitmap back_ground;
		double map_width;
		double layer_width;
		int _x;
		int _y;
		int _loop = 0;

		double move_pixel_left;
		double move_pixel_right;
		double temp;
		double layer_dis;

		int delay1 = 10;
		int temp2 = 0;

	};
}