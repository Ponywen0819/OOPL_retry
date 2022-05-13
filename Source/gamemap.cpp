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

	void gamemap::AddBitmap(char *filename, COLORREF color) {
		back_ground_ani.AddBitmap(filename, color);
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

	void gamemap::set(double mw, double lw, int x, int y, int loop,int cc) {
		map_width = mw;
		layer_width = lw;
		_x = x;
		_y = y;
		_loop = loop;
		_cc = cc;
		/*_c1 = c1;
		_c2 = c2;*/
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
	
	void gamemap::onShow(int _man_pos) {
		int total_pos = _man_pos;
		if (total_pos % 2 == 1)total_pos += 1;
		if (total_pos / 2 > last_pos) {
			for (temp2; temp2 <= last_pos; temp2++) {
				if (move_pixel_right != 0 && temp2 > move_pixel_right && temp2 >= 0) {
					if (move_pixel_right < temp * (layer_dis - 1)) {
						_x--;
						move_pixel_right += temp;
						move_pixel_left += temp;
					}
				}
			}
			last_pos = total_pos / 2;
		}
		if (total_pos / 2 < last_pos) {
			for (temp2; temp2 >= last_pos; temp2--) {
				if (move_pixel_left != 0 && temp2 < move_pixel_left && temp2 >= 0) {
					_x++;
					move_pixel_right -= temp;
					move_pixel_left -= temp;
				}
			}
			last_pos = total_pos / 2;
		}
		//TRACE("%d %1.f %1.f\n", temp2, move_pixel_right, temp * (layer_dis - 1));

		if (_cc) {
			back_ground_ani.SetTopLeft(_x , _y);
			back_ground_ani.OnMove();
			back_ground_ani.OnShow();
		}
		else {
			back_ground.SetTopLeft(_x, _y);
			back_ground.ShowBitmap();
		}
		

		if (_loop) {
			int temp_loop = _loop;
			for (int i = 0; i < map_width / _loop; i++) {
				if (_cc) {
					back_ground_ani.SetTopLeft(_x + temp_loop, _y);
					back_ground_ani.OnMove();
					back_ground_ani.OnShow();
				}
				else {
					back_ground.SetTopLeft(_x + temp_loop, _y);
					back_ground.ShowBitmap();
				}
				
				temp_loop += _loop;
			}
		}
		//delay(_man_pos1, _man_pos2);
	}

	void gamemap::delay(int _man_pos1, int _man_pos2) {
		int total_pos = _man_pos1 + _man_pos2;
		if (total_pos % 2 == 1)total_pos += 1;
		if (total_pos / 2 > last_pos) {
			for (temp2; temp2<= last_pos; temp2++) {
				
			}
			last_pos = total_pos / 2;
			
		}
		else if (total_pos / 2 < last_pos) {
			for (temp2; temp2 >= last_pos; temp2--) {
				
			}
			last_pos = total_pos / 2;
		}
		//TRACE("last_pos: %d \n",last_pos);
		//TRACE("%d %d %1.f\n", _man_pos1 ,_man_pos2, temp * (layer_dis - 1));
	}


	int gamemap::map_pos() {
		return temp2;
	}
}