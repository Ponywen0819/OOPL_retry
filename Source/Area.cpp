
#include "stdafx.h"
#include "Area.h"

namespace game_framework {
	area::area(/* args */) {
		_Lx = _Ly = _Rx = _Ry = _w = _h = 0;
	}

	bool area::touch(const area &other) {
		int min_x = other._Lx > _Lx ? other._Lx : _Lx;
		int min_y = other._Ly > _Ly ? other._Ly : _Ly;
		int max_x = other._Rx < _Rx ? other._Rx : _Rx;
		int max_y = other._Ry < _Ry ? other._Ry : _Ly;
		if (min_x > max_x || min_y > max_y) {
			return false;
		}
		else {
			return true;
		}
	}

	void area::init(int x, int y, int w, int h) {
		_Lx = x; _Ly = y; _w = w; _h = h;
		_Rx = _Lx + _w;
		_Ry = _Ly + _h;
	}
}