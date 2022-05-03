
#include "stdafx.h"
#include "Area.h"

namespace game_framework {
	area::area(/* args */) {
		_Lx = _Ly = _Rx = _Ry = _w = _h = 0;
	}

	bool area::touch(const area &other) {
		double min_x = other._Lx > _Lx ? other._Lx : _Lx;
		double min_y = other._Ly > _Ly ? other._Ly : _Ly;
		double max_x = other._Rx < _Rx ? other._Rx : _Rx;
		double max_y = other._Ry < _Ry ? other._Ry : _Ry;
		TRACE("%.1f %.1f %.1f %.1f\n", min_x, min_y, max_x, max_y);
		if (min_x > max_x || min_y > max_y) {
			return false;
		}
		else {
			return true;
		}
	}

	void area::init(double x1, double y1, double x2, double y2, double w, double h, bool f, int max) {
		_Lx = x1;
		_Ly = y1;
		if (f) {
			_Rx = _Lx - x2 + max;
			_Lx = _Rx - w;
		}
		else {
			_Lx += x2;
			_Rx = _Lx + w;
		}
		_Ly += y2;
		_Ry = _Ly + h;
	}
}