#pragma once
namespace game_framework {

	class area {
	private:
		/* data */
		double _Lx, _Ly, _w, _h;
		double _Rx, _Ry;
	public:
		area(/* args */);
		bool touch(const area &other);

		void init(double x1, double y1, double x2, double y2, double w, double h,bool f ,int);
		void	setPosetion(int x, int y) {
			_Lx = x; _Ly = y;
			_Rx = _Lx + _w;
			_Ry = _Ly + _h;
		}


		double get_x() {
			return _Lx;
		}
		double get_y() {
			return _Ly;
		}
	};

}