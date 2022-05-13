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
		int _map_width();
		int _upper();
		int _lower();
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
		int _map_width();
		int _upper();
		int _lower();
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
		int _map_width();
		int _upper();
		int _lower();
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
		int _map_width();
		int _upper();
		int _lower();
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
			delay1 = 100;
			now_stage = 0;
			map = 0;
			temp = 0;
			trans_index = 1;
			branch = FALSE;
			main = TRUE;
			clean = FALSE;
			over = FALSE;
		}


		void init(int);
		void OnShow(int);
		void info();
		void delay();
		void test();
		boolean check(int);
		boolean overgame();
		void show_trans();

		int get_mapwidth();
		int get_upbound();
		int get_downbound();
		int get_mappos();


	private:



		SP* sp1 =new SP;
		lf* lf1 = new lf;
		temp1* ex1 = new temp1;
		GW* gw1 = new GW;

		CMovingBitmap trans[16];
		std::string path;
		boolean branch;
		boolean main;
		boolean clean;
		boolean over;

		int now_stage;
		int map;
		int map_width;
		int upper_bound;
		int lower_bound;
		int map_pos;
		int a;
		int man_pos;
		int delay1;
		int temp;
		int trans_index;
	};


}

