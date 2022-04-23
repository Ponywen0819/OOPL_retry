#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <string>
#include <map>
#include "Frame.h"
#include "Bitmaplib.h"

namespace game_framework {

	Bitmaplib::Bitmaplib() {}

	void Bitmaplib::LoadBitmap() {
		std::string path;
		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\temp\\all\\" + std::to_string(i) + ".bmp";
			pic[0][1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\temp\\all\\" + std::to_string(140+i) + ".bmp";
			pic[0][0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
	}

	void Bitmaplib::selectByNum(int n, int index, int x, int y) {
		pic[0][index][n].SetTopLeft(x, y);
		pic[0][index][n].ShowBitmap();
	}
}