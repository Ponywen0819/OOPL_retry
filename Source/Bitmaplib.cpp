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
		
		super_att[0][0].LoadBitmap(".\\Bitmaps\\temp\\super_att\\L\\0.bmp", RGB(0, 0, 0));
		super_att[1][0].LoadBitmap(".\\Bitmaps\\temp\\super_att\\R\\0.bmp", RGB(0, 0, 0));

		super_att[0][1].LoadBitmap(".\\Bitmaps\\temp\\super_att\\L\\1.bmp", RGB(0, 0, 0));
		super_att[1][1].LoadBitmap(".\\Bitmaps\\temp\\super_att\\R\\1.bmp", RGB(0, 0, 0));

		super_att[0][2].LoadBitmap(".\\Bitmaps\\temp\\super_att\\L\\2.bmp", RGB(0, 0, 0));
		super_att[1][2].LoadBitmap(".\\Bitmaps\\temp\\super_att\\R\\2.bmp", RGB(0, 0, 0));

		falling[0][ 0].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\0.bmp", RGB(0, 0, 0));
		falling[0][ 1].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\1.bmp", RGB(0, 0, 0));
		falling[0][ 2].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\2.bmp", RGB(0, 0, 0));
		falling[0][ 3].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\3.bmp", RGB(0, 0, 0));
		falling[0][ 4].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\4.bmp", RGB(0, 0, 0));
		falling[0][ 5].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\5.bmp", RGB(0, 0, 0));
		falling[0][ 6].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\6.bmp", RGB(0, 0, 0));
		falling[0][ 7].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\7.bmp", RGB(0, 0, 0));
		falling[0][ 8].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\8.bmp", RGB(0, 0, 0));
		falling[0][ 9].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\9.bmp", RGB(0, 0, 0));
		falling[0][10].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\10.bmp", RGB(0, 0, 0));
		falling[0][11].LoadBitmap(".\\Bitmaps\\temp\\fall\\L\\11.bmp", RGB(0, 0, 0));
		
		falling[1][ 0].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\0.bmp", RGB(0, 0, 0));
		falling[1][ 1].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\1.bmp", RGB(0, 0, 0));
		falling[1][ 2].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\2.bmp", RGB(0, 0, 0));
		falling[1][ 3].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\3.bmp", RGB(0, 0, 0));
		falling[1][ 4].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\4.bmp", RGB(0, 0, 0));
		falling[1][ 5].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\5.bmp", RGB(0, 0, 0));
		falling[1][ 6].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\6.bmp", RGB(0, 0, 0));
		falling[1][ 7].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\7.bmp", RGB(0, 0, 0));
		falling[1][ 8].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\8.bmp", RGB(0, 0, 0));
		falling[1][ 9].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\9.bmp", RGB(0, 0, 0));
		falling[1][10].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\10.bmp", RGB(0, 0, 0));
		falling[1][11].LoadBitmap(".\\Bitmaps\\temp\\fall\\R\\11.bmp", RGB(0, 0, 0));
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
	void Bitmaplib::showBeaten(int step,bool FaceToLeft, int index) {
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

	void Bitmaplib::setSuper_attTopLeft(int f, int index, int x, int y){
		super_att[f][index].SetTopLeft(x, y);
	}
	void Bitmaplib::showSuper_att(int f, int index) {
		super_att[f][index].ShowBitmap();
	}

	void Bitmaplib::Falling(int step, int FaceToLeft, int index, int x, int y) {
		if (step == 0) {		// 被右邊打
			falling[FaceToLeft][index].SetTopLeft(x, y);
			falling[FaceToLeft][index].ShowBitmap();
		}
		else{
			falling[FaceToLeft][index+6].SetTopLeft(x, y);
			falling[FaceToLeft][index + 6].ShowBitmap();
		}
	}
	


	PAnimation::PAnimation(Bitmaplib *l) :num{ 0 }, index{ 0 }, lib{ l }{}

	void PAnimation::addBitmap(int i) {
		//TRACE("skills add %d\n", i);
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
		//TRACE("%d\n",index);
		int n = bitmapnumbers.at(index);
		lib->showBynumber(n, _x, _y);
	}
}