#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <fstream>
#include <string>
#include <sstream>
#include <string>
#include "Area.h"
#include "CStateBar.h"
#include "Frame.h"
#include <map>
#include "man.h"

namespace game_framework {

	//
	//------------------------------物品的部分------------------------------------------
	//

	void obj::addBeaten(obj *who) {
		numOfBeaten++;
		if (beatenList == nullptr) {
			beatenList = new obj*;
			beatenCount = new int;
			*(beatenList) = who;
			int vrest = (*Frams)[_mode]._i.getVrest();
			if (vrest == 0) { *beatenCount = 4; }
			else { *beatenCount = vrest; }
		}
		else{
			obj ** temp = new obj*[numOfBeaten];
			int * tempc = new int[numOfBeaten];
			int i;
			for (i = 0; i < numOfBeaten-1; i++) {
				(*(temp + i)) = *(beatenList + i);
				*(tempc + i) = *(beatenCount + i);
			}
			(*(temp + i)) = who;
			*beatenCount = (*Frams)[_mode]._i.getVrest();
			delete beatenList;
			beatenList = temp;
		
			int vrest = (*Frams)[_mode]._i.getVrest();
			if (vrest == 0) { *(tempc + i) = 4; }
			else { *(tempc + i) = vrest; }

			delete beatenCount;
			beatenCount = tempc;
		}
	}

	bool obj::checkBeenBeaten(obj *who) {
		if (beatenList == nullptr) return false;
		for (int i = 0; i < numOfBeaten; i++) {
			if ((*(beatenList + i)) == who) {
				return true;
			}
		}
		return false;
	}
	void obj::restList() {
		numOfBeaten = 0;
		delete beatenList;
		delete beatenCount;
		beatenList = nullptr;
		beatenCount = nullptr;
	}

	void obj::bcount() {
		int i = 0;
		while (i<numOfBeaten) {
			if (--(*(beatenCount + i))==0) {
				del(i);
			}
			i++;
		}
	}
	void obj::del(int n) {
		if (n >= numOfBeaten) return;
		if (numOfBeaten == 1) {
			restList(); return;
		}
		obj ** temp = new obj*[numOfBeaten-1];
		int * tempc = new int[numOfBeaten-1];
		int real = 0;
		for (int i = 0; i < numOfBeaten; i++) {
			if (n == i)continue;
			else{
				(*(temp + real)) = *(beatenList + real);
				*(tempc + real) = *(beatenCount + real);
				real++;
			}
		}
		delete beatenList;
		beatenList = temp;
		delete beatenCount;
		beatenCount = tempc;
		numOfBeaten--;
	}

	//
	//------------------------------武器的部分------------------------------------------
	//

	void weapon::OnShow() {

	}


	//
	//------------------------------氣功的部分------------------------------------------
	//

	void wp::adjustPosition(int f_now, int f_next) {
		if (!Face_to_Left) _x = _x + (*Frams)[f_now]._centerx - (*Frams)[f_next]._centerx;
		else _x = _x - (*Frams)[f_now]._centerx + (*Frams)[f_next]._centerx;
	}

	void wp::backToRandon() {
		inMotion = false;
		_mode = 0;
		setTimmer((*Frams)[_mode]._wait);
	}

	void wp::toMotion(int f) {
		adjustPosition(_mode, f);
		_mode = f;
		inMotion = true;
		setTimmer((*Frams)[_mode]._wait);
		if ((*Frams)[_mode]._have_opiont) {
			wp* temp = new wp;

		}
	}

	void wp::nextFrame() {
		int temp = (*Frams)[_mode]._next;
		if (temp == 1000) {
			
		}
		else if (temp == 999) {
			adjustPosition(_mode, 0);
			_mode = 0;
			setTimmer((*Frams)[_mode]._wait);
		}
		else {
			adjustPosition(_mode, temp);
			_mode = temp;
			setTimmer((*Frams)[_mode]._wait);
		}
	}

	void wp::OnShow() {
		int index;
		if (Face_to_Left) index = 0;
		else index = 1;
		lib->selectOpiont(oid, (*Frams)[_mode]._pic, index, int(_x), int(_y) + int(_z) - (*Frams)[_mode]._centery);
	}

	void wp::OnMove() {
		//if (!Alive) return;
		if (isTime()) {
			nextFrame();
		}
		if (Face_to_Left) {
			_x -= (*Frams)[_mode]._dvx;
		}
		else {
			_x += (*Frams)[_mode]._dvx;
		}
		_z += (*Frams)[_mode]._dvy;

	}

	//
	//------------------------------人物的部分------------------------------------------
	//

	// 以新的中心位置調整人物
	void man::adjustPosition(int f_now, int f_next) {
		if(!Face_to_Left) _x = _x + (*Frams)[f_now]._centerx - (*Frams)[f_next]._centerx;
		else _x = _x - (*Frams)[f_now]._centerx + (*Frams)[f_next]._centerx;
	}

	//狀態調整

	void man::backToRandon() {
		inMotion = false;
		_mode = 0;
		setTimmer((*Frams)[_mode]._wait);
	}

	void man::toMotion(int f) {
		adjustPosition(_mode,f);
		_mode = f;
		inMotion = true;
		setTimmer((*Frams)[_mode]._wait);
		if ((*Frams)[_mode]._have_opiont) {
			int i = (*Frams)[_mode]._op.getOid();
			wp* temp = new wp(i, (*Frams)[_mode]._op.getAction());
			temp->init(fl->getobjFrame(i),lib,int(_x)- (*Frams)[_mode]._op.getX(),int(_y)- (*Frams)[_mode]._op.getY(),int(_z),Face_to_Left);
			skills = temp;
		}
	}

	void man::nextFrame() {
		restList();
		int ast = (*Frams)[_mode]._i.getArest();
		if ((*Frams)[_mode]._have_itr && ast!=0) {
			arestC = ast;
		}
		int temp = (*Frams)[_mode]._next;
		if (temp == 999) {
			if ((*Frams)[_mode]._state == 7) {
				if (!flag[6]) {
					backToRandon();
				}
			}
			else if ( _y < 0) {
				adjustPosition(_mode, 212);
				toMotion(212);
			}
			else {
				adjustPosition(_mode, 0);
				backToRandon();
			}
		}
		else if(temp != 0){
			toMotion(temp);
			if ((*Frams)[_mode]._state == 9) {
				Caught->_mode = (*Frams)[_mode]._cp.getVaction();
			}
		}
		else{
			// 特殊動作
			switch ((*Frams)[_mode]._state){
			case 2: {
				if (run_Ani_dir) {
					if (++_mode == 12) {
						_mode = 10;
						run_Ani_dir = !run_Ani_dir;
					}
				}
				else {
					if (--_mode == 8) {
						_mode = 10;
						run_Ani_dir = !run_Ani_dir;
					}
				}
				setTimmer((*Frams)[_mode]._wait);
				break;
			}
			case 3: {
				
			}
			case 4: {
				setTimmer((*Frams)[_mode]._wait);
				break;
			}
			case 5: {
				setTimmer((*Frams)[_mode]._wait);
				break;
			}
			case 9: {
				if (cc <= 0) {
					backToRandon();
					Caught->toMotion(133);
				}
				break;
			}
			case 10: {
				if (_mode >= 133) {
					if (_mode == 138) {
						if (_y == 0) {
							toMotion(230);
						}
					}
					else if (_mode == 144) {
						if (_y == 0) {
							toMotion(231);
						}
					}
					else {
						adjustPosition(_mode, _mode + 1);
						_mode++;
						setTimmer((*Frams)[_mode]._wait);
					}
				}
				break;
			}
			case 12: {
				if (_mode == 185) {
					adjustPosition(_mode, 230);
					_mode = 230;
					setTimmer((*Frams)[_mode]._wait);
				}
				else if (_mode == 190) {
					if (_y == 0) {
						adjustPosition(_mode, 231);
						_mode = 231;
						setTimmer((*Frams)[_mode]._wait);
					}
				}
				else {
					adjustPosition(_mode, _mode + 1);
					_mode++;
					setTimmer((*Frams)[_mode]._wait);
				}
				break;
			}
			default: {
				break;
			}
			}
		}
	}

	//輸入處理

	void man::setComm(UINT comm) {
		flag[comm - 1] = true;

		if (comm == 1) {
			flag[1] = false;
			commandBuffer += 'L';
		}
		else if (comm == 2) {
			flag[0] = false;
			commandBuffer += 'R';
		}
		else if (comm == 3) {
			flag[3] = false;
			commandBuffer += 'U';
		}
		else if (comm == 4) {
			flag[2] = false;
			commandBuffer += 'D';
		}
		else if (comm == 5) {
			commandBuffer += 'J';
		}
        else if (comm == 6) {
			commandBuffer += 'A';
		}
		else if (comm == 7) {
			commandBuffer += 'F';
		}
		
	}

	void man::cComm(UINT comm) {
		flag[comm - 1] = false;
	}

	// 依據輸入改變狀態

	void man::checkFlag() {
		bool button_down = false;
		// 處理移動
		if (flag[0]) {
			_dir[0] = true; _dir[1] = false; button_down = true;
		}
		else if (flag[1]) {
			_dir[0] = false;_dir[1] = true; button_down = true;
		}
		else {
			_dir[0] = false; _dir[1] = false;
		}

		if (flag[2]) {
			_dir[2] = true;_dir[3] = false; button_down = true;
		}
		else if (flag[3]) {
			_dir[2] = false;_dir[3] = true; button_down = true;
		}
		else {
			_dir[2] = false; _dir[3] = false;
		}

		if (inMotion) {
			this->specialEvent();
		}
		else {
			if (button_down) {
				toMotion(getNextWalkMotion());
			}
			else if (flag[5]) {
				flag[5] = false;
				if (useSupperAtt) {
					toMotion(70);
				}
				else {
					if (first_att_animation)
						toMotion(60);
					else {
						toMotion(65);
					}
					first_att_animation = !first_att_animation;
				}
			}
			else if (flag[4]) {
				flag[4] = false;
				if (_dir[0]) { JumpBack = true; JumpFront = false; }
				else if (_dir[1]) { JumpBack = false; JumpFront = true; }
				else { JumpBack = false; JumpFront = false; }

				if (_dir[2]) { JumpUp = true; }
				else { JumpUp = false; }

				if (_dir[3]) { JumpDown = true; }
				else { JumpDown = false; }
				setYstep(jump_height, jump_distance, jump_distance_z);
				toMotion(210);
			}
			else if (flag[6]) {
				toMotion(111);
			}
		}
	}

	void man::checkBuff() {
		/*if (inMotion) {
			return;
		}*/
		if (_Double_Tap_Gap <= 0) {
			_Double_Tap_Gap = 55;
			commandBuffer = "";
		}
		else{
			_Double_Tap_Gap--;
			std::string commandList[] = { "LL","RR","FRA","FRJ","FUJ","FDJ","FDA","FUJA"};
			//TRACE("%s\n",commandBuffer.c_str());
			// 檢查是否有在技能表裡面
			bool match = false;
			for (int i = 0; i < 8; i++) {
				//TRACE("%d\n", SkillsMotion[i]);
				if (SkillsMotion[i] == -1) continue;
				else if (commandBuffer == commandList[i]) {
					//TRACE("matched\n");
					int temp_state = (*Frams)[_mode]._state;
					if (( temp_state <= 1) || (temp_state==7)) {
						//TRACE("%d %s\n", (*Frams)[_mode]._state, commandBuffer.c_str());
						if (i == 0) {
							if (Face_to_Left) {
								toMotion(SkillsMotion[0]);
							}
						}
						else if (i == 1) {
							if (!Face_to_Left) {
								toMotion(SkillsMotion[1]);
							}
						}
						else {
							toMotion(SkillsMotion[i]);
						}
						commandBuffer = "";
					}
				}
				else {
					int len = commandBuffer.size();
					if (commandList[i].substr(0, len) == commandBuffer) {
						match = true;
					}
				}
			}

			// 如果沒有在技能列表裡面就重置
			if (!match) {
				commandBuffer = "";
			}
		}

	}

	void man::specialEvent() {

		int stateNow = (*Frams)[_mode]._state;
		int ha = (*Frams)[_mode].hit_a;
		if ( ha != 0) {
			if (flag[5]) {
				toMotion(ha);
			}
		}
		int hd = (*Frams)[_mode].hit_d;
		if (hd != 0) {
			if (flag[6]) {
				toMotion(hd);
			}
		}
		int hj = (*Frams)[_mode].hit_j;
		if ((*Frams)[_mode].hit_j != 0) {
			if (flag[4]) {
				toMotion(hj);
			}
		}
		// TRACE("%d %d %d %d\n", ha, hd, hj, _mode);
		switch (stateNow){
		case 1: {
			if (flag[6]) {
				toMotion(102);
			}
			break;
		}
		case 2: {
			if (flag[0] && !Face_to_Left) {
				toMotion(218);
			}
			else if (flag[1] && Face_to_Left) {
				toMotion(218);
			}
			else if (flag[4]) {
				if (Face_to_Left) { JumpBack = true; JumpFront = false; }
				else {  JumpBack = false; JumpFront = true;}
				if (_dir[2]) { JumpUp = true; }
				else { JumpUp = false; }
				if (_dir[3]) { JumpDown = true; }
				else { JumpDown = false; }
				setYstep(-11, 15, 3.75);
				toMotion(213);
			}
			else if (flag[5]) {
				toMotion(85);
			}
			break;
		}
		case 4: {
			if (flag[0]) Face_to_Left = true;
			if (flag[1])Face_to_Left = false;

			if (flag[5]) {
				toMotion(80);
			}
			break;
		}
		case 5: {
			if (JumpFront) {
				if (flag[0]) {
					if (!Face_to_Left)_mode = 213; Face_to_Left = true;
				}
				if(flag[1]) {
					if (Face_to_Left)_mode = 214; Face_to_Left = false;
				}
			}
			else {
				if (flag[0]) {
					if (!Face_to_Left)_mode = 214; Face_to_Left = true;
				}
				if (flag[1]) {
					if (Face_to_Left)_mode = 213; Face_to_Left = false;
				}
			}
			if (flag[5]) {
				toMotion(90);
			}
			break;
		}
		case 9: {
			if (flag[0]) {
				if (!Face_to_Left) {
					backToRandon();
					Caught->_mode = 133;
				}
			}
			else if (flag[1]) {
				if (Face_to_Left) {
					backToRandon();
					Caught->_mode = 133;
				}
			}
			else if (flag[5] && _mode ==121) {
				flag[5] = false;
				int p = (*Frams)[_mode]._cp.getAaction();
				adjustPosition(_mode, p);
				_mode = p;
				Caught->_mode = (*Frams)[_mode]._cp.getVaction();
				setTimmer((*Frams)[_mode]._wait);
			}
		}
		//溫紹傑是白癡
		default:
			break;
		}
	}

	void man::checkbeenatt() {
		for (int i = 0; i < numOfObj; i++) {
			if ((*(all + i)) == this) {
				continue;
			}
			int mode = (*(*(all + i)))._mode;
			Frame tempf = (*((*(all + i))->Frams))[mode];
			if ((*(all + i))->arestC > 0) {
				continue;
			}
			bool t = touch((*(all + i)));
			if(tempf._have_itr && t){				// 這個東西具有攻擊性並且有碰到
				switch (tempf._i.getKind()) {
				case 0: {
					if (!((*(all + i))->checkBeenBeaten(this))) {
						int fa = tempf._i.getFall();

						if (fa == 0) { fall -= 18; }
						else { fall -= fa; }

						if (fall < 35) {			// 擊飛
							if ((*(*(all + i))).Face_to_Left != this->Face_to_Left) {
								toMotion(180);
							}
							else {
								toMotion(186);
							}
							time = (*Frams)[_mode]._wait;
							fall = 100;
						}
						else if (fall < 55) {		// 暈眩
							toMotion(226);
						}
						else if (fall < 60) {		// 被打到第二下
							if ((*(*(all + i))).Face_to_Left != this->Face_to_Left) {
								toMotion(222);
							}
							else {
								toMotion(224);
							}
						}
						else {						// 被打到第一下
							toMotion(220);
						}


						if ((*(*(all + i))).Face_to_Left) {
							_x -= tempf._i.getDvx();
						}
						else {
							_x += tempf._i.getDvx();
						}

						(*(all + i))->addBeaten(this);
					}
					break;
				}
				case 1: {
					if ((*Frams)[_mode]._state == 16) {
						(*(all + i))->toMotion(tempf._i.getCatching());
						(*(all + i))->Caught = this;
						this->toMotion(tempf._i.getCaught());

						Face_to_Left = !(*(all + i))->Face_to_Left;
						(*(all + i))->cc = 301;
					}
					break;
				}
				case 6: {
					useSupperAtt = true;
					break;
				}
				default: {
					break;
				}
				}
			}
		}
	}

	void man::checkbeenatt(obj ** a,int n) {
		for (int i = 0; i < n; i++) {
			if ((*(a + i)) == this) {
				continue;
			}
			int mode = (*(*(a + i)))._mode;
			Frame tempf = (*((*(a + i))->Frams))[mode];
			if ((*(a + i))->arestC > 0) {
				continue;
			}
			if (tempf._have_itr) {				// 這個東西具有攻擊性
				bool t = touch(tempf._i, (*(*(a + i))).Face_to_Left, (*(*(a + i)))._x, (*(*(a + i)))._y, (*(*(a + i)))._z);
				if (t) {
					switch (tempf._i.getKind()) {
					case 0: {
						if (!((*(a + i))->checkBeenBeaten(this))) {
							int fa = tempf._i.getFall();
							if (fa == 0) { fall -= 18; }
							else { fall -= fa; }
							if (fall < 35) {			// 擊飛
								if ((*(*(a + i))).Face_to_Left != this->Face_to_Left) {
									toMotion(180);
								}
								else {
									toMotion(186);
								}
								time = (*Frams)[_mode]._wait;
								fall = 100;
							}
							else if (fall < 55) {		// 暈眩
								toMotion(226);
							}
							else if (fall < 60) {		// 被打到第二下
								if ((*(*(a + i))).Face_to_Left != this->Face_to_Left) {
									toMotion(222);
								}
								else {
									toMotion(224);
								}
							}
							else {						// 被打到第一下
								toMotion(220);
							}
							if ((*(*(a + i))).Face_to_Left) {
								_x -= tempf._i.getDvx();
							}
							else {
								_x += tempf._i.getDvx();
							}

							(*(a + i))->addBeaten(this);
						}
						break;
					}
					case 1: {
						if ((*Frams)[_mode]._state == 16) {
							(*(a + i))->toMotion(tempf._i.getCatching());
							(*(a + i))->Caught = this;
							this->toMotion(tempf._i.getCaught());

							Face_to_Left = !(*(all + i))->Face_to_Left;
							(*(a + i))->cc = 301;
						}
						break;
					}
					case 6: {
						useSupperAtt = true;
						break;
					}
					default: {
						break;
					}
					}
				}
			}
		}
	}
		//人物狀態更新
	void man::OnMove() {
		//負責動作的變更
		if (isTime()) {
			nextFrame();
		}
		Count();

		int stateNow = (*Frams)[_mode]._state;
		// 負責位置的調整
		//moveY();
		switch (stateNow) {
		// 走路狀態
		case 1: {
			if (_dir[0]) {
				Face_to_Left = true;
				_x -= wlaking_speed;
			}
			if (_dir[1]) {
				Face_to_Left = false;
				_x += wlaking_speed;
			}
			if (_dir[2]) {
				_z -= wlaking_speed_z;
			}
			if (_dir[3]) {
				_z += wlaking_speed_z;
			}
			break;
		}
		// 跑步狀態
		case 2: {
			if (Face_to_Left) {
				_x -= running_speed;
			}
			else {
				_x += running_speed;
			}
			if (_dir[2]) {
				_z -= running_speed_z;
			}
			if (_dir[3]) {
				_z += running_speed_z;
			}
			break;
		}
		// 普通拳腳攻擊
		case 3: {
			if (_y > 0) {
				_y = 0;
				backToRandon();
			}
			else{
				int dvx = (*Frams)[_mode]._dvx;
				if (Face_to_Left) { _x -= dvx; }
				else { _x += dvx; }
			}
			break;
		}
		//原地跳
		case 4: {
			moveY();
			if (_y > 0) {
				_y = 0;backToRandon();
			}
			break;
		}
		//大跳
		case 5: {
			moveY();
			if (_y > 0) {
				_y = 0;backToRandon();
			}
			break;
		}
		// 抓人與被抓
		case 9: {
			if (Face_to_Left) {
				Caught->_x = this->_x + 79 - (*Frams)[_mode]._cp.getX() - (*(Caught->Frams))[Caught->_mode]._cp.getX();
			}
			else {
				Caught->_x = this->_x +(*Frams)[_mode]._cp.getX() + (*(Caught->Frams))[Caught->_mode]._cp.getX() -79;
			}

			cc += (*Frams)[_mode]._cp.getDecrese();
			break;
		}
		case 10: {
			break;
		}
		default: {
			if (_y > 0) {
				_y = 0;
				backToRandon();
			}
			if (Face_to_Left)
				_x -= (*Frams)[_mode]._dvx;
			else
				_x += (*Frams)[_mode]._dvx;
			_z += (*Frams)[_mode]._dvy;

			break;
		}
		}
		
		useSupperAtt = false;
		bcount();
		checkbeenatt();
		checkFlag();
		checkBuff();

	}
	
		//人物顯示
	void man::OnShow() {
		int index;
		if (Face_to_Left) index = 0;
		else index = 1;
		lib->selectByNum(charector,(*Frams)[_mode]._pic, index, int(_x), int(_y) + int(_z) - (*Frams)[_mode]._centery);
		//TRACE("%d\n", (*Frams)[_mode]._pic);
	}

		//處理指令輸入時間間隔
	void man::setCountDwon() {
		_Double_Tap_Gap = 75;
	}

	void man::resetCountDown() {
		_Double_Tap_Gap = -1;
	}

	//
	//------------------------------主控的部分------------------------------------------
	//

	void ObjContainer::init(int p1,int p2, Bitmaplib *l , Framelib* f) {
		lib = l;
		fl = f;
		if ((p1 != -1) && (p2 != -1)) {
			state = 0;
			all = new obj*[2];
			man* temp1 = new man(p1);
			man* temp2 = new man(p2);
			temp1->getFl(f); temp2->getFl(f);
			all[0] = temp1;
			all[1] = temp2;
			numOfObj = 2;
			all[0]->init(l, all, numOfObj, f->getFrame(p1));
			all[1]->init(l, all, numOfObj, f->getFrame(p2));

			all[0]->_x = 100;
			all[1]->_x = 100;

			all[0]->_z = 400;
			all[1]->_z = 500;
		}
		else if ((p1 != -1) && (p2 == -1)) {
			state = 1;
			all = new obj*[1];
			man* temp1 = new man(p1);
			temp1->getFl(f);
			all[0] = temp1;
			numOfObj = 1;
			all[0]->init(l, all, numOfObj, f->getFrame(p1));

			all[0]->_x = 100;
			
			all[0]->_z = 400;
		}
		else if ((p1 == -1) && (p2 != -1)) {
			state = 2;
			all = new obj*[1];
			man* temp1 = new man(p1);
			temp1->getFl(f);
			all[0] = temp1;
			numOfObj = 1;
			all[0]->init(l, all, numOfObj, f->getFrame(p2));
			
			all[0]->_x = 100;
			
			all[0]->_z = 400;
		}
	}
	
	void ObjContainer::KeyDown(UINT nChar){
		//TRACE("%d\n", nChar);
		const char KEY_A = 65;
		const char KEY_W = 87;
		const char KEY_S = 83;
		const char KEY_D = 68;
		const char KEY_X = 88;
		const char KEY_dot = 96;
		const char KEY_TAB = 9;


		if (state == 0) {
			switch (nChar){
			case KEY_A: {
				all[0]->setComm(1);
				break;
			}
			case KEY_D: {
				all[0]->setComm(2);
				break;
			}
			case KEY_W: {
				all[0]->setComm(3);
				break;
			}
			case KEY_X:{
				all[0]->setComm(4);
				break;
			}
			case KEY_TAB: {
				all[0]->setComm(5);
				break;
			}
			case KEY_S: {
				all[0]->setComm(6);
				break;
			}
			case 192: {
				all[0]->setComm(7);
				break;
			}
			case 74: {
				all[1]->setComm(1);
				break;
			}
			case 76: {
				all[1]->setComm(2);
				break;
			}
			case 73: {
				all[1]->setComm(3);
				break;
			}
			case 188: {
				all[1]->setComm(4);
				break;
			}
			case  75: {
				all[1]->setComm(5);
				break;
			}
			case 32: {
				all[1]->setComm(6);
				break;
			}
			case 190: {
				all[1]->setComm(7);
				break;
			}
			default:
				break;
			}

		}
		else if (state == 1) {
			switch (nChar) {
			case KEY_A: {
				all[0]->setComm(1);
				break;
			}
			case KEY_D: {
				all[0]->setComm(2);
				break;
			}
			case KEY_W: {
				all[0]->setComm(3);
				break;
			}
			case KEY_X: {
				all[0]->setComm(4);
				break;
			}
			case KEY_TAB: {
				all[0]->setComm(5);
				break;
			}
			case KEY_S: {
				all[0]->setComm(6);
				break;
			}
			case 192: {
				all[0]->setComm(7);
				break;
			}
			default:
				break;
			}
		}
		else {
			switch (nChar) {
			case 74: {
				all[0]->setComm(1);
				break;
			}
			case 76: {
				all[0]->setComm(2);
				break;
			}
			case 73: {
				all[0]->setComm(3);
				break;
			}
			case 188: {
				all[0]->setComm(4);
				break;
			}
			case  75: {
				all[0]->setComm(5);
				break;
			}
			case 32: {
				all[0]->setComm(6);
				break;
			}
			case 190: {
				all[0]->setComm(7);
				break;
			}
			default: {
				
			}
			}
		}
	}
	void ObjContainer::KeyUp(UINT nChar){
		const char KEY_A = 65;
		const char KEY_W = 87;
		const char KEY_S = 83;
		const char KEY_D = 68;
		const char KEY_X = 88;
		const char KEY_dot = 96;
		const char KEY_TAB = 9;


		if (state == 0) {
			switch (nChar) {
			case KEY_A: {
				all[0]->cComm(1);
				break;
			}
			case KEY_D: {
				all[0]->cComm(2);
				break;
			}
			case KEY_W: {
				all[0]->cComm(3);
				break;
			}
			case KEY_X: {
				all[0]->cComm(4);
				break;
			}
			case KEY_TAB: {
				all[0]->cComm(5);
				break;
			}
			case KEY_S: {
				all[0]->cComm(6);
				break;
			}
			case 192: {
				all[0]->cComm(7);
				break;
			}
			case 74: {
				all[1]->cComm(1);
				break;
			}
			case 76: {
				all[1]->cComm(2);
				break;
			}
			case 73: {
				all[1]->cComm(3);
				break;
			}
			case 188: {
				all[1]->cComm(4);
				break;
			}
			case  75: {
				all[1]->cComm(5);
				break;
			}
			case 32: {
				all[1]->cComm(6);
				break;
			}
			case 190: {
				all[1]->cComm(7);
				break;
			}
			default:
				break;
			}

		}
		else if (state == 1) {
			switch (nChar) {
			case KEY_A: {
				all[0]->cComm(1);
				break;
			}
			case KEY_D: {
				all[0]->cComm(2);
				break;
			}
			case KEY_W: {
				all[0]->cComm(3);
				break;
			}
			case KEY_X: {
				all[0]->cComm(4);
				break;
			}
			case KEY_TAB: {
				all[0]->cComm(5);
				break;
			}
			case KEY_S: {
				all[0]->cComm(6);
				break;
			}
			case 192: {
				all[0]->cComm(7);
				break;
			}
			default:
				break;
			}
		}
		else {
			switch (nChar) {
			case 74: {
				all[0]->cComm(1);
				break;
			}
			case 76: {
				all[0]->cComm(2);
				break;
			}
			case 73: {
				all[0]->cComm(3);
				break;
			}
			case 188: {
				all[0]->cComm(4);
				break;
			}
			case  75: {
				all[0]->cComm(5);
				break;
			}
			case 32: {
				all[0]->cComm(6);
				break;
			}
			case 190: {
				all[0]->cComm(7);
				break;
			}
			default: {

			}
			}
		}
	}

	void ObjContainer::OnMove() {
		for (int i = 0; i < numOfObj; i++) {
			all[i]->OnMove();
			obj* temp = all[i]->usingSkills();
			if (temp != nullptr) {
				addobj(temp);
			}
			all[i]->updateObj(all,numOfObj);
		}
	}

	void ObjContainer::OnShow() {
		//TRACE("%d\n", numOfObj);
		for (int i = 0; i < numOfObj; i++) {
			all[i]->OnShow();
		}
	}

	void ObjContainer::creatWeapon(int n) {
		weapon* temp = new weapon;


	}

	void ObjContainer::addobj(obj* n) {
		obj** temp = new obj*[numOfObj + 1];
		int i;
		for (i = 0; i < numOfObj; i++) {
			*(temp + i) = *(all + i);
		}
		*(temp + i) = n;
		numOfObj++;

		delete all;
		all = temp;
	}
}
