#pragma once
namespace game_framework {
	class SP {
	public:

		void init();
		void showmap(int);
		int map_pos();
	private:
		gamemap wall[2];
		gamemap fire_ani;
		gamemap wall_ani;
	};
}
