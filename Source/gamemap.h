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

		void LoadBitmap(char *, COLORREF = RGB(0,0,0));
		void AddBitmap(char *, COLORREF = RGB(0, 0, 0));
		void calShow();
		void onShow(int a);
		int map_pos();
		void delay(int,int);

	private:

		CAnimation back_ground_ani;
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
		int last_pos = 0;
	};
}