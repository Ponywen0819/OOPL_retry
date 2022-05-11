#pragma once

namespace game_framework {

	class SP {
	public:
		SP() {
			map_width = 2400;
			upper_bound = 292;
			lower_bound = 495;
		}
		void init();
		void showmap(int);
		int map_pos();
	private:
		gamemap wall[2];
		gamemap fire_ani;
		gamemap wall_ani;
		int map_width;
		int upper_bound;
		int lower_bound;
	};

	class lf {
	public:
		lf() {
			map_width = 3200;
			upper_bound = 365;
			lower_bound = 505;
		}
		void init();
		void showmap(int);
		int map_pos();
	private:
		gamemap forests;
		gamemap forestm[4];
		gamemap forestt;
		gamemap land[4];
		int map_width;
		int upper_bound;
		int lower_bound;
	};

	class temp1 {
	public:
		temp1() {
			map_width = 1600;
			upper_bound = 370;
			lower_bound = 510;
		}
		void init();
		void showmap(int);
		int map_pos();

	private:
		gamemap pic[8];
		int map_width;
		int upper_bound;
		int lower_bound;
	};

	class GW {
	public:
		GW() {
			map_width = 2400;
			upper_bound = 326;
			lower_bound = 477;
		}
		void init();
		void showmap(int);
		int map_pos();
	private:
		gamemap sky;
		gamemap ground;
		gamemap hill[2];
		gamemap road[3];
		int map_width;
		int upper_bound;
		int lower_bound;
	};

	class stage {
	public:
		stage() {
			now_stage = 0;
			map = 2;
		}


		void init();
		void OnShow(int);


	private:



		SP* sp1 =new SP;
		lf* lf1 = new lf;
		temp1* ex1 = new temp1;
		GW* gw1 = new GW;

		int now_stage;
		int map;
	};


}

