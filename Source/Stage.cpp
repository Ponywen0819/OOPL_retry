#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "gamemap.h"
#include "Stage.h"

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

		wall[0].set(2400, 2400, 0, 128, 277);
		wall[1].set(2400, 2400, 0, 308, 800);

		wall_ani.set(2400, 2400, -57, 269, 277, 1);
		fire_ani.set(2400, 2400, 0, 128, 277, 1);

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

		forests.set(3200, 800, 0, 128);
		forestm[0].set(3200, 1100, 0, 147);
		forestm[1].set(3200, 1100, 800, 147);
		forestm[2].set(3200, 1400, 0, 170);
		forestm[3].set(3200, 1400, 1216, 155);
		forestt.set(3200, 2900, 0, 199, 253);
		land[0].set(3200, 2950, 0, 356, 520);
		land[1].set(3200, 3070, 300, 385, 530);
		land[2].set(3200, 3200, 600, 420, 570);
		land[3].set(3200, 800, 0, 356);

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


	void GW::init() {

		sky.LoadBitmap("./Bitmaps/bg/gw/sky.bmp");
		ground.LoadBitmap("./Bitmaps/bg/gw/underground.bmp");
		hill[0].LoadBitmap("./Bitmaps/bg/gw/hill1.bmp", RGB(0, 0, 0));
		hill[1].LoadBitmap("./Bitmaps/bg/gw/hill2.bmp", RGB(0, 0, 0));
		road[0].LoadBitmap("./Bitmaps/bg/gw/road1.bmp", RGB(0, 0, 0));
		road[1].LoadBitmap("./Bitmaps/bg/gw/road2.bmp", RGB(0, 0, 0));
		road[2].LoadBitmap("./Bitmaps/bg/gw/road3.bmp", RGB(0, 0, 0));


		sky.set(2400, 800, 0, 128);
		ground.set(2400, 800, 0, 324);
		hill[0].set(2400, 1204, 0, 142);
		hill[1].set(2400, 1204, 800, 142);
		road[0].set(2400, 2330, 0, 171);
		road[1].set(2400, 2400, 235, 256, 93);
		road[2].set(2400, 2600, 0, 481, 104);

		sky.calShow();
		ground.calShow();
		hill[0].calShow();
		hill[1].calShow();
		road[0].calShow();
		road[1].calShow();
		road[2].calShow();

	}

	void GW::showmap(int _man_pos) {

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

	void temp1::init() {
		pic[0].LoadBitmap("./Bitmaps/bg/1/pic1.bmp");
		pic[1].LoadBitmap("./Bitmaps/bg/1/pic2.bmp");
		pic[2].LoadBitmap("./Bitmaps/bg/1/pic3.bmp", RGB(0, 0, 0));
		pic[3].LoadBitmap("./Bitmaps/bg/1/pic4.bmp", RGB(0, 0, 0));
		pic[4].LoadBitmap("./Bitmaps/bg/1/pic5.bmp");
		pic[5].LoadBitmap("./Bitmaps/bg/1/pic6.bmp");
		pic[6].LoadBitmap("./Bitmaps/bg/1/pic7.bmp");
		pic[7].LoadBitmap("./Bitmaps/bg/1/pic8.bmp");




		pic[0].set(1600.0, 967.0, 0, 128);
		pic[1].set(1600.0, 967.0, 800, 128);
		pic[2].set(1600.0, 1000.0, 0, 200);
		pic[3].set(1600.0, 1000.0, 500, 200);
		pic[4].set(1600.0, 1500.0, 0, 347);
		pic[5].set(1600.0, 1500.0, 750, 347);
		pic[6].set(1600.0, 1600.0, 0, 413);
		pic[7].set(1600.0, 1600.0, 800, 413);


		for (int i = 0; i < 8; i++) {
			pic[i].calShow();
		}
	}

	void temp1::showmap(int _man_pos) {
		for (int i = 0; i < 8; i++) {
			pic[i].onShow(_man_pos);
		}
	}

	int temp1::map_pos() {
		return pic[0].map_pos();
	}





	void stage::init() {
		sp1->init();
		lf1->init();
		gw1->init();
		ex1->init();
	}

	void stage::OnShow(int _man_pos) {

		if (map == 0) {

		}
		else if(map == 1) {
			lf1->showmap(_man_pos);
		}
		else if (map == 2) {
			sp1->showmap(_man_pos);
		}
		else if (map == 3) {
			gw1->showmap(_man_pos);
		}

	}




}