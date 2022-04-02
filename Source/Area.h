#pragma once
namespace game_framework {

	class area {
	private:
		/* data */
		int _Lx, _Ly, _w, _h;
		int _Rx, _Ry;
	public:
		area(/* args */);
		bool touch(const area &other);

		void init(int x, int y, int w, int h);
		void	setPosetion(int x, int y) {
			_Lx = x; _Ly = y;
			_Rx = _Lx + _w;
			_Ry = _Ly + _h;
		}


		int get_x() {
			return _Lx;
		}
		int get_y() {
			return _Ly;
		}
	};

}