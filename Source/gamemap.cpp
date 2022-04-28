#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gamemap.h"

namespace game_framework {

	void gamemap::LoadBitmap(char *filename, COLORREF color) {
		back_ground.LoadBitmap(filename, color);
	}

	void gamemap::set(double mw, double lw, int x, int y) {
		map_width = mw;
		layer_width = lw;
		_x = x;
		_y = y;
	}

	void gamemap::set(double mw, double lw, int x, int y, int loop) {
		map_width = mw;
		layer_width = lw;
		_x = x;
		_y = y;
		_loop = loop;
	}

	void gamemap::calShow() {
		move_pixel_left = 0;
		move_pixel_right = 0;
		layer_dis = layer_width - 800;

		if (layer_dis != 0) {
			move_pixel_right = map_width / layer_dis;
			temp = move_pixel_right;
		}
		else {
			move_pixel_right = 0;
		}
		// TRACE("!!!%.3f %.3f %.3f %d %.3f\n",  move_pixel_right, layer_dis, layer_width, back_ground.Width(), temp);
	}
	void gamemap::onShow() {



		if (move_pixel_right != 0 && temp2 > move_pixel_right) {
			
			if (move_pixel_right < temp * (layer_dis - 1)) {
				_x--;
				move_pixel_right += temp;
				move_pixel_left += temp;
				// TRACE("%d %1.f %1.f\n", temp2, move_pixel_right, temp * (layer_dis - 1));
			}
		}

		back_ground.SetTopLeft(_x, _y);
		back_ground.ShowBitmap();

		if (_loop) {
			int temp_loop = _loop;
			for (int i = 0; i < map_width / _loop; i++) {
				back_ground.SetTopLeft(_x + temp_loop, _y);
				back_ground.ShowBitmap();
				temp_loop += _loop;
			}
		}
		delay();

	}
	void gamemap::onShow(int man_position) {
		

		
		if (move_pixel_right != 0 && man_position > move_pixel_right) {
			_x--;
			if (move_pixel_right < temp * (layer_dis - 1)) {
				move_pixel_right += temp;
				move_pixel_left += temp;
				// TRACE("%d %d\n", man_position, move_pixel_right);
			}
		}

		/*if (move_pixel_left != 0 && man_position < move_pixel_left) {
			_x++;
			move_pixel_right -= temp;
			move_pixel_left -= temp;
		}*/
		back_ground.SetTopLeft(_x, _y);
		back_ground.ShowBitmap();


	}

	void gamemap::delay() {
		if (--delay1 < 0) {
			temp2++;
			delay1 = 0;
		
		}
	}
}