#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "man.h"
#include "Bitmaplib.h"
#include "gamemap.h"
#include "Stage.h"
#include <time.h>
#include <string>
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

	int SP::_map_width() {
		return map_width;
	}

	int SP::_upper() {
		return upper_bound;
	}

	int SP::_lower() {
		return lower_bound;
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

	int lf::_map_width() {
		return map_width;
	}

	int lf::_upper() {
		return upper_bound;
	}

	int lf::_lower() {
		return lower_bound;
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

	int GW::_map_width() {
		return map_width;
	}

	int GW::_upper() {
		return upper_bound;
	}

	int GW::_lower() {
		return lower_bound;
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

	int temp1::_map_width() {
		return map_width;
	}

	int temp1::_upper() {
		return upper_bound;
	}

	int temp1::_lower() {
		return lower_bound;
	}


	void stage::init(int init_stage, ObjContainer* _obj,int player1,int player2) {
		obj = _obj;
		now_stage = init_stage;
		_player1 = player1;
		_player2 = player2;
		if (now_stage == 1) {
			trans_index = 1;
		}
		else if (now_stage == 2) {
			trans_index = 6;
		}
		else if (now_stage == 3) {
			trans_index = 11;
		}
		srand((unsigned int)time(NULL));
		branch = FALSE;
		main = TRUE;
		clean = FALSE;
		over = FALSE;
		audio = FALSE;
		initcheckhp = FALSE;
		initover = FALSE;
		cheatover = FALSE;
		map = 0;
		temp = 0;
		tempover = 0;
		delay();
		if (temp > 10) {
			obj->init(player1, player2);
			temp = 0;
		}
		
	}

	void stage::load() {
		sp1->init();
		lf1->init();
		gw1->init();
		ex1->init();
	
		CAudio::Instance()->Load(3, "Sounds\\stage1.wav");
		CAudio::Instance()->Load(4, "Sounds\\stage2.wav");
		CAudio::Instance()->Load(5, "Sounds\\stage3.wav");
		for (int i = 0; i < 16; i++) {
			path = "./Bitmaps/stage/"+ std::to_string(i) +"~1.bmp";
			if (i == 1 || i == 6 || i == 11) {
				trans[i].LoadBitmap((char *)path.c_str());
			}
			else {
				trans[i].LoadBitmap((char *)path.c_str(),RGB(0,0,0));
			}	
		}
	}
	//關卡換關資訊
	void stage::info() {
		data[4] = trans_index;
		if (now_stage == 1) {
			if (!audio) {
				TRACE("!!!!!\n");
				CAudio::Instance()->Stop(4);
				CAudio::Instance()->Stop(5);
				CAudio::Instance()->Play(3,true);
				audio = TRUE;
			}
			map = 1;
			data[0] = map_width = lf1->_map_width();
			data[2] = upper_bound = lf1->_upper();
			data[3] = lower_bound = lf1->_lower();

			switch (trans_index) {
			case 1:
				obj->init(_player1, _player2);
				obj->creatWeapon(10, 300, 300);
				randObj(0, 2, 0, map_width, lower_bound, upper_bound);
				randObj(1, 2, 10, map_width, lower_bound, upper_bound);
				break;
			case 2:
				randObj(0,3, 0, map_width, lower_bound, upper_bound);
				randObj(1, 2, 10, map_width, lower_bound, upper_bound);
				break;
			case 3:
				randObj(0,4, 0, map_width, lower_bound, upper_bound);
				randObj(1, 2, 10, map_width, lower_bound, upper_bound);
				break;
			case 4:
				randObj(1,2, 10, map_width, lower_bound, upper_bound);
				randObj(0,5, 0, map_width, lower_bound, upper_bound);
				break;
			case 5:
				randObj(1,2, 10, map_width, lower_bound, upper_bound);
				randObj(0,7, 0, map_width, lower_bound, upper_bound);
				break;
			}
		}
		if (now_stage == 2) {
			if (!audio) {
				CAudio::Instance()->Stop(3);
				CAudio::Instance()->Stop(5);
				CAudio::Instance()->Play(4,true);
				audio = TRUE;
			}
			map = 2;
			data[0] = map_width = sp1->_map_width();
			data[2] = upper_bound = sp1->_upper();
			data[3] = lower_bound = sp1->_lower();
			switch (trans_index) {
			case 6:
				obj->init(_player1, _player2);
				randObj(1,2, 11, map_width, lower_bound, upper_bound);
				randObj(0,2, 1, map_width, lower_bound, upper_bound);
				break;
			case 7:
				randObj(1,2, 11, map_width, lower_bound, upper_bound);
				randObj(0,3, 1, map_width, lower_bound, upper_bound);
				break;
			case 8:
				randObj(0,4, 1, map_width, lower_bound, upper_bound);
				break;
			case 9:
				randObj(0,5, 1, map_width, lower_bound, upper_bound);
				break;
			case 10:
				randObj(1,2, 11, map_width, lower_bound, upper_bound);
				randObj(0,7, 1, map_width, lower_bound, upper_bound);
				break;
			}			
		}
		if (now_stage == 3) {
			if (!audio) {
				CAudio::Instance()->Stop(3);
				CAudio::Instance()->Stop(4);
				CAudio::Instance()->Play(5,true);			
				audio = TRUE;
			}
			map = 3;
			data[0] = map_width = gw1->_map_width();
			data[2] = upper_bound = gw1->_upper();
			data[3] = lower_bound = gw1->_lower();
			switch (trans_index) {
			case 11:
				obj->init(_player1, _player2);
				randObj(1, 1, 10, map_width, lower_bound, upper_bound);
				randObj(1, 1, 11, map_width, lower_bound, upper_bound);
				randObj(0,1, 1, map_width, lower_bound, upper_bound);
				randObj(0,1, 0, map_width, lower_bound, upper_bound);
				break;
			case 12:
				randObj(0,2, 1, map_width, lower_bound, upper_bound);
				randObj(0,2, 0, map_width, lower_bound, upper_bound);
				break;
			case 13:
				randObj(1, 2, 10, map_width, lower_bound, upper_bound);
				randObj(1, 2, 11, map_width, lower_bound, upper_bound);
				randObj(0,3, 1, map_width, lower_bound, upper_bound);
				randObj(0,3, 0, map_width, lower_bound, upper_bound);
				break;
			case 14:
				randObj(1, 20, 10, map_width, lower_bound, upper_bound);
				randObj(0,4, 1, map_width, lower_bound, upper_bound);
				randObj(0,4, 0, map_width, lower_bound, upper_bound);
				break;
			case 15:
				randObj(1, 20, 11, map_width, lower_bound, upper_bound);
				randObj(0,6, 1, map_width, lower_bound, upper_bound);
				randObj(0,6, 0, map_width, lower_bound, upper_bound);
				break;
			}
		}

	}
	//檢查敵人是否全滅
	void stage::check(int enemyhp) {
	if ((!obj->enemystate()) && map != 0) {
			if ( (trans_index == 6 || trans_index == 11) && man_pos>map_width + 750) {
				if (main) {
					now_stage++;
					audio = FALSE;
					map = 0;
					main = FALSE;
				}
			}

			else if ((trans_index == 6 || trans_index == 11 || trans_index == 16) && man_pos < map_width+800) {
				clean = TRUE;
			}

			else if(trans_index != 6 && trans_index != 11){
				branch = TRUE;
			}
		}
	
	}
	//過場動畫
	void stage::show_trans() {
		if (trans_index < 16) {
			trans[trans_index].SetTopLeft(0, 140);
			trans[trans_index].ShowBitmap();
			delay();
			if (temp > 10) {
				temp = 0;
				info();
				trans_index++;
				if (cheatover) {
					obj->kill();
					CAudio::Instance()->Stop(3);
					CAudio::Instance()->Stop(4);
					CAudio::Instance()->Stop(5);
				}
			}
		}
	}
	//判斷結束
	boolean stage::overgame() {
		overdelay();
		if (tempover > 23) {
			if (!obj->end()) {
				over = TRUE;
			}	
			tempover = 0;
		}
		return over;
	}
	//作弊
	void stage::cheat() {
		obj->kill();
		now_stage = 3;
		trans_index = 15;
		show_trans();
		cheatover = TRUE;
	}
	//該關該顯示的資訊
	void stage::OnShow(int _man_pos) {
		man_pos = _man_pos;
		
		if (map == 0) {
			man_pos = 0;
			show_trans();
		}
		else if(map == 1) {
			lf1->showmap(man_pos);
			map_pos = lf1->map_pos();
			if (branch) {
				show_trans();
				branch = FALSE;
			}
			if (clean) {
				trans[0].SetTopLeft(0, 140);
				trans[0].ShowBitmap();
				clean = FALSE;
			}
		}
		else if (map == 2) {
			sp1->showmap(man_pos);
			map_pos = sp1->map_pos();
			main = TRUE;
			if (branch) {
				show_trans();
				branch = FALSE;
			}
			if (clean) {
				trans[0].SetTopLeft(0, 140);
				trans[0].ShowBitmap();
				clean = FALSE;
			}
		}
		else if (map == 3) {
			gw1->showmap(man_pos);
			map_pos = gw1->map_pos();
			main = TRUE;
			if (branch) {
				show_trans();
				branch = FALSE;
			}
			if (clean) {
				trans[0].SetTopLeft(0, 140);
				trans[0].ShowBitmap();
				clean = FALSE;
				delay();
				if (temp > 10) {
					CAudio::Instance()->Stop(5);
					over = TRUE;
					temp = 0;
				}
			}
		}
		if (man_pos <= 400) data[1] = 0;
		else if (man_pos >= (data[0] + 400)) data[1] = data[0];
		else data[1] = man_pos - 400;
	}
	//隨機生成敵人
	void stage::randObj(int chooseObj,int index,int type, int width, int lower_bound, int upper_bound) {
		if (chooseObj == 0) {
			for (int i = 0; i < index; i++) {
				randWidth = rand() % (width + 800 - 800 + 1) + 800;
				randBound = rand() % (lower_bound - upper_bound + 1) + upper_bound;
				obj->creatEnemy(type, randWidth, randBound);
			}
		}
		else if (chooseObj == 1) {
			for (int i = 0; i < index; i++) {
				randWidth = rand() % (width + 800 - 800 + 1) + 800;
				randBound = rand() % (lower_bound - upper_bound + 1) + upper_bound;
				obj->creatWeapon(type, randWidth, randBound);
			}
		}

	}
	//取得關卡資訊
	int* stage::getdata() { return data; }
	void stage::delay() {
		for (int i = 0; i < 2; i++) {
			if (--delay1 < 0) {
				temp++;
				delay1 = 10;
			}
		}
	}
	void stage::overdelay() {
		for (int i = 0; i < 2; i++) {
			if (--delay2 < 0) {
				tempover++;
				delay2 = 10;
			}
		}
	}
}