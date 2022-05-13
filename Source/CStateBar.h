#pragma once

namespace game_framework {

	class CStateBar {
	public:
		CStateBar();
		void LoadBitmap();
		void init(int player1, int player2);
		void OnShowBar();
		void Player1HPState(int HP1, int HP2);
		void Player2HPState(int HP1, int HP2);
		void Player1MPState(int MP);
		void Player2MPState(int MP);
		void setHP(int p, int HP1, int HP2);
		void setMP(int p,int MP);
	protected:
		CMovingBitmap bar;
		CMovingBitmap HP1;
		CMovingBitmap HP2;
		CMovingBitmap MP1;
		CMovingBitmap MP2;
		CMovingBitmap character[3];


	private:
		int state;

		int cma_x[4], cma_y[2];
		int p1, p2;
		int p1_hp1, p1_hp2, p1_mp, p2_hp1, p2_hp2, p2_mp;
	};
}