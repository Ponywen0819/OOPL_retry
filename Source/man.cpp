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
#include <algorithm>
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

	void obj::setArest(int n) {
		arestC = n;
	}
	int	 obj::getArest() {
		return arestC;
	}

	//
	//------------------------------武器的部分------------------------------------------
	//

	void weapon::backToRandon() {
		inMotion = false;
		_mode = 0;
		setTimmer((*Frams)[_mode]._wait);
	}

	void weapon::toMotion(int f) {
		adjustPosition(_mode, f);
		_mode = f;
		inMotion = true;
		setTimmer((*Frams)[_mode]._wait);
	}

	void weapon::nextFrame() {
		int temp = (*Frams)[_mode]._next;
		//TRACE("%d %d\n",temp,_mode);
		if (temp == 999) {
			toMotion(0);
		}
		else if (temp ==0) {
			if ((*Frams)[_mode]._state != 1004) {

			}
		}
		else {
			toMotion(temp);
		}
	}

	void weapon::OnShow() {
		int index;
		if (Face_to_Left) index = 0;
		else index = 1;
		//TRACE("%d %d %d\n", (*Frams)[_mode]._pic,_mode,id);
		lib->selectByNum(id, (*Frams)[_mode]._pic, index, int(_x), -int(_y) + int(_z));
	}

	void weapon::OnMove() {
		if (holding == nullptr) {
			moveY();
			if (isTime()) {
				nextFrame();
			}
			int state = (*Frams)[_mode]._state;
			switch (state){
			case 1000: {
				if (_y <= maxH) {
					toMotion(70);
				}
				break;
			}
			case 1003: {

				break;
			}
			case 1004: {

				break;
			}
			default:
				break;
			}

			checkbeenatt();
		}
		else{
			
		}
		Count();
	}

	void weapon::checkbeenatt() {
		Frame myF = (*Frams)[_mode];
		for (int i = 0; i < _a->getN(); i++) {
			obj* temp_obj = _a->getobj(i);
			if (temp_obj == this || holding == temp_obj) {
				continue;
			}
			int mode = temp_obj->_mode;
			Frame tempf = (*(temp_obj->Frams))[mode];
			bool t = touch(temp_obj);
			//TRACE("fuck %d \n",t);
			if (tempf._have_itr && t) {				// 這個東西具有攻擊性並且有碰到
				switch (tempf._i.getKind()) {
				case 2: {
					holding = temp_obj;
					temp_obj->toMotion(219);
					temp_obj->holdingSth(this);
					temp_obj->holdinglt = true;
					break;
				}
				default: {
					break;
				}
				}
				temp_obj->setArest(tempf._i.getArest());
			}
		}
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
			int i = (*Frams)[_mode]._op.getOid();
			wp* temp = new wp(i, (*Frams)[_mode]._op.getAction(),fl,lib,getOwner());
			bool ftl;
			if ((*Frams)[_mode]._op.getFacing() == 1) ftl = !Face_to_Left;
			else ftl = Face_to_Left;

			Frame tempF = (*Frams)[_mode];
			if (Face_to_Left) {
				temp->init(int(_x) + maxW - tempF._op.getX(), int(_y) - tempF._op.getY(), int(_z), ftl);
			}
			else {
				temp->init(int(_x) + tempF._op.getX(), int(_y) - tempF._op.getY(), int(_z), ftl);
			}
			temp->setmax(3200, 500);
			skills = temp;
		}
	}

	void wp::nextFrame() {
		int temp = (*Frams)[_mode]._next;
		//TRACE("%d %d\n",temp,_mode);
		if (temp == 1000) {
			Alive = false;
		}
		else if (temp == 999) {
			toMotion(0);
		}
		else {
			toMotion(temp);
		}
	}

	void wp::hitSomeOne(obj* other) {
		switch (id) {
		case 203:
		case 209:
		case 210:
			toMotion(10);
			break;
		default: {
			break;
		}
		}
		who = other;
		stop = true;
		
	}

	void wp::OnShow() {
		int index;
		if (Face_to_Left) index = 0;
		else index = 1;
		//TRACE("%d %d %d\n", (*Frams)[_mode]._pic,_mode,id);
		lib->selectByNum( id, (*Frams)[_mode]._pic, index, int(_x), -int(_y)+int(_z));
	}

	void wp::OnMove() {
		
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
		hp -= (*Frams)[_mode].hit_a;
		if (hp <= 0 && (*Frams)[_mode].hit_d != 0) {
			hp = 500;
			toMotion((*Frams)[_mode].hit_d);
		}

		if (_x > maxx || _x<0) {
			Alive = false;
		}

		Count();
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
		if (cantBrTouchCount == 0) {
			cantBeTouch = false;
		}
	}

	void man::toMotion(int f) {
		adjustPosition(_mode,f);
		_mode = f;
		inMotion = true;
		Frame tempF = (*Frams)[_mode];
		setTimmer(tempF._wait);
		if (tempF._have_opiont) {
			wp* temp = new wp(tempF._op.getOid(), tempF._op.getAction(), fl, lib,getOwner());
			bool ftl;
			if (tempF._op.getFacing() == 1) ftl = !Face_to_Left;
			else ftl = Face_to_Left;
			
			if (Face_to_Left) {
				//TRACE("%d \n", maxW - tempF._op.getX());
				temp->init(int(_x) + maxW - tempF._op.getX(), int(_y) - tempF._op.getY(), int(_z), ftl);
			}
			else {
				//TRACE("%d \n", tempF._op.getX());
				temp->init(int(_x) + tempF._op.getX(), int(_y) - tempF._op.getY(), int(_z), ftl);
			}
			temp->setmax(3200, 500);
			skills = temp;
		}
	}

	void man::nextFrame() {
		hit = false;
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
			else if ( _y > maxH) {
				adjustPosition(_mode, 212);
				toMotion(212);
			}
			else {
				adjustPosition(_mode, 0);
				backToRandon();
			}
		}
		else if(temp != 0){
			if ((*Frams)[_mode]._state == 14) {
				cantBeTouch = true;
				cantBrTouchCount = 20;
			}
			toMotion(temp);
			if ((*Frams)[_mode]._state == 9) {
				Caught->_mode = (*Frams)[_mode]._cp.getVaction();
			}
		}
		else{
			//TRACE("right %d\n", (*Frams)[_mode]._state);
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
						if (_y == maxH) {
							toMotion(230);
						}
					}
					else if (_mode == 144) {
						if (_y == maxH) {
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
					if (int(_y) <= maxH) {
						_y = maxH;
						toMotion(230);
					}
				}
				else if (_mode == 190) {
					if (int(_y) <= maxH) {
						_y = maxH;
						toMotion(191);
					}
				}
				else if (_mode == 191) {
					toMotion(231);
				}
				else {
					toMotion(_mode + 1);
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
					if (first_att_animation) {
						if (holdinglt) {
							toMotion(20);
						}
						else {
							toMotion(60);
						}
					}
					else {
						if (holdinglt) {
							toMotion(25);
						}
						else {
							toMotion(65);
						}
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
		if (hj != 0) {
			if (flag[4]) {
				toMotion(hj);
			}
		}
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
		Frame myF = (*Frams)[_mode];
		if (cantBeTouch) return;
		for (int i = 0; i < _a->getN(); i++) {
			obj* temp_obj = _a->getobj(i);
			if (temp_obj == this || temp_obj == holding) {
				continue;
			}
			int mode = temp_obj->_mode;
			Frame tempf = (*(temp_obj->Frams))[mode];
			if (temp_obj->getArest() > 0) {
				continue;
			}
			bool t = touch(temp_obj);
			if(tempf._have_itr && t){				// 這個東西具有攻擊性並且有碰到
				if (myF._state == 12 && tempf._i.getFall() < 60) {
					continue;
				}
				switch (tempf._i.getKind()) {
				case 0: {
					if (!(temp_obj->checkBeenBeaten(this))) {
						int fa = tempf._i.getFall();

						if (fa == 0) { fall -= 18; }
						else { fall -= fa; }

						if (fall < 35) {			// 擊飛
							if (temp_obj->Face_to_Left != this->Face_to_Left) {
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
							if (temp_obj->Face_to_Left != this->Face_to_Left) {
								toMotion(222);
							}
							else {
								toMotion(224);
							}
						}
						else {						// 被打到第一下
							toMotion(220);
						}


						setYstep(tempf._i.getDvy(), tempf._i.getDvx(), 0);
						if (temp_obj->Face_to_Left) {
							JumpFront = false; JumpBack = true;
						}
						else {
							JumpFront = true; JumpBack = false;
						}

						switch (tempf._i.get_effect()) {
						case 2:
							toMotion(203);
							break;
						case 3:
							toMotion(200);
							break;
						case 20:
							cantBeTouch = true;
							toMotion(203);
							break;
						case 30:
							cantBeTouch = true;
							toMotion(200);
							break;

						default:
							break;
						}
						temp_obj->addBeaten(this);
						temp_obj->hitSomeOne(this);
						hit = true;
					}

					break;
				}
				case 1: {
					if ((*Frams)[_mode]._state == 16) {
						temp_obj->toMotion(tempf._i.getCatching());
						temp_obj->Caught = this;
						this->toMotion(tempf._i.getCaught());

						Face_to_Left = !temp_obj->Face_to_Left;
						temp_obj->cc = 301;
					}
					break;
				}
				case 5: {
					int dvx;
					Frame weapont = (*(temp_obj->getOwner()->Frams))[temp_obj->getOwner()->_mode];
					int att = weapont._wp.getattcking();
					switch (att){
					case 0: {
						return;
						break;
					}
					case 1: {
						if (temp_obj->id == 10) {
							dvx = 2;
							this->fall -= 40.0;
						}
						else if (temp_obj->id == 11) {
							dvx = 2;
						}
						else {
							dvx = 2;
						}
						break;
					}
					case 2: {
						if (temp_obj->id == 10) {
							dvx = 7;
							fall -= 70;
						}
						else if (temp_obj->id == 11) {

						}
						else {

						}
						break;
					}
					case 3: {
						if (temp_obj->id == 10) {
							dvx = 10;
							fall -= 70;
						}
						else if (temp_obj->id == 11) {

						}
						else {

						}
						break;
					}
					case 4: {
						if (temp_obj->id == 10) {
							dvx = 12;
							fall -= 70;
						}
						else if (temp_obj->id == 11) {

						}
						else {

						}
						break;
					}
					default:
						break;
					}
					if (fall < 35) {			// 擊飛
						if (temp_obj->Face_to_Left != this->Face_to_Left) {
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
						if (temp_obj->Face_to_Left != this->Face_to_Left) {
							toMotion(222);
						}
						else {
							toMotion(224);
						}
					}
					else {						// 被打到第一下
						toMotion(220);
					}

					setYstep(tempf._i.getDvy(), tempf._i.getDvx(), 0);
					if (temp_obj->Face_to_Left) {
						JumpFront = false; JumpBack = true;
					}
					else {
						JumpFront = true; JumpBack = false;
					}

					switch (tempf._i.get_effect()) {
					case 2:
						toMotion(203);
						break;
					case 3:
						toMotion(200);
						break;
					case 20:
						cantBeTouch = true;
						toMotion(203);
						break;
					case 30:
						cantBeTouch = true;
						toMotion(200);
						break;

					default:
						break;
					}

					temp_obj->addBeaten(this);
					temp_obj->getOwner()->hitSomeOne(this);
					break;
				}
				case 6: {
					useSupperAtt = true;
					break;
				}
				case 15: {
					break;
				}
				case 16: {
					break;
				}
				default: {
					break;
				}
				}
				temp_obj->setArest(tempf._i.getArest());
			}
		}
	}

	
	//人物狀態更新
	void man::OnMove() {
		//TRACE("%d\n",_mode);
		if (stop) {
			if (who->hit) {
				return;
			}
			else {
				stop = false;
			}
		}
		//負責動作的變更
		if (isTime()) {
			nextFrame();
		}
		Count();
		int stateNow = (*Frams)[_mode]._state;
		moveY();
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
			if (_y <= maxH && jumping) {
				jumping = false;
				_y = maxH;
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
			if (_y <= maxH && jumping) {
				jumping = false;
				_y = maxH;
				backToRandon();
			}
			break;
		}
		//大跳
		case 5: {
			if (_y <= maxH && jumping) {
				jumping = false;
				_y = maxH;
				backToRandon();
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
		case 11: {

			break;
		}
		// 跌倒的部分
		case 12: {
			
			break;
		}
		case 13: {
			break;
		}
		// 可被同盟攻擊
		case 14: {
			break;
		}
		case 15: {
			if (_y <= maxH && jumping) {
				jumping = false;
				_y = maxH;
				if(_mode>202 && _mode <200)
					backToRandon();
			}
		}
		case 16: {
			break;
		}
		default: {
			if (_y <= maxH && jumping) {
				jumping = false;
				_y = maxH;
				backToRandon();
			}
			else {
				int dvx = (*Frams)[_mode]._dvx;
				if (Face_to_Left) { _x -= dvx; }
				else { _x += dvx; }
			}
			break;
		}
		}

		if (holdinglt || holdingheavy) {
			wpoint temp = this->getNoFrame()._wp;
			holding->_mode = temp.get_weaponact();

			wpoint ht = holding->getNoFrame()._wp;
			double x = _x;
			double y = _y;
			double z = _z;

			if (Face_to_Left) {
				x += maxW - temp.getX();
				holding->_x = x - (holding->maxW - ht.getX());
				holding->Face_to_Left = true;
			}
			else {
				x += temp.getX();
				holding->_x = x - ht.getX();
				holding->Face_to_Left = false;
			}
			holding->_y = y - temp.getY() + ht.getY();

			holding->_z = _z;
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
		lib->selectByNum(id,(*Frams)[_mode]._pic, index, int(_x), -int(_y) + int(_z));
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
	//------------------------------我也不知道的部分------------------------------------------
	//

	void allobj::add(obj* a) {
		if (all == nullptr) {
			all = new obj*[1];
			all[0] = a;
		}
		else {
			obj** temp = new obj*[num + 1];
			int i;
			for (i = 0; i < num; i++) {
				*(temp + i) = *(all + i);
			}
			*(temp + i) = a;

			delete all;
			all = temp;
		}
		num++;
		so();
	}

	void allobj::del(int n) {
		obj** temp = new obj*[num - 1];
		int i;
		int no = 0;
		for (i = 0; i < num; i++) {
			if (i != n) {
				*(temp + no) = *(all + i);
				no++;
			}
		}
		num--;
		delete all;
		all = temp;
	}

	obj* allobj::getobj(int n) {
		return (*(all + n));
	}

	obj* allobj::getSortObj(int n) {
		return (*(s + n));
	}

	void allobj::so() {
		s = new obj*[num];
		for (int i = 0; i < num; i++) {
			(*(s + i)) = *(all + i);
		}

		std::sort(s, s + num, [](obj* a, obj* b) {return (a)->_z < (b)->_z; });
	}



	//
	//------------------------------主控的部分------------------------------------------
	//

	void ObjContainer::init(int p1,int p2, Bitmaplib *l , Framelib* f) {
		lib = l;
		fl = f;
		if ((p1 != -1) && (p2 != -1)) {
			state = 0;
			mans = new man*[2];
			mans[0] = new man(p1,f,l,&a);
			mans[1] = new man(p2,f,l,&a);

			a.add(mans[0]);
			a.add(mans[1]);

			mans[0]->_x = 100;
			mans[0]->_z = 400;

			mans[1]->_x = 100;
			mans[1]->_z = 500;
		}
		else if ((p1 != -1) && (p2 == -1)) {
			state = 1;
			mans = new man*[1];
			mans[0] = new man(p1, f, l, &a);
			a.add(mans[0]);

			mans[0]->_x = 100;
			mans[0]->_z = 400;
		}
		else if ((p1 == -1) && (p2 != -1)) {
			state = 2;
			mans = new man*[1];
			mans[0] = new man(p1, f, l, &a);
			a.add(mans[0]);

			mans[0]->_x = 100;
			mans[0]->_z = 400;
		}

		creatWeapon(10);
	}
	
	void ObjContainer::KeyDown(UINT nChar){
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
				mans[0]->setComm(1);
				break;
			}
			case KEY_D: {
				mans[0]->setComm(2);
				break;
			}
			case KEY_W: {
				mans[0]->setComm(3);
				break;
			}
			case KEY_X:{
				mans[0]->setComm(4);
				break;
			}
			case KEY_TAB: {
				mans[0]->setComm(5);
				break;
			}
			case KEY_S: {
				mans[0]->setComm(6);
				break;
			}
			case 192: {
				mans[0]->setComm(7);
				break;
			}
			case 74: {
				mans[1]->setComm(1);
				break;
			}
			case 76: {
				mans[1]->setComm(2);
				break;
			}
			case 73: {
				mans[1]->setComm(3);
				break;
			}
			case 188: {
				mans[1]->setComm(4);
				break;
			}
			case  32: {
				mans[1]->setComm(5);
				break;
			}
			case 75: {
				mans[1]->setComm(6);
				break;
			}
			case 190: {
				mans[1]->setComm(7);
				break;
			}
			default:
				break;
			}

		}
		else if (state == 1) {
			switch (nChar) {
			case KEY_A: {
				mans[0]->setComm(1);
				break;
			}
			case KEY_D: {
				mans[0]->setComm(2);
				break;
			}
			case KEY_W: {
				mans[0]->setComm(3);
				break;
			}
			case KEY_X: {
				mans[0]->setComm(4);
				break;
			}
			case KEY_TAB: {
				mans[0]->setComm(5);
				break;
			}
			case KEY_S: {
				mans[0]->setComm(6);
				break;
			}
			case 192: {
				mans[0]->setComm(7);
				break;
			}
			default:
				break;
			}
		}
		else {
			switch (nChar) {
			case 74: {
				mans[0]->setComm(1);
				break;
			}
			case 76: {
				mans[0]->setComm(2);
				break;
			}
			case 73: {
				mans[0]->setComm(3);
				break;
			}
			case 188: {
				mans[0]->setComm(4);
				break;
			}
			case  32: {
				mans[0]->setComm(5);
				break;
			}
			case 75: {
				mans[0]->setComm(6);
				break;
			}
			case 190: {
				mans[0]->setComm(7);
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
				mans[0]->cComm(1);
				break;
			}
			case KEY_D: {
				mans[0]->cComm(2);
				break;
			}
			case KEY_W: {
				mans[0]->cComm(3);
				break;
			}
			case KEY_X: {
				mans[0]->cComm(4);
				break;
			}
			case KEY_TAB: {
				mans[0]->cComm(5);
				break;
			}
			case KEY_S: {
				mans[0]->cComm(6);
				break;
			}
			case 192: {
				mans[0]->cComm(7);
				break;
			}
			case 74: {
				mans[1]->cComm(1);
				break;
			}
			case 76: {
				mans[1]->cComm(2);
				break;
			}
			case 73: {
				mans[1]->cComm(3);
				break;
			}
			case 188: {
				mans[1]->cComm(4);
				break;
			}
			case  32: {
				mans[1]->cComm(5);
				break;
			}
			case 75: {
				mans[1]->cComm(6);
				break;
			}
			case 190: {
				mans[1]->cComm(7);
				break;
			}
			default:
				break;
			}

		}
		else if (state == 1) {
			switch (nChar) {
			case KEY_A: {
				mans[0]->cComm(1);
				break;
			}
			case KEY_D: {
				mans[0]->cComm(2);
				break;
			}
			case KEY_W: {
				mans[0]->cComm(3);
				break;
			}
			case KEY_X: {
				mans[0]->cComm(4);
				break;
			}
			case KEY_TAB: {
				mans[0]->cComm(5);
				break;
			}
			case KEY_S: {
				mans[0]->cComm(6);
				break;
			}
			case 192: {
				mans[0]->cComm(7);
				break;
			}
			default:
				break;
			}
		}
		else {
			switch (nChar) {
			case 74: {
				mans[0]->cComm(1);
				break;
			}
			case 76: {
				mans[0]->cComm(2);
				break;
			}
			case 73: {
				mans[0]->cComm(3);
				break;
			}
			case 188: {
				mans[0]->cComm(4);
				break;
			}
			case  32: {
				mans[0]->cComm(5);
				break;
			}
			case 75: {
				mans[0]->cComm(6);
				break;
			}
			case 190: {
				mans[0]->cComm(7);
				break;
			}
			default: {

			}
			}
		}
	}

	void ObjContainer::OnMove() {
		for (int i = 0; i < a.getN(); i++) {
			(a.getobj(i))->OnMove();
			obj* temp = (a.getobj(i))->usingSkills();
			if (temp != nullptr) {
				a.add(temp);
			}
		}
		check();
		a.so();
	}

	void ObjContainer::OnShow() {
		for (int i = 0; i < a.getN(); i++) {
			(a.getSortObj(i))->OnShow();
		}
	}

	void ObjContainer::creatWeapon(int n) {
		weapon* temp = new weapon(n,0,fl,lib,nullptr,&a);

		temp->init(400, 300,400,false);
		
		temp->setmax(3200, 500);
		a.add(temp);
	}

	void ObjContainer::check() {
		int i;
		if (state == 0) {
			i = 2;
		}
		else {
			i = 1;
		}
		while (i < a.getN()) {
			//TRACE("%d %d\n", i, (all[i]->Alive));
			if (!((a.getobj(i))->Alive)) {
				a.del(i);
			}
			else {
				i++;
			}
		}
	}


}