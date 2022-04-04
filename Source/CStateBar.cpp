#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CBall.h"
#include "CStateBar.h"

namespace game_framework {


	CStateBar::CStateBar() {
		p1_hp1 = 500;
		p1_hp2 = 500;
		p1_mp = 500;
		p2_hp1 = 500;
		p2_hp2 = 500;
		p2_mp = 500;

		delay1_hp = 50;
		delay1_mp = 40;
		delay2_hp = 50;
		delay2_mp = 40;
		
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

	void CStateBar::OnShowBar(int player1,int player2) {
		bar.SetTopLeft(0, 0);
		bar.ShowBitmap();
		if (player1 != -1 ) {
			character[player1].SetTopLeft(97, 33);
			character[player1].ShowBitmap();
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
			p1regen_hp();
			p1regen_mp();
		}
		if (player2 != -1) {
			character[player2].SetTopLeft(493, 33);
			character[player2].ShowBitmap();
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
			p2regen_hp();
			p2regen_mp();
		}
	}

	bool CStateBar::Player1HPState(int HP1, int HP2) {
		if (p1_hp1 > 0) {
			p1_hp1 -= HP1;
			p1_hp2 -= HP2;
			delay1_hp = 50;
			delay1_mp = 40;
			return TRUE;
		}
		return FALSE;
		
		
		
	}
	bool CStateBar::Player2HPState(int HP1, int HP2) {
		if (p2_hp1 > 0) {
			p2_hp1 -= HP1;
			p2_hp2 -= HP2;
			delay2_hp = 50;
			delay2_mp = 40;
			return TRUE;
		}
		return FALSE;
		
		
	}
	bool CStateBar::Player1MPState(int MP) {
		if (p1_mp >= MP) {
			p1_mp -= MP;
			return TRUE;
		}
		return FALSE;
	}

	bool CStateBar::Player2MPState(int MP) {
		if (p2_mp >= MP) {
			p2_mp -= MP;
			return TRUE;
		}
		return FALSE;
	}


	void CStateBar::p1regen_hp() {
		//TRACE("%d\n",delay1_hp);
		if (--delay1_hp < 0 ) {
			if (p1_hp1 < p1_hp2 && p1_hp1 > 0) {
				p1_hp1+=3;
				if (p1_hp1 > p1_hp2) {
					p1_hp1 = p1_hp2;
				}
			}
			delay1_hp = 50;
		}
	}
	void CStateBar::p1regen_mp() {
		if (--delay1_mp < 0) {
			if (p1_mp < 500) {
				p1_mp += 3;
				if (p1_mp > 500) {
					p1_mp = 500;
				}
			}
			delay1_mp = 40;
		}
	}
	void CStateBar::p2regen_hp() {
		//TRACE("%d\n", delay2_hp);
		if (--delay2_hp < 0) {
			if (p2_hp1 < p2_hp2 && p2_hp1 > 0) {
				p2_hp1 += 3;
				if (p2_hp1 > p2_hp2) {
					p2_hp1 = p2_hp2;
				}
			}
			delay2_hp = 50;
		}
	}
	void CStateBar::p2regen_mp() {
		if (--delay2_mp < 0) {
			if (p2_mp < 500) {
				p2_mp += 3;
				if (p2_mp > 500) {
					p2_mp = 500;
				}
			}
			delay2_mp = 40;
		}
	}

}