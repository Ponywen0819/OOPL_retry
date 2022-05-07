#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gamemap.h"
#include "Stanley_Prison.h"

#define map_width 2400

namespace game_framework {

	void SP::init() {
		wall.LoadBitmap("./Bitmaps/bg/SP/wall.bmp");
		wall[1].LoadBitmap("./Bitmaps/bg/SP/wall2.bmp");
		wall[2].LoadBitmap("./Bitmaps/bg/SP/wall3.bmp");
		wall[3].LoadBitmap("./Bitmaps/bg/SP/wall4.bmp");
		fire[0].LoadBitmap("./Bitmaps/bg/SP/fire1.bmp");
		fire[1].LoadBitmap("./Bitmaps/bg/SP/fire2.bmp");
		fire[2].LoadBitmap("./Bitmaps/bg/SP/fire3.bmp");
		fire[3].LoadBitmap("./Bitmaps/bg/SP/fire4.bmp");
		fire[4].LoadBitmap("./Bitmaps/bg/SP/fire5.bmp");
		fire[5].LoadBitmap("./Bitmaps/bg/SP/fire6.bmp");
		fire[6].LoadBitmap("./Bitmaps/bg/SP/fire7.bmp");


		wall.set(map_width, 2400, 0, 128, 277);
		wall[1].set(map_width, 2400, -57, 269, 277);
		//wall[2].set(map_width, 2400, -57, 269, 277);
		fire[0].set(map_width, 2400, 0, 128, 277);


		wall.calShow();
		wall[1].calShow();
		fire[0].calShow();
	}

	void SP::showmap(int _man_pos) {
		wall.onShow(_man_pos);
		wall[1].onShow(_man_pos);
		fire[0].onShow(_man_pos);
	}

	int SP::map_pos() {
		return wall.map_pos();
	}

}