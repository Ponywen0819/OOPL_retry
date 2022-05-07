#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gamemap.h"
#include "great wall.h"

#define map_width 2400

namespace game_framework {

	void GW::init() {

		sky.LoadBitmap("./Bitmaps/bg/gw/sky.bmp");
		ground.LoadBitmap("./Bitmaps/bg/gw/underground.bmp");
		hill[0].LoadBitmap("./Bitmaps/bg/gw/hill1.bmp", RGB(0, 0, 0));
		hill[1].LoadBitmap("./Bitmaps/bg/gw/hill2.bmp", RGB(0, 0, 0));
		road[0].LoadBitmap("./Bitmaps/bg/gw/road1.bmp", RGB(0, 0, 0));
		road[1].LoadBitmap("./Bitmaps/bg/gw/road2.bmp", RGB(0, 0, 0));
		road[2].LoadBitmap("./Bitmaps/bg/gw/road3.bmp", RGB(0, 0, 0));


		sky.set(map_width, 800, 0, 128);
		ground.set(map_width, 800, 0, 324);
		hill[0].set(map_width, 1204, 0, 142);
		hill[1].set(map_width, 1204, 800, 142);
		road[0].set(map_width, 2330, 0, 171);
		road[1].set(map_width, 2400, 235, 256, 93);
		road[2].set(map_width, 2600, 0, 481, 104);

		sky.calShow();
		ground.calShow();
		hill[0].calShow();
		hill[1].calShow();
		road[0].calShow();
		road[1].calShow();
		road[2].calShow();

	}

	void GW::showmap(int _man_pos){

		sky.onShow(_man_pos);
		ground.onShow(_man_pos);
		hill[0].onShow(_man_pos);
		hill[1].onShow(_man_pos);
		road[0].onShow(_man_pos);
		road[1].onShow(_man_pos);
		road[2].onShow(_man_pos);

	}

	int GW::map_pos() {
		return sky.map_pos();
	}

}
