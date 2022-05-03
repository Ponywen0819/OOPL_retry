#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gamemap.h"
#include "lion forest.h"

#define map_width 3200

namespace game_framework{
	
	void lf::init() {
		forestm[0].LoadBitmap("./Bitmaps/bg/lf/forestm1.bmp", RGB(0, 0, 0));
		forestm[1].LoadBitmap("./Bitmaps/bg/lf/forestm2.bmp", RGB(0, 0, 0));
		forestm[2].LoadBitmap("./Bitmaps/bg/lf/forestm3.bmp", RGB(0, 0, 0));
		forestm[3].LoadBitmap("./Bitmaps/bg/lf/forestm4.bmp", RGB(0, 0, 0));
		forests.LoadBitmap("./Bitmaps/bg/lf/forests.bmp");
		forestt.LoadBitmap("./Bitmaps/bg/lf/forestt.bmp", RGB(0, 0, 0));
		land[0].LoadBitmap("./Bitmaps/bg/lf/land1.bmp");
		land[1].LoadBitmap("./Bitmaps/bg/lf/land2.bmp");
		land[2].LoadBitmap("./Bitmaps/bg/lf/land3.bmp");
		land[3].LoadBitmap("./Bitmaps/bg/lf/green.bmp");

		forests.set(map_width, 800, 0, 128);
		forestm[0].set(map_width, 1100, 0, 147);
		forestm[1].set(map_width, 1100, 800, 147);
		forestm[2].set(map_width, 1400, 0, 170);
		forestm[3].set(map_width, 1400, 1216, 155);
		forestt.set(map_width, 2900, 0, 199,253);
		land[0].set(map_width, 2950, 0, 356,520);
		land[1].set(map_width, 3070, 300, 385,530);
		land[2].set(map_width, 3200, 600, 420,570);
		land[3].set(map_width, 800, 0, 356);

		forests.calShow();
		land[3].calShow();
		forestm[0].calShow();
		forestm[1].calShow();
		forestm[2].calShow();
		forestm[3].calShow();
		forestt.calShow();
		land[0].calShow();
		land[1].calShow();
		land[2].calShow();
	}

	void lf::showmap(int _man_pos) {
		forests.onShow(_man_pos);
		land[3].onShow(_man_pos);
		forestm[0].onShow(_man_pos);
		forestm[1].onShow(_man_pos);
		forestm[2].onShow(_man_pos);
		forestm[3].onShow(_man_pos);
		forestt.onShow(_man_pos);
		land[0].onShow(_man_pos);
		land[1].onShow(_man_pos);
		land[2].onShow(_man_pos);
	}

	int lf::map_pos() {
		return forests.map_pos();
	}

}
