#pragma once
namespace game_framework {
	class SP {
	public:

		void init();
		void showmap(int);
		int map_pos();
	private:
		gamemap wall;
		gamemap wall_ani;
		gamemap fire_ani;
	};
}
