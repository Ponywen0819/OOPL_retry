#pragma once

namespace game_framework {

	class CStateBar {
	public:
		CStateBar();
		void LoadBitmap();
		void OnShowBar(int player1,int player2);
		bool Player1HPState(int HP1, int HP2);
		bool Player2HPState(int HP1, int HP2);
		bool Player1MPState(int MP);
		bool Player2MPState(int MP);
		void p1regen_hp();
		void p1regen_mp();
		void p2regen_hp();
		void p2regen_mp();

	protected:
		CMovingBitmap bar;
		CMovingBitmap HP1;
		CMovingBitmap HP2;
		CMovingBitmap MP1;
		CMovingBitmap MP2;
		CMovingBitmap character[3];


	private:
		int cma_x[4], cma_y[2];
		int player1, player2;
		int p1_hp1, p1_hp2,p1_mp,p2_hp1,p2_hp2,p2_mp;
		int delay1_hp ,delay1_mp, delay2_hp, delay2_mp;


	};
}