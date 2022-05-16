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
#include "CStateBar.h"
#include <stdlib.h>
#include <stdlib.h>
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

	void obj::OnShow() {
		int index;
		if (Face_to_Left) index = 0;
		else index = 1;
		lib->selectByNum(id, (*Frams)[_mode]._pic, index, int(_x) - mapdata[1], -int(_y) + int(_z));
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

	void weapon::OnMove() {
		//TRACE("%.1f %.1f %d %d\n",initG,_y, ((*Frams)[_mode]._centery),_mode);
		if (holding == nullptr) {
			moveY();
			if (isTime()) {
				nextFrame();
			}
			int state = (*Frams)[_mode]._state;
			switch (state){
			case 1000: {
				if (_y <= ((*Frams)[_mode]._centery)) {
					toMotion(70);
				}
				break;
			}
			case 1002: {
				if (_y <= ((*Frams)[_mode]._centery)) {
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
			case 2000: {
				if (_y <= ((*Frams)[_mode]._centery)) {
					toMotion(20);
					throwing = false;
				}
				break;
			}
			default:
				break;
			}
			

			int half = int(maxW/2);
			if (_x <= -(half))  _x = -(half);
			else if (_x >= (mapdata[0] + 800 - half))_x = (mapdata[0] + 800 - half);
			if (_z <= mapdata[2])_z = mapdata[2];
			else if (_z >= mapdata[3]) _z = mapdata[3];

			if (_y <= (*Frams)[_mode]._centery && id == 201) {
				Alive = false;
			}

			checkbeenatt();
		}
		else{
			
		}
		Count();
		bcount();
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
			if (tempf._have_itr && t) {				// 這個東西具有攻擊性並且有碰到
				switch (tempf._i.getKind()) {
				case 0: {
					if (!(temp_obj->checkBeenBeaten(this))) {
						setYstep(tempf._i.getDvy(), tempf._i.getDvx(), 0);
						if (temp_obj->Face_to_Left) {
							JumpFront = false; JumpBack = true;
						}
						else {
							JumpFront = true; JumpBack = false;
						}
						temp_obj->addBeaten(this);
						temp_obj->hitSomeOne(this);

						hp -= tempf._i.getInjury();
					}
					break;
				}
				case 2: {
					if (myF._have_itr) continue;

					holding = temp_obj;
					temp_obj->holdingSth(this);
					if (id == 11) {
						temp_obj->toMotion(116);
						temp_obj->holdingheavy = true;
					}
					else {
						temp_obj->toMotion(115);
						temp_obj->holdinglt = true;
					}
					break;
				}
				
				case 5: {
					int dvx;
					Frame weapont = (*(temp_obj->getOwner()->Frams))[temp_obj->getOwner()->_mode];
					int att = weapont._wp.getattcking();
					switch (att) {
					case 0: {
						return;
						break;
					}
					case 1: {
						if (temp_obj->id == 10) {
							dvx = 2;
							hp -= 40;
						}
						else {
							dvx = 2;
							hp -= 30;
						}
						break;
					}
					case 2: {
						if (temp_obj->id == 10) {
							dvx = 7;
							hp -= 40;
						}
						else {
							dvx = 7;
							hp -= 30;
						}
						break;
					}
					case 3: {
						if (temp_obj->id == 10) {
							dvx = 10;
							hp -= 50;
						}
						else {
							dvx = 10;
							hp -= 40;
						}
						break;
					}
					case 4: {
						if (temp_obj->id == 10) {
							dvx = 12;
							hp -= 50;
						}
						else {
							dvx = 12;
							hp -= 40;
						}
						break;
					}
					default:
						break;
					}
					setYstep(tempf._i.getDvy(), tempf._i.getDvx(), 0);
					if (temp_obj->Face_to_Left) {
						JumpFront = false; JumpBack = true;
					}
					else {
						JumpFront = true; JumpBack = false;
					}
					temp_obj->addBeaten(this);
					temp_obj->getOwner()->hitSomeOne(this);
					break;
				}
				
				case 15: {
					setYstep(tempf._i.getDvy(),tempf._i.getDvx(),0);
					
					int middle = int(temp_obj->_x);
					if (temp_obj->Face_to_Left) {
						middle += (temp_obj->maxW - tempf._centerx);
					}
					else {
						middle += tempf._centerx;
					}

					int self_middle = int(_x);
					if (this->Face_to_Left) {
						self_middle += (this->maxW - myF._centerx);
					}
					else {
						self_middle += myF._centerx;
					}

					// 在左邊
					if ((middle - self_middle) <0) {
						JumpBack = false; JumpFront = true;
					}
					else {
						JumpBack = true; JumpFront = false;
					}

					if (!(temp_obj->checkBeenBeaten(this))) {
						temp_obj->addBeaten(this);
						temp_obj->hitSomeOne(this);
						hp -= tempf._i.getInjury();
					}

				}

				default: {
					break;
				}
				}
				temp_obj->setArest(tempf._i.getArest());
			}
		}
	}

	void weapon::hitSomeOne(obj* other) {
		if(id == 201)
			toMotion(60);
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
			temp->setmax(3200);
			temp->mapSetting(mapdata);
			skills = temp;
		}
	}

	void wp::nextFrame() {
		int temp = (*Frams)[_mode]._next;
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

		if (_x > mapdata[1] + 1000 || _x< -200) {
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
		if (holdingheavy) {
			_mode = 12;
			setTimmer((*Frams)[_mode]._wait);
		}
		else {
			_mode = 0;
			setTimmer((*Frams)[_mode]._wait);
		}
		if (cantBrTouchCount == 0) {
			cantBeTouch = false;
		}
	}

	void man::toMotion(int f) {
		int next;
		int nowmp = (*Frams)[f]._mp;
		int afterhp, aftermp;
		afterhp = (nowmp / 1000) *10;
		aftermp = (nowmp % 1000);
		if ((afterhp > 0 && afterhp > hp) || aftermp > mp) {
			next = 0;
		}
		else {
			next = f;
			hurt(afterhp);
			mp -= aftermp;
		}


		adjustPosition(_mode, next);
		_mode = next;
		inMotion = true;
		Frame tempF = (*Frams)[_mode];
		setTimmer(tempF._wait);
		int numOFwav = tempF._sound;
		if(numOFwav!=0)  CAudio::Instance()->Play(numOFwav+5);
		if (tempF._have_opiont) {
			int oid = tempF._op.getOid();
			if (oid == 12) {
				weapon* temp = new weapon(oid, 0, fl, lib, nullptr, _a);
				temp->holdingSth(this);
				holding = temp;
				holdinglt = true;
				temp->setmax(3200);

				skills = temp;
			}
			else if (oid == 201) {
				weapon* temp = new weapon(oid, 0, fl, lib, nullptr, _a);
				temp->holdingSth(nullptr);

				bool ftl;
				if (tempF._op.getFacing() == 1) ftl = !Face_to_Left;
				else ftl = Face_to_Left;

				if (Face_to_Left) {
					temp->init(int(_x) + maxW - tempF._op.getX(), int(_y) - tempF._op.getY(), int(_z), ftl);
				}
				else {
					temp->init(int(_x) + tempF._op.getX(), int(_y) - tempF._op.getY(), int(_z), ftl);
				}

				temp->setYstep(-3, 12, 0);
				temp->toMotion(40);
				temp->setdir(Face_to_Left);
				temp->mapSetting(mapdata);

				skills = temp;
			}
			else {
				wp* temp = new wp(oid, tempF._op.getAction(), fl, lib, getOwner());
				bool ftl;
				if (tempF._op.getFacing() == 1) ftl = !Face_to_Left;
				else ftl = Face_to_Left;

				if (Face_to_Left) {
					temp->init(int(_x) + maxW - tempF._op.getX(), int(_y) - tempF._op.getY(), int(_z), ftl);
				}
				else {
					temp->init(int(_x) + tempF._op.getX(), int(_y) - tempF._op.getY(), int(_z), ftl);
				}
				temp->mapSetting(mapdata);
				
				skills = temp;
			}
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
			else if (holdingheavy) {
				toMotion(12);
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
			int tempState = (*Frams)[_mode]._state;
			if (tempState == 14) {
				if (hp<=0) {
					Alive = false;
				}
				else {
					cantBeTouch = true;
					cantBrTouchCount = 20;
					toMotion(temp);
				}
			}
			else if (tempState == 18) {
				if (_y <= maxH) {
					if (_mode == 204) {
						toMotion(230);
					}
					else if (_mode == 206) {
						toMotion(231);
					}
					else {
						toMotion(temp);
					}
				}
				else {
					toMotion(temp);
				}
			}
			else if (tempState == 9) {
				Caught->_mode = (*Frams)[_mode]._cp.getVaction();
				if ((*Frams)[_mode]._cp.getInjury() != 0) {
					Caught->hp -= 15;
				}
				toMotion(temp);
			}
			else {
				toMotion(temp);
			}
		}
		else{
			//TRACE("right %d\n", (*Frams)[_mode]._state);
			// 特殊動作
			switch ((*Frams)[_mode]._state){
			case 2: {
				if (run_Ani_dir) {
					if (holdingheavy) {
						if (++_mode >= 19) {
							_mode = 17;
							run_Ani_dir = !run_Ani_dir;
						}
					}
					else {
						if (++_mode >= 12) {
							_mode = 10;
							run_Ani_dir = !run_Ani_dir;
						}
					}
				}
				else {
					if (holdingheavy) {
						if (--_mode <= 15) {
							_mode = 17;
							run_Ani_dir = !run_Ani_dir;
						}
					}
					else {
						if (--_mode <= 8) {
							_mode = 10;
							run_Ani_dir = !run_Ani_dir;
						}
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
						if (_y <= maxH) {
							toMotion(230);
						}
					}
					else if (_mode == 144) {
						if (_y <= maxH) {
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
				else if (_mode == 191) {
					if (int(_y) <= maxH) {
						_y = maxH;
						toMotion(231);
					}
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
						if (holdinglt) {
							if (first_att_animation) {
								toMotion(20);
							}
							else {
								toMotion(25);
							}
							first_att_animation = !first_att_animation;
						}
						else {
							toMotion(70);
						}
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
					int temp_state = (*Frams)[_mode]._state;
					
					if (( temp_state <= 1) || (temp_state==7)) {
						if (i == 0) {
							if (Face_to_Left) { 
								if (holdingheavy) toMotion(16);
								else toMotion(SkillsMotion[0]);
							} 
						}
						else if (i == 1) { 
							if (!Face_to_Left) {
								if (holdingheavy) toMotion(16);
								else toMotion(SkillsMotion[1]);
							}
						}
						else { toMotion(SkillsMotion[i]); }
						commandBuffer = "";
					}
				}
				else {
					int len = commandBuffer.size();
					if (commandList[i].substr(0, len) == commandBuffer) { match = true; }
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
			bool button_down = false;
			// 處理移動
			
			for (int i = 0; i < 4; i++) {
				if (_dir[i]) {
					button_down = true;
					break;
				}
			}
			if (button_down && isTime()) {
				if (holdingheavy) {
					int Modecc;
					if (walk_Ani_dir) {
						Modecc = _mode + 1;
						if (Modecc >= 16) {
							toMotion(14);
							walk_Ani_dir = !walk_Ani_dir;
						}
						else { toMotion(Modecc); }
					}
					else {
						Modecc = _mode - 1;
						if (Modecc <= 11) {
							toMotion(13);
							walk_Ani_dir = !walk_Ani_dir;
						}
						else { toMotion(Modecc); }
					}
				}
			}

			if (flag[5] && holdingheavy) {
				flag[5];
				toMotion(50);
			}
			if (flag[6]) {
				toMotion(102);
			}
			break;
		}
		case 2: {
			if (flag[0] && !Face_to_Left) {
				if (holdingheavy) { toMotion(19); }
				else { toMotion(218); }
			}
			else if (flag[1] && Face_to_Left) {
				if (holdingheavy) { toMotion(19); }
				else { toMotion(218); }
			}
			else if (flag[4]) {
				if (!holdingheavy) {
					if (Face_to_Left) { JumpBack = true; JumpFront = false; }
					else { JumpBack = false; JumpFront = true; }
					if (_dir[2]) { JumpUp = true; }
					else { JumpUp = false; }
					if (_dir[3]) { JumpDown = true; }
					else { JumpDown = false; }
					setYstep(-11, 15, 3.75);
					toMotion(213);
				}
			}
			else if (flag[5]) {
				if (holdinglt) {
					if (flag[0] && Face_to_Left) toMotion(45);
					else if (flag[1] && !Face_to_Left) toMotion(45);
					else toMotion(35);
				}
				else if (holdingheavy) toMotion(50);
				else {
					toMotion(85);
				}
			}
			break;
		}
		case 4: {
			if (flag[0]) Face_to_Left = true;
			if (flag[1])Face_to_Left = false;

			if (flag[5]) {
				if (holdinglt) {
					toMotion(30);
				}
				else {
					toMotion(80);
				}
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
				if (holdinglt) {
					toMotion(40);
				}
				else {
					toMotion(90);
				}
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
			if (temp_obj == this || temp_obj == holding || this == temp_obj->getOwner()) {
				continue;
			}



			if (temp_obj->id > 2 && temp_obj->id < 5  && id > 2 && id < 5) {
				continue;
			}
			int mode = temp_obj->_mode;
			Frame tempf = (*(temp_obj->Frams))[mode];
			if (temp_obj->getArest() > 0) {
				continue;
			}
			bool t = touch(temp_obj);
			if(tempf._have_itr && t){				// 這個東西具有攻擊性並且有碰到
				if ((myF._state == 12 || myF._state == 18)&& tempf._i.getFall() < 60) {
					continue;
				}
				// TRACE("%d %d \n",temp_obj->id, tempf._i.getKind());

				int eff;
				switch (tempf._i.getKind()) {
				// 普通攻擊
				case 0: {
					if (!(temp_obj->checkBeenBeaten(this))) {
						if (tempf._state == 18 && myF._state == 19) continue;

						if (holdinglt) {
							holding->setYstep(0, 0, 0);
							holding->setdir(Face_to_Left);
							holding->toMotion(40);
							holding->holdingSth(nullptr);
							holding = nullptr;
							holdinglt = false;
							holdingheavy = false;
						}
						else if (holdingheavy) {
							holding->setYstep(0, 0, 0);
							holding->setdir(Face_to_Left);
							holding->toMotion(0);
							holding->holdingSth(nullptr);
							holding = nullptr;
							holdinglt = false;
							holdingheavy = false;
						}

						int fa = tempf._i.getFall();

						if (fa == 0) { fall -= 18; }
						else { fall -= fa; }

						injuredMotion(temp_obj->Face_to_Left);

						switch (tempf._i.get_effect()) {
						case 2:
							toMotion(203);
							
							setYstep(tempf._i.getDvy()/2, tempf._i.getDvx(), 0);
							if (temp_obj->Face_to_Left) {
								JumpFront = false; JumpBack = true;
							}
							else {
								JumpFront = true; JumpBack = false;
							}
							break;
						case 3:
							toMotion(201);
							
							setYstep(tempf._i.getDvy()/2, tempf._i.getDvx(), 0);
							if (temp_obj->Face_to_Left) {
								JumpFront = false; JumpBack = true;
							}
							else {
								JumpFront = true; JumpBack = false;
							}
							break;
						case 20:
							cantBeTouch = true;
							toMotion(203);
							break;
						case 30:
							cantBeTouch = true;
							toMotion(201);
							break;
						default:
							setYstep(tempf._i.getDvy(), tempf._i.getDvx(), 0);
							if (temp_obj->Face_to_Left) {
								JumpFront = false; JumpBack = true;
							}
							else {
								JumpFront = true; JumpBack = false;
							}
							break;
						}
						
						temp_obj->addBeaten(this);
						temp_obj->hitSomeOne(this);
						hit = true;

						hurt(tempf._i.getInjury());
						if (hp <= 0) {
							if (temp_obj->Face_to_Left != this->Face_to_Left) {
								toMotion(180);
							}
							else {
								toMotion(186);
							}
							time = (*Frams)[_mode]._wait;
							fall = 100;
						}
					}
					break;
				}
				// 抓住暈眩的人
				case 1: {
					if ((*Frams)[_mode]._state == 16) {
						temp_obj->toMotion(tempf._i.getCatching());
						temp_obj->Caught = this;
						this->toMotion(tempf._i.getCaught());

						Face_to_Left = !temp_obj->Face_to_Left;
						temp_obj->cc = 301;
						_z = temp_obj->_z;
					}
					break;
				}
				// 武器攻擊
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
							fall -= 40.0;
							hurt(40);
							hp -= 40;
							defend -= 16;
						}
						else {
							dvx = 2;
							fall -= 40.0;
							hurt(30);
							defend -= 16;
						
							eff = 201;
						}
						break;
					}
					case 2: {
						if (temp_obj->id == 10) {
							dvx = 7;
							fall -= 70;
							hurt(40);
							defend -= 16;
						}
						else {
							dvx = 7;
							fall -= 70;
							hurt(30);
							defend -= 16;

							eff = 201;
						}
						break;
					}
					case 3: {
						if (temp_obj->id == 10) {
							dvx = 10;
							fall -= 70;
							hurt(50);
							defend -= 16;
						}
						else {
							dvx = 10;
							fall -= 70;
							hurt(40);
							defend -= 16;

							eff = 201;
						}
						break;
					}
					case 4: {
						if (temp_obj->id == 10) {
							dvx = 12;
							fall -= 70;
							hurt(50);
							defend -= 60;
						}
						else {
							dvx = 12;
							fall -= 70;
							hurt(40);
							defend -= 60;

							eff = 201;
						}
						break;
					}
					default:
						break;
					}
					
					injuredMotion(temp_obj->Face_to_Left);


					setYstep(tempf._i.getDvy(), tempf._i.getDvx(), 0);
					if (temp_obj->Face_to_Left) {
						JumpFront = false; JumpBack = true;
					}
					else {
						JumpFront = true; JumpBack = false;
					}

					switch (tempf._i.get_effect()) {
					case 2:
						eff = 203;
						break;
					case 3:
						eff = 200;
						break;
					case 20:
						cantBeTouch = true;
						eff = 203;
						break;
					case 30:
						cantBeTouch = true;
						eff = 200;
						break;

					default:
						break;
					}
					if (eff == 201) {
						if (myF._state == 15 || myF._state == 13) {
							if (temp_obj->Face_to_Left != this->Face_to_Left) {
								toMotion(180);
							}
							else {
								toMotion(186);
							}
							fall = 100;
						}
						else {
							toMotion(200);
						}
					}
					else {
						toMotion(203);
					}

					temp_obj->addBeaten(this);
					temp_obj->getOwner()->hitSomeOne(this);

					if (hp <= 0) {
						if (temp_obj->Face_to_Left != this->Face_to_Left) {
							toMotion(180);
						}
						else {
							toMotion(186);
						}
						time = (*Frams)[_mode]._wait;
						fall = 100;
					}
					break;
				}
				// 可使用終結季
				case 6: {
					useSupperAtt = true;
					break;
				}
				// 龍捲風捲起來
				case 15: {
					setYstep(tempf._i.getDvy(), tempf._i.getDvx(), 0);

					int middle = int(temp_obj->_x);
					if (temp_obj->Face_to_Left) {
						middle += (temp_obj->maxW - tempf._centerx);
					}
					else {
						middle += tempf._centerx;
					}

					int self_middle = int(_x);
					if (this->Face_to_Left) {
						self_middle += (this->maxW - myF._centerx);
					}
					else {
						self_middle += myF._centerx;
					}

					// 在左邊
					if ((middle - self_middle) < 0) {
						JumpBack = false; JumpFront = true;
					}
					else {
						JumpBack = true; JumpFront = false;
					}

					if (!(temp_obj->checkBeenBeaten(this))) {
						temp_obj->addBeaten(this);
						temp_obj->hitSomeOne(this);
						hp -= tempf._i.getInjury();
					}
					break;
				}
				// 龍捲風結冰
				case 16: {
					if (!(temp_obj->checkBeenBeaten(this))) {
						temp_obj->addBeaten(this);
						temp_obj->hitSomeOne(this);
						hp -= tempf._i.getInjury();
					}
					toMotion(201);
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

	void man::thw_obj() {
		if (holdinglt) {
			holding->toMotion(40);

		}
		else if (holdingheavy) {

		}
	}
	
	
	//人物狀態更新
	void man::OnMove() {
		if (!Alive) return;

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
			if (_y <= (*Frams)[_mode]._centery && jumping) {
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
			if (_y <= (*Frams)[_mode]._centery && jumping) {
				jumping = false;
				_y = maxH;
				backToRandon();
			}
			break;
		}
		//大跳
		case 5: {
			if (_y <= (*Frams)[_mode]._centery && jumping) {
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
		// 被打
		case 11: {

			break;
		}
		// 跌倒的部分
		case 12: {
			
			break;
		}
		
		// 被冰起來
		case 13: {
			if (_y <= maxH && jumping) {
				toMotion(182);
			}
			break;
		}
		// 可被同盟攻擊
		case 14: {
			break;
		}
		
		// 可以被同盟攻擊，基本上沒用
		case 15: {
			if (_y <= maxH && jumping) {
				jumping = false;
				_y = maxH;
				if(_mode>202 && _mode <200)
					backToRandon();
			}
		}
		
		// 暈眩
		case 16: {
			break;
		}
		case 18: {
			break;
		}
		case 19: {
			int dvx = (*Frams)[_mode]._dvx;
			if (Face_to_Left) { _x -= dvx; }
			else { _x += dvx; }
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

		if (_x <= -40)  _x = -40;
		else if (_x >= (mapdata[0] + 760))_x = (mapdata[0] + 760);
		if (_z <= mapdata[2])_z = mapdata[2];
		else if (_z >= mapdata[3]) _z = mapdata[3];

		useSupperAtt = false;
		bcount();
		checkbeenatt();
		checkFlag();
		checkBuff();


		if (holdinglt || holdingheavy) {
			wpoint temp = this->getNoFrame()._wp;
			//TRACE("%d %d \n", temp.get_weaponact(), _mode);
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

			int weapony = temp.getdvy();
			int weaponx = temp.getdvx();
			if (weaponx != 0) {
				holding->setYstep(weapony, weaponx, 0);
				holding->setdir(Face_to_Left);
				if (holdinglt) {
					holding->toMotion(40);
				}
				else if (holdingheavy) {
					holding->toMotion(0);
				}
				holding->holdingSth(nullptr);
				holding = nullptr;
				holdinglt = false;
				holdingheavy = false;
			}

		}
		
		if (mp >= 500) mp = 500;
		if (hp >= 500) hp = 500;
		else if (HpRecover >= 500) HpRecover = 500;
		else if (hp >= HpRecover) HpRecover = hp;
		
		if (id < 3) {
			bar->setHP(player, hp, HpRecover);
			bar->setMP(player, mp);
		}
	}

	//處理指令輸入時間間隔
	void man::setCountDwon() {
		_Double_Tap_Gap = 75;
	}

	void man::resetCountDown() {
		_Double_Tap_Gap = -1;
	}

	void man::hurt(int d) {
		HpRecover -= (d / 3);
		hp -= d;
	}
	
	//
	//------------------------------物品容器------------------------------------------
	//

	void allobj::init() {
		if (all != nullptr) {
			delete[] all;
		}
		all = nullptr;
		num = 0;
	}
	
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
		delete *(all + n);
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

	void ObjContainer::init(int p1,int p2) {
		//
		// 物品初始化
		// 
		a.init();

		//
		//人物初始化
		//
		if (mans != nullptr) delete[] mans;
		mans = nullptr;
		
		if ((p1 != -1) && (p2 != -1)) {
			state = 0;
			mans = new man*[2];
			mans[0] = new man(p1, fl, lib, &a);
			mans[0]->mapSetting(map_data);
			mans[0]->_x = 100;
			mans[0]->_z = 400;
			mans[0]->setplayer(0, &bar);

			a.add(mans[0]);

			mans[1] = new man(p2, fl, lib, &a);
			mans[1]->mapSetting(map_data);
			mans[1]->_x = 100;
			mans[1]->_z = 450;
			mans[1]->setplayer(1, &bar);

			a.add(mans[1]);
		}
		else if ((p1 != -1) && (p2 == -1)) {
			state = 1;
			mans = new man*[1];
			mans[0] = new man(p1, fl, lib, &a);
			mans[0]->mapSetting(map_data);
			mans[0]->_x = 100;
			mans[0]->_z = 425;
			mans[0]->setplayer(0, &bar);
			
			a.add(mans[0]);
		}
		else if ((p1 == -1) && (p2 != -1)) {
			state = 2;
			mans = new man*[1];
			mans[0] = new man(p2, fl, lib, &a);
			mans[0]->mapSetting(map_data);
			mans[0]->_x = 100;
			mans[0]->_z = 425;
			mans[0]->setplayer(1, &bar);

			a.add(mans[0]);
		}
		else {
			state = 3;
		}
		bar.init(p1, p2);

	}
	
	void ObjContainer::mapSetting(int* data){
		map_data = data;
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
		if (state == 0) {
			com.updateEnemy(2, mans);
		}
		else {
			com.updateEnemy(1, mans);
		}


		for (int i = 0; i < a.getN(); i++) {
			(a.getobj(i))->OnMove();
			obj* temp = (a.getobj(i))->usingSkills();
			if (temp != nullptr) {
				a.add(temp);
			}
		}

		com.OnMove();							//電腦指派任務階段
		
		check();
		a.so();
	}

	void ObjContainer::OnShow() {
		bar.OnShowBar();
		for (int i = 0; i < a.getN(); i++) {
			(a.getSortObj(i))->OnShow();
		}
	}

	void ObjContainer::creatWeapon(int n,int x,int z) {
		weapon* temp = new weapon(n,0,fl,lib,nullptr,&a);
		temp->init(x, 800 - z,z,false);
		
		temp->mapSetting(map_data);
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
			if (!((a.getobj(i))->isAlive())) {
				com.check();
				a.del(i);
			}
			else {
				i++;
			}
		}

	}

	void ObjContainer::creatEnemy(int type, int x, int z) {
		man* enemy;
		if (type) {
			enemy = new man(4, fl, lib, &a);
		}
		else {
			enemy = new man(3, fl, lib, &a);
		}
		enemy->_x = x;
		enemy->_z = z;
		enemy->mapSetting(map_data);
		com.add(enemy);
		a.add(enemy);
	}

	int ObjContainer::getEnemyHP() {
		return com.getTotalHP();
	}

	int ObjContainer::getHP() {
		if (state == 0) {
			int total = 0;
			for (int i = 0; i < 2; i++)
				total += mans[i]->getHP();
			return total;
		}
		else {
			return mans[0]->getHP();
		}
	}

	//
	// ------------------------------電腦的部分------------------------------------------
	//

	

	void AI::OnMove() {
		for (int i = 0; i < n; i++) {
			//
			// 選定目標
			//
			man *Traget_now;
			man *com_now = *(self + i);


			int ch = (*(commandType + i)) % numOfTarget;

			if (!(*(Target + ch))->isAlive()) {
				ch = (ch + 1 ) % numOfTarget;
			}
			Traget_now = *(Target + ch);

			
			int tx = Traget_now->getX();
			int tz = Traget_now->getZ();
			
			int diffx = com_now->getX() - tx;
			int diffz = com_now->getZ() - tz;
			
			int se = 0;
			if (com_now->id == 3) {
				if (com_now->Face_to_Left)
					se = 80;
				else
					se = 40;
			}
			else {
				if (com_now->Face_to_Left)
					se = 250;
				else
					se = 200;
			}
			//TRACE("%d\n", diffx);

			for (int j = 1; j < 7; j++)com_now->cComm(j);
			if (abs(diffx)>500) {
				if ((*(com_now->Frams))[com_now->_mode]._state != 2) {
					if (diffx < 0) {
						com_now->Face_to_Left = false;
					}
					else {
						com_now->Face_to_Left = true;
					}
					com_now->toMotion(9);
				}
				if (diffz < -10) {
					com_now->setComm(4);
				}
				else if (diffz > 10) {
					com_now->setComm(3);
				}
				else {
					com_now->cComm(3);
					com_now->cComm(4);
				}
			}
			else if(abs(diffx) > se){
				if ((*(com_now->Frams))[com_now->_mode]._state == 2 && com_now->_mode != 218) {
					if ((rand() % 25) == 0)com_now->toMotion(218);
				}
				else {
					if ((*(com_now->Frams))[com_now->_mode]._state != 1) {
						if (diffx < 0) {
							com_now->setComm(2);
						}
						else {
							com_now->setComm(1);
						}
					}
				}

				if (diffz < -10) {
					com_now->setComm(4);
				}
				else if(diffz > 10){
					com_now->setComm(3);
				}
			}
			else {
				if (diffz < -10) {
					com_now->setComm(4);
				}
				else if (diffz > 10) {
					com_now->setComm(3);
				}
				if (com_now->getX() == 0) {
					if (com_now->Face_to_Left) {
						com_now->setComm(2);
					}
					else {
						com_now->setComm(1);
					}
				}
				else {
					if (diffx < 0 && !com_now->Face_to_Left) {
						if (!com_now->Face_to_Left) {
							if ((rand() % 25) == 0) { com_now->setComm(6); }
						}
						else { 
							if ((rand() % 10) == 0) { com_now->setComm(2); } 
						}
					}
					else if (diffx > 0 && com_now->Face_to_Left) {
						if (com_now->Face_to_Left) {
							if ((rand() % 25) == 0) { com_now->setComm(6); }
						}
						else {
							if ((rand() % 10) == 0) { com_now->setComm(1); }
						}
					}
					
				}


			}
		}
	}

	void AI::updateEnemy(int n, man** mans) {
		numOfTarget = n;
		Target = mans;
	}

	void AI::add(man* newone) {
		if (self == nullptr) {
			self = new man*[1];
			self[0] = newone;

			commandType = new int;
			commandType[0] = rand() % 2;
		}
		else {
			man** temp = new man*[n + 1];
			
			int * temp_command = new int[n+1];
			
			int i;
			for (i = 0; i < n; i++) {
				*(temp + i) = *(self + i);
				*(temp_command + i) = *(commandType + i);
			}
			*(temp + i) = newone;
			*(temp_command + i) = rand()%2;


			delete commandType;
			commandType = temp_command;
			delete self;
			self = temp;

		}
		n++;
	}

	void AI::del(int num) {
		man** temp = new man*[n - 1];
		int * temp_command = new int[n - 1];
		int i;
		int no = 0;
		for (i = 0; i < n; i++) {
			if (i != num) {
				*(temp + no) = *(self + i);
				*(temp_command + no) = *(commandType + i);
				no++;
			}
		}
		n--;
		delete commandType;
		commandType = temp_command;
		delete self;
		self = temp;
	}

	void AI::del(obj* shit) {
		
		
		if (n == 1) {
			n = 0;
			//delete commandType;
			//delete self;
			commandType = nullptr;
			self = nullptr;
		}
		else {
			man** temp = new man*[n - 1];
			int * temp_command = new int[n - 1];
			int i;
			int no = 0;
			for (i = 0; i < n; i++) {
				if (*(temp + i) != shit) {
					*(temp + no) = *(self + i);
					*(temp_command + no) = *(commandType + i);
					no++;
				}
			}
			n--;
			delete commandType;
			commandType = temp_command;
			delete self;
			self = temp;
		}

	}

	void AI::check() {
		int i = 0;
		while (i < n) {
			if (! ((*(self + i))->isAlive())) {
				del(i);
			}
			else {
				i++;
			}
		}
	}

	int AI::getTotalHP() {
		int temp =0 ;
		for (int i = 0; i < n; i++) {
			int hp = (*(self + i))->hp;
			if (hp < 0) {
				temp += 0;
			}
			else {
				temp += hp;
			}
		}
		return temp;
	}
}