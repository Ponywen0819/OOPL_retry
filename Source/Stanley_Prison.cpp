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
		wall[0].LoadBitmap("./Bitmaps/bg/SP/wall.bmp");
		wall[1].LoadBitmap("./Bitmaps/bg/SP/underground.bmp");
		wall_ani.AddBitmap("./Bitmaps/bg/SP/wall2.bmp");
		wall_ani.AddBitmap("./Bitmaps/bg/SP/wall3.bmp");
		fire_ani.AddBitmap("./Bitmaps/bg/SP/fire1.bmp");
		fire_ani.AddBitmap("./Bitmaps/bg/SP/fire2.bmp");
		fire_ani.AddBitmap("./Bitmaps/bg/SP/fire3.bmp");
		fire_ani.AddBitmap("./Bitmaps/bg/SP/fire4.bmp");
		fire_ani.AddBitmap("./Bitmaps/bg/SP/fire5.bmp");
		fire_ani.AddBitmap("./Bitmaps/bg/SP/fire6.bmp");
		fire_ani.AddBitmap("./Bitmaps/bg/SP/fire7.bmp");

		wall[0].set(map_width, 2400, 0, 128, 277);
		wall[1].set(map_width, 2400, 0, 308,800);

		wall_ani.set(map_width, 2400, -57, 269, 277,1);
		fire_ani.set(map_width, 2400, 0, 128, 277,1);

		wall[0].calShow();
		wall[1].calShow();
		wall_ani.calShow();
		fire_ani.calShow();

	}

	void SP::showmap(int _man_pos) {
	
		wall[0].onShow(_man_pos);
		wall[1].onShow(_man_pos);
		wall_ani.onShow(_man_pos);
		fire_ani.onShow(_man_pos);
	}

	int SP::map_pos() {
		return wall[0].map_pos();
	}

}