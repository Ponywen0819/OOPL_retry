#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CStateBar.h"

namespace game_framework {


	CStateBar::CStateBar() {
		p1_hp1 = 500;
		p1_hp2 = 500;
		p1_mp = 500;
		p2_hp1 = 500;
		p2_hp2 = 500;
		p2_mp = 500;
	}

	void CStateBar::LoadBitmap() {
		bar.LoadBitmap("./Bitmaps/state/bar.bmp");
		character[0].LoadBitmap("./Bitmaps/state/deep_s.bmp", RGB(50, 77, 154));
		character[1].LoadBitmap("./Bitmaps/state/freeze_s.bmp", RGB(50, 77, 154));
		character[2].LoadBitmap("./Bitmaps/state/firen_s.bmp", RGB(50, 77, 154));
		HP1.LoadBitmap("./Bitmaps/state/HP1.bmp");
		HP2.LoadBitmap("./Bitmaps/state/HP2.bmp");
		MP1.LoadBitmap("./Bitmaps/state/MP1.bmp");
		MP2.LoadBitmap("./Bitmaps/state/MP2.bmp");

	}

	void CStateBar::init(int player1, int player2) {
		this->p1 = player1;
		this->p2 = player2;
		if (player2 == -1) {
			state = 0;
		}
		else if (player1 == -1) {
			state = 1;
		}
		else {
			state = 2;
		}

		p1_hp1 = 500;
		p1_hp2 = 500;
		p1_mp = 500;
		p2_hp1 = 500;
		p2_hp2 = 500;
		p2_mp = 500;
	}

	void CStateBar::OnShowBar() {
		bar.SetTopLeft(0, 0);
		bar.ShowBitmap();
		if (p1 != -1 ) {
			character[p1].SetTopLeft(97, 33);
			character[p1].ShowBitmap();
			if (p1_hp1 > 0) {
				for (int i = 0; i < p1_hp2 / 10; i++) {
					HP2.SetTopLeft(147 + i * 3, 44);
					HP2.ShowBitmap();
				}
				for (int i = 0; i < p1_hp1 / 10; i++) {
					HP1.SetTopLeft(147 + i * 3, 44);
					HP1.ShowBitmap();
				}
				MP2.SetTopLeft(147, 64);
				MP2.ShowBitmap();
				for (int i = 0; i < p1_mp / 10; i++) {
					MP1.SetTopLeft(147 + i * 3, 64);
					MP1.ShowBitmap();
				}
			}
		}

		if (p2 != -1) {
			character[p2].SetTopLeft(493, 33);
			character[p2].ShowBitmap();
			if (p2_hp1 > 0) {
				for (int i = 0; i < p2_hp2 / 10; i++) {
					HP2.SetTopLeft(543 + i * 3, 44);
					HP2.ShowBitmap();
				}
				for (int i = 0; i < p2_hp1 / 10; i++) {
					HP1.SetTopLeft(543 + i * 3, 44);
					HP1.ShowBitmap();
				}
				MP2.SetTopLeft(543, 64);
				MP2.ShowBitmap();
				for (int i = 0; i < p2_mp / 10; i++) {
					MP1.SetTopLeft(543 + i * 3, 64);
					MP1.ShowBitmap();
				}
			}
		}
	}

	void CStateBar::Player1HPState(int HP1, int HP2) {
		if (HP1 == p1_hp1) {
			if (HP1 == 500) {
				p1_hp1 = p1_hp2 = 500;
			}
		}
		else if(p1_hp1 > 0) {
			p1_hp1 = HP1;
			p1_hp2 = HP2;
		}
		//TRACE("%d %d\n", p1_hp1, p1_hp2);
	}
	void CStateBar::Player2HPState(int HP1, int HP2) {
		if (HP1 == p2_hp1) {
			if (HP1 == 500) {
				p2_hp1 = p2_hp2 = 500;
			}
			return;
		}
		if (p2_hp1 > 0) {
			p2_hp1 = HP1;
			p2_hp2 = HP2;
		}
	}

	void CStateBar::setHP(int p,int HP1,int HP2) {
		//TRACE("%d %d %d \n",p,HP1,HP2);
		if (p == 0) {
			Player1HPState(HP1, HP2);
		}
		else {
			Player2HPState(HP1, HP2);
		}
	}
	void CStateBar::Player1MPState(int MP) {
		p1_mp = MP;
	}

	void CStateBar::Player2MPState(int MP) {
		p2_mp = MP;
	}

	void CStateBar::setMP(int p, int MP) {
		if (p == 0) {
			Player1MPState(MP);
		}
		else {
			Player2MPState(MP);
		}
	}
}