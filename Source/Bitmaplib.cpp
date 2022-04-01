#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Bitmaplib.h"


namespace game_framework {

	Bitmaplib::Bitmaplib() {}

	void Bitmaplib::LoadBitmap() {
		punch.LoadBitmap(".\\Bitmaps\\punch.bmp",RGB(0,0,0));
		beaten1[0][0].LoadBitmap(".\\Bitmaps\\temp\\beaten\\L\\0.bmp", RGB(0, 0, 0));
		beaten1[1][0].LoadBitmap(".\\Bitmaps\\temp\\beaten\\R\\0.bmp", RGB(0, 0, 0));

		beaten1[0][1].LoadBitmap(".\\Bitmaps\\temp\\beaten\\L\\1.bmp", RGB(0, 0, 0));
		beaten1[1][1].LoadBitmap(".\\Bitmaps\\temp\\beaten\\R\\1.bmp", RGB(0, 0, 0));

		dizzy[0].LoadBitmap(".\\Bitmaps\\temp\\beaten\\L\\2.bmp", RGB(0, 0, 0));
		dizzy[1].LoadBitmap(".\\Bitmaps\\temp\\beaten\\R\\2.bmp", RGB(0, 0, 0));

		beatenR2[0][0].LoadBitmap(".\\Bitmaps\\temp\\beaten\\L\\3.bmp", RGB(0, 0, 0));
		beatenR2[1][0].LoadBitmap(".\\Bitmaps\\temp\\beaten\\R\\3.bmp", RGB(0, 0, 0));

		beatenR2[0][1].LoadBitmap(".\\Bitmaps\\temp\\beaten\\L\\4.bmp", RGB(0, 0, 0));
		beatenR2[1][1].LoadBitmap(".\\Bitmaps\\temp\\beaten\\R\\4.bmp", RGB(0, 0, 0));

		beatenL2[0][0].LoadBitmap(".\\Bitmaps\\temp\\beaten\\L\\5.bmp", RGB(0, 0, 0));
		beatenL2[1][0].LoadBitmap(".\\Bitmaps\\temp\\beaten\\R\\5.bmp", RGB(0, 0, 0));
		
		beatenL2[0][1].LoadBitmap(".\\Bitmaps\\temp\\beaten\\L\\6.bmp", RGB(0, 0, 0));
		beatenL2[1][1].LoadBitmap(".\\Bitmaps\\temp\\beaten\\R\\6.bmp", RGB(0, 0, 0));
;
	}

	void Bitmaplib::showBynumber(int i, int x, int y) {
		switch (i) {
		case 0:
			punch.SetTopLeft(x, y);
			punch.ShowBitmap();
			break;
		default:
			break;
		}
	}

	void Bitmaplib::setPunchTopLeft(int x, int y) {
		punch.SetTopLeft(x, y);
	}

	void Bitmaplib::showPunch() {
		punch.ShowBitmap();
	}

	void Bitmaplib::setbeatenTopLeft(int step, bool FaceToLeft, int index,int x,int y) {
		int f;
		if (FaceToLeft) f = 0;
		else f = 0;

		switch (step) {
		case 0:				// 被打第一下
			beaten1[f][index].SetTopLeft(x, y);
			break;
		case 1:				// 被右邊打
			beatenR2[f][index].SetTopLeft(x, y);
			break;
		case 2:				// 被左邊打
			beatenL2[f][index].SetTopLeft(x, y);
			break;
		case 3:
			dizzy[f].SetTopLeft(x, y);
			break;
		}
	}

	void Bitmaplib::showBeaten(int step, bool FaceToLeft, int index) {
		int f;
		if (FaceToLeft) f = 0;
		else f = 0;

		switch (step) {
		case 0:				// 被打第一下
			beaten1[f][index].ShowBitmap();
			break;
		case 1:				// 被右邊打
			beatenR2[f][index].ShowBitmap();
			break;
		case 2:				// 被左邊打
			beatenL2[f][index].ShowBitmap();
			break;
		case 3:
			dizzy[f].ShowBitmap();
			break;
		}
	}

	PAnimation::PAnimation(Bitmaplib *l) :num{ 0 }, index{ 0 }, lib{ l }{}

	void PAnimation::addBitmap(int i) {
		TRACE("skills add %d\n", i);
		bitmapnumbers.push_back(i);
		num++;
		index = 0;
	}
	
	void PAnimation::setTopLeft(int x,int y) {
		_x = x; _y = y;
	}

	void PAnimation::onMove() {
		index = (index + 1);
		if (index >= num) {
			index = 0;
		}
	}

	void PAnimation::onShow() {
		TRACE("%d\n",index);
		int n = bitmapnumbers.at(index);
		lib->showBynumber(n, _x, _y);
	}
}