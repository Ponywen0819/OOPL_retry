#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gamemap.h"
#include "templete1.h"

#define map_width 1600.0

namespace game_framework {

	void temp1::init() {
		pic[0].LoadBitmap("./Bitmaps/bg/1/pic1.bmp");
		pic[1].LoadBitmap("./Bitmaps/bg/1/pic2.bmp");
		pic[2].LoadBitmap("./Bitmaps/bg/1/pic3.bmp", RGB(0, 0, 0));
		pic[3].LoadBitmap("./Bitmaps/bg/1/pic4.bmp", RGB(0, 0, 0));
		pic[4].LoadBitmap("./Bitmaps/bg/1/pic5.bmp");
		pic[5].LoadBitmap("./Bitmaps/bg/1/pic6.bmp");
		pic[6].LoadBitmap("./Bitmaps/bg/1/pic7.bmp");
		pic[7].LoadBitmap("./Bitmaps/bg/1/pic8.bmp");
		

		

		pic[0].set(map_width, 967.0, 0, 128);
		pic[1].set(map_width, 967.0, 800, 128);
		pic[2].set(map_width, 1000.0, 0, 200);
		pic[3].set(map_width, 1000.0, 500, 200);
		pic[4].set(map_width, 1500.0, 0, 347);
		pic[5].set(map_width, 1500.0, 750, 347);
		pic[6].set(map_width, 1600.0, 0, 413);
		pic[7].set(map_width, 1600.0, 800, 413);
		

		for (int i = 0; i < 8; i++) {
			pic[i].calShow();
		}
	}

	void temp1::showmap(int man_pos) {
		for (int i = 0; i < 8; i++) {
			pic[i].onShow();
		}
	}

}
