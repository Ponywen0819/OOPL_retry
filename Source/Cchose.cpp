#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CBall.h"
#include "Cchose.h"



namespace game_framework {
	Cchose::Cchose()
	{
		cma_ani.SetDelayCount(5);
		CountDown.SetDelayCount(10);
		for (int i = 0; i < 3; i++) {
			name[i].SetDelayCount(8);
		}

	}

	Cchose::~Cchose()
	{
	}

	void Cchose::LoadBitmap() {
		charmenu.LoadBitmap("./Bitmaps/menu.bmp");
		character[0].LoadBitmap("./Bitmaps/deep_f.bmp");
		character[1].LoadBitmap("./Bitmaps/freeze_f.bmp");
		character[2].LoadBitmap("./Bitmaps/firen_f.bmp");
		player[0].LoadBitmap("./Bitmaps/1.bmp", RGB(0, 0, 0));
		player[1].LoadBitmap("./Bitmaps/2.bmp", RGB(0, 0, 0));
		logo.LoadBitmap("./Bitmaps/MENU_BACK1.bmp", RGB(0, 0, 0));
		back.LoadBitmap("./Bitmaps/start_background.bmp");
		title.LoadBitmap("./Bitmaps/title.bmp", RGB(17, 34, 101));
		team.LoadBitmap("./Bitmaps/team.bmp");
		option[0].LoadBitmap("./Bitmaps/menu_start.bmp", RGB(255, 255, 255));
		option[1].LoadBitmap("./Bitmaps/menu_start_r.bmp", RGB(90, 119, 216));
		option[2].LoadBitmap("./Bitmaps/menu_quit.bmp", RGB(255, 255, 255));
		option[3].LoadBitmap("./Bitmaps/menu_quit_r.bmp", RGB(90, 119, 216));
		lock[0].LoadBitmap("./Bitmaps/deep_1.bmp");
		lock[1].LoadBitmap("./Bitmaps/Freeze_1.bmp");
		lock[2].LoadBitmap("./Bitmaps/Fizen_1.bmp");

		char *filename[2] = { ".\\Bitmaps\\CMA.bmp", ".\\Bitmaps\\CMA2.bmp" };

		for (int i = 0; i < 2; i++) {
			cma_ani.AddBitmap(filename[i], RGB(0, 0, 0));
		}
		char *filename_CountDown[6] = { ".\\Bitmaps\\CM5.bmp", ".\\Bitmaps\\CM4.bmp",".\\Bitmaps\\CM3.bmp",".\\Bitmaps\\CM2.bmp",".\\Bitmaps\\CM1.bmp",".\\Bitmaps\\CM0.bmp" };
		for (int i = 0; i < 6; i++) {
			CountDown.AddBitmap(filename_CountDown[i]);
		}
		char *filename_deep[4] = { ".\\Bitmaps\\deep_1.bmp", ".\\Bitmaps\\deep_2.bmp",".\\Bitmaps\\deep_3.bmp",".\\Bitmaps\\deep_4.bmp" };
		for (int i = 0; i < 4; i++) {
			name[0].AddBitmap(filename_deep[i], RGB(0, 0, 0));
		}

		char *filename_freeze[4] = { ".\\Bitmaps\\Freeze_1.bmp", ".\\Bitmaps\\Freeze_2.bmp",".\\Bitmaps\\Freeze_3.bmp",".\\Bitmaps\\Freeze_4.bmp" };
		for (int i = 0; i < 4; i++) {
			name[1].AddBitmap(filename_freeze[i], RGB(0, 0, 0));
		}
		char *filename_fizen[4] = { ".\\Bitmaps\\Fizen_1.bmp", ".\\Bitmaps\\Fizen_2.bmp",".\\Bitmaps\\Fizen_3.bmp",".\\Bitmaps\\Fizen_4.bmp" };
		for (int i = 0; i < 4; i++) {
			name[2].AddBitmap(filename_fizen[i], RGB(0, 0, 0));
		}

	}

	void Cchose::OnShowMenu(int index) {

		if (index == 1) {
			back.SetTopLeft(0, 0);
			back.ShowBitmap();

			logo.SetTopLeft(0, 0);
			logo.ShowBitmap();

			title.SetTopLeft((SIZE_X - title.Width()) / 2, SIZE_Y / 9);
			title.ShowBitmap();
		}
		else if (index == 2) {
			charmenu.SetTopLeft((SIZE_X - charmenu.Width()) / 2, (SIZE_Y - charmenu.Height()) / 2);
			charmenu.ShowBitmap();
			cma_ani.SetTopLeft(222, 225);
			cma_ani.OnShow();
			cma_ani.SetTopLeft(457, 225);
			cma_ani.OnShow();
			cma_ani.OnMove();
			for (int i = 0; i < 4; i++) {

			}
		}
	}

	void Cchose::OnShowSelect(int index) {
		if (index == 0) {
			option[1].SetTopLeft((SIZE_X - option[0].Width()) / 2, SIZE_Y * 5 / 9);
			option[1].ShowBitmap();
			option[2].SetTopLeft((SIZE_X - option[2].Width()) / 2, SIZE_Y * 5 / 9 + 50);
			option[2].ShowBitmap();
		}
		else {
			option[0].SetTopLeft((SIZE_X - option[0].Width()) / 2, SIZE_Y * 5 / 9);
			option[0].ShowBitmap();
			option[3].SetTopLeft((SIZE_X - option[2].Width()) / 2, SIZE_Y * 5 / 9 + 50);
			option[3].ShowBitmap();
		}

	}

	void Cchose::OnShowChar1(int index) {
		character[index].SetTopLeft(224, 195);
		character[index].ShowBitmap();
		player[0].SetTopLeft(224, 318);
		player[0].ShowBitmap();
		OnShowCharAni(1, index);
	}

	void Cchose::OnShowChar2(int index) {
		character[index].SetTopLeft(458, 195);
		character[index].ShowBitmap();
		player[1].SetTopLeft(458, 318);
		player[1].ShowBitmap();
		OnShowCharAni(2, index);
	}

	void Cchose::OnShowCharAni(int player, int index) {
		player == 1 ? name[index].SetTopLeft(224, 340) : name[index].SetTopLeft(458, 340);
		name[index].OnShow();
		if (player1 == player2) {
			if (player == 1) {
				name[index].OnMove();
			}
		}
		else {
			name[index].OnMove();
		}
	}

	void Cchose::OnShowCharLock(int player1_lock, int player2_lock) {

		if (player1_lock == 1) {
			lock[player1].SetTopLeft(224, 340);
			lock[player1].ShowBitmap();
			team.SetTopLeft(224, 362);
			team.ShowBitmap();
		}
		if (player2_lock == 1) {
			lock[player2].SetTopLeft(458, 340);
			lock[player2].ShowBitmap();
			team.SetTopLeft(458, 362);
			team.ShowBitmap();
		}
	}

	bool Cchose::OnShowCountDown(int player1_lock, int player2_lock) {
		if (player1_lock == 1 && player2_lock == 1) {
			CountDown.SetTopLeft(224, 195);
			CountDown.OnShow();
			CountDown.SetTopLeft(458, 195);
			CountDown.OnShow();

		}
		else if (player1_lock == 1) {
			CountDown.SetTopLeft(458, 195);
			CountDown.OnShow();
		}
		else {
			CountDown.SetTopLeft(224, 195);
			CountDown.OnShow();
		}
		CountDown.OnMove();
		if (CountDown.GetCurrentBitmapNumber() == 5) {
			return TRUE;
		}
		return FALSE;
	}

	int Cchose::Get_player1(int player1_index) {

		return player1 = abs(player1_index % 3);
	}

	int Cchose::Get_player2(int player2_index) {

		return player2 = abs(player2_index % 3);
	}
}