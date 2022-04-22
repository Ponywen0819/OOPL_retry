#pragma once


namespace game_framework {
	class lf{
	public:
		
		void init();
		void showmap(int a);

	private:
		gamemap forests;
		gamemap forestm[4];
		gamemap forestt;
		gamemap land[4];
	};
}
