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
#include "skills.h"
#include "Area.h"
#include "CStateBar.h"
#include "Frame.h"
#include <map>
#include "man.h"

namespace game_framework {

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


	void man::readCommand() {
	}

	void man::setInitPosotion(int x, int y) {
		_x = float(x);
		_z = float(y);
	}

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
			adjustPosition(_mode, temp);
			_mode = temp;
			setTimmer((*Frams)[_mode]._wait);
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

	void man::setPosotion(int n) {
		if (_dir[0]) _x -= n;
		if (_dir[1]) _x += n;
		if (_dir[2]) _y -= 1;
		if (_dir[3]) _y += 1;
	}

	void man::checkFlag() {
		if (inMotion) {
			this->specialEvent();
		}
		else {
			if (flag[5]) {
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
				if (_dir[0]) { JumpBack = true; JumpFront = false;}
				else if(_dir[1]){ JumpBack = false; JumpFront = true;}
				else{ JumpBack = false; JumpFront = false; }

				if (_dir[2]) { JumpUp = true; }
				else { JumpUp = false; }

				if (_dir[3]) { JumpDown = true; }
				else { JumpDown = false; }
				setYstep(-16.3, 8.0, 3.0);
				toMotion(210);
			}
			else if (flag[6]) {
				toMotion(111);
			}
		}
		
		// 處理移動
		if (flag[0]) {
			_dir[0] = true;_dir[1] = false;
		}
		else if (flag[1]) {
			_dir[0] = false;_dir[1] = true;
		}
		else {
			_dir[0] = false; _dir[1] = false;
		}

		if (flag[2]) {
			_dir[2] = true;_dir[3] = false;
		}
		else if (flag[3]) {
			_dir[2] = false;_dir[3] = true;
		}
		else {
			_dir[2] = false; _dir[3] = false;
		}

		bool button_down = true;
		for (int i = 0; i < 4; i++) {
			if (flag[i]) {
				button_down = false;
				break;
			}
		}
		if (button_down) {
			if ((*Frams)[_mode]._state == 1)
				backToRandon();
		}
		else {
			if ((*Frams)[_mode]._state == 0) {
				_mode = getNextWalkMotion();
				setTimmer(3);
			}
		}

	}

	void man::checkBuff() {
		if (inMotion) {
			return;
		}
		if (_Double_Tap_Gap <= 0) {
			_Double_Tap_Gap = 55;
			commandBuffer = "";
		}
		else{
			_Double_Tap_Gap--;
			std::string commandList[] = { "LL","RR","FRA","FRJ","FUJ","FDJ","FDA","FUJA"};
			// 檢查是否有在技能表裡面
			bool match = false;
			for (int i = 0; i < 8; i++) {
				if (SkillsMotion[i] == -1) continue;
				else if (commandBuffer == commandList[i]) {
					if ((*Frams)[_mode]._state <= 1) {
						TRACE("%d %s\n", (*Frams)[_mode]._state, commandBuffer.c_str());
						if (i == 0) {
							if (Face_to_Left) {
								toMotion(SkillsMotion[i]);
							}
						}
						else if (i == 1) {
							if (!Face_to_Left) {
								toMotion(SkillsMotion[i]);
							}
						}
						else {
							toMotion(SkillsMotion[i]);
						}
					}
					commandBuffer = "";
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
			//TRACE("%s\n", commandBuffer.c_str());
		}

	}

	void man::specialEvent() {

		int stateNow = (*Frams)[_mode]._state;
		switch (stateNow){

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
			else if (flag[5]) {
				flag[5] = false;
				int p = (*Frams)[_mode]._cp.getAaction();
				adjustPosition(_mode, p);
				_mode = p;
				Caught->_mode = (*Frams)[_mode]._cp.getVaction();
				setTimmer((*Frams)[_mode]._wait);
			}
		}
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
			if(tempf._have_itr){				// 這個東西具有攻擊性
				switch (tempf._i.getKind()) {
				case 0: {
					if (touch(tempf._i, (*(*(all + i))).Face_to_Left, (*(*(all + i)))._x, (*(*(all + i)))._y, (*(*(all + i)))._z)) {
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
					}
					break;
				}
				case 1: {
					if (touch(tempf._i, (*(*(all + i))).Face_to_Left, (*(*(all + i)))._x, (*(*(all + i)))._y, (*(*(all + i)))._z)) {
						if ((*Frams)[_mode]._state == 16 ) {
							(*(all + i))->toMotion(tempf._i.getCatching());
							(*(all + i))->Caught = this;
							this->toMotion(tempf._i.getCaught());

							Face_to_Left = !(*(all + i))->Face_to_Left;
							(*(all + i))->cc = 301;
						}
					}
					break;
				}
				case 6: {
					if (touch(tempf._i, (*(*(all + i))).Face_to_Left, (*(*(all + i)))._x, (*(*(all + i)))._y, (*(*(all + i)))._z)) {
						useSupperAtt = true;
					}
					break;
				}
				default: {
					break;
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
		
		int stateNow = (*Frams)[_mode]._state;
		// 負責位置的調整
		moveY();
		switch (stateNow) {
		// 走路狀態
		case 1: {
			if (_dir[0]) {
				Face_to_Left = true;
				_x -= 4;
			}
			if (_dir[1]) {
				Face_to_Left = false;
				_x += 4;
			}
			if (_dir[2]) {
				_z -= float(1.3);
			}
			if (_dir[3]) {
				_z += float(1.3);
			}
			break;
		}
		// 跑步狀態
		case 2: {
			if (Face_to_Left) {
				_x -= 8;
			}
			else {
				_x += 8;
			}
			if (_dir[2]) {
				_z -= 1;
			}
			if (_dir[3]) {
				_z += 1;
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
				int dvy = (*Frams)[_mode]._dvy;
				if (Face_to_Left) { _x -= dvx; }
				else { _x += dvx; }
			}
			break;
		}
		//原地跳
		case 4: {
			if (_y > 0) {
				_y = 0;backToRandon();
			}
			break;
		}
		//大跳
		case 5: {
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

		Count();
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

	void weapon::OnShow() {

	}

	void ObjContainer::init(int p1,int p2, Bitmaplib *l , Framelib* f) {
		lib = l;
		fl = f;
		if ((p1 != -1) && (p2 != -1)) {
			state = 0;
			all = new obj*[2];
			all[0] = new man(p1);
			all[1] = new man(p2);
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
			all[0] = new man(p1);
			numOfObj = 1;
			all[0]->init(l, all, numOfObj, f->getFrame(p1));

			all[0]->_x = 100;
			
			all[0]->_z = 400;
		}
		else if ((p1 == -1) && (p2 != -1)) {
			state = 2;
			all = new obj*[1];
			all[0] = new man(p2);
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
		}
	}

	void ObjContainer::OnShow() {
		for (int i = 0; i < numOfObj; i++) {
			all[i]->OnShow();
		}
	}

	void ObjContainer::creatWeapon(int n) {
		weapon* temp = new weapon;


	}

	void ObjContainer::addobj(obj* n) {

	}
}
