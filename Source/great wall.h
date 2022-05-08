#pragma once

namespace game_framework {
	class GW {
	public:

		void init();
		void showmap(int);
		int map_pos();
	private:
		gamemap sky;
		gamemap ground;
		gamemap hill[2];
		gamemap road[3];
		
	};
}
