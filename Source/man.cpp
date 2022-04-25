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


	// 初始化外部資料
	void man::init(Bitmaplib *l, man *m, int n, CStateBar *state, std::map<int, Frame> *f) {
		lib = l;				//獲取圖片庫
		mans = m;				//獲取場上人數
		NumOfMan = n;
		Frams = f;				//獲取動作表
		_s = state;				//搞耍

		readCommand();
	}

	void man::readCommand() {
		commandList.push_back("11");
		commandList.push_back("22");
		readOtherList();
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
		//TRACE("next : %d pic : %d\n", (*Frams)[_mode]._next, (*Frams)[_mode]._pic);
		restList();
		int temp = (*Frams)[_mode]._next;
		if (temp == 999) {
			if ( _y < 0) {
				adjustPosition(_mode, 212);
				_mode = 212;
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
				if (flag[5]) {
					flag[5] = false;
					int p = (*Frams)[_mode]._cp.getAaction();
					adjustPosition(_mode, p);
					_mode = p;
					Caught->_mode = (*Frams)[_mode]._cp.getVaction();
					setTimmer((*Frams)[_mode]._wait);
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
		if (comm == 2) {
			flag[0] = false;
			commandBuffer += '2';
		}

		if (comm == 1) {
			flag[1] = false;
			commandBuffer += '1';
		}

		if (comm == 3) {
			flag[3] = false;
			commandBuffer += '3';
		}

		if (comm == 4) {
			flag[2] = false;
			commandBuffer += '4';
		}

		if (comm == 5) {commandBuffer += '5';}

        if (comm == 6) {commandBuffer += '6';}

		if (comm == 7) {commandBuffer += '7';}
		
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
		}
		// 處理移動
		if (flag[0]) {
			_dir[0] = true;
			_dir[1] = false;
		}
		else if (flag[1]) {
			_dir[0] = false;
			_dir[1] = true;
		}
		else {
			_dir[0] = false; _dir[1] = false;
		}

		if (flag[2]) {
			_dir[2] = true;
			_dir[3] = false;
		}
		else if (flag[3]) {
			_dir[2] = false;
			_dir[3] = true;
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
		if (inMotion) return;

		if (_Double_Tap_Gap <= 0) {
			setCountDwon();
			commandBuffer = "";
		}
		else{
			//TRACE("%s\n", commandBuffer.c_str());
			int index = 0;
			std::vector<std::string>::iterator i;
			for (i = commandList.begin(); i != commandList.end(); ++i) {
				if (*i == commandBuffer) break;
				index++;
			}
			if (index != commandList.size()) {
				commandBuffer = "";
				if (index == 0 || index == 1) {
					toMotion(9);
				}
				else{
					otherCommand(index);
				}
			}
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
		
		default:
			break;
		}
	}

	void man::checkbeenatt() {
		for (int i = 0; i < numofobj; i++) {
			if (*(all + i) == this) {
				continue;
			}
			int mode = (*(*(all + i)))._mode;
			Frame tempf = (*((*(*(all + i))).Frams))[mode];
			if(tempf._have_itr){				// 這個東西具有攻擊性
				switch (tempf._i.getKind()) {
				case 0: {
					if (touch(tempf._i, (*(*(all + i))).Face_to_Left, (*(*(all + i)))._x, (*(*(all + i)))._y, (*(*(all + i)))._z)) {
						if (!((*(all + i))->checkBeenBeaten(this))) {
							int fa = tempf._i.getFall();
							if (fa == 0) { fall -= 18; }
							else { fall -= fa; }
							//TRACE("%d %.1f\n", fa, fall);
							//TRACE("%d %d\n", temp.Face_to_Left, this->Face_to_Left);
							if (fall < 35) {			// 擊飛
								if ((*(*(all + i))).Face_to_Left != this->Face_to_Left) {
									toMotion(180);
								}
								else {
									toMotion(186);
								}
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
						}
					}
					break;
				}
				case 1: {
					if (touch(tempf._i, (*(*(all + i))).Face_to_Left, (*(*(all + i)))._x, (*(*(all + i)))._y, (*(*(all + i)))._z)) {
						if ((*Frams)[_mode]._state == 16) {
							inMotion = true;
							(*(all + i))->inMotion = true;

							(*(all + i))->_mode = tempf._i.getCatching();
							(*(all + i))->Caught = this;
							this->_mode = tempf._i.getCaught();

							Face_to_Left = !(*(all + i))->Face_to_Left;
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
				(*(all + i))->addBeaten(this);
			}
		}
	}

	//人物狀態更新

	void man::OnMove() {

		int stateNow = (*Frams)[_mode]._state;
		int nextF = (*Frams)[_mode]._next;
		// 負責動作變更
		if (isTime()) {
			nextFrame();
		}
		moveY();
		// 負責位置的調整
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
		
		case 9: {
			int cx;
			int cy  = (*(Caught->Frams))[_mode]._cp.getY();
			bool cf = Caught->Face_to_Left;

			if (cf) { cx = 79 - (*(Caught->Frams))[_mode]._cp.getX(); }
			else { cx = (*(Caught->Frams))[_mode]._cp.getX(); }


			
			break;
		}
		case 10: {

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

		CountDown();
		Count();
	}
	
	//人物顯示

	void man::onShow() {
		int index;
		if (Face_to_Left) index = 0;
		else index = 1;
		//TRACE("%d\n", (*Frams)[_mode]._pic);
		lib->selectByNum(0,(*Frams)[_mode]._pic, index, int(_x), int(_y) + int(_z) - (*Frams)[_mode]._centery);
	
		
	}

	//處理指令輸入時間間隔

	void man::setCountDwon() {
		_Double_Tap_Gap = 75;
	}

	void man::resetCountDown() {
		_Double_Tap_Gap = -1;
	}

	//這是留給子類別操控的func

	void man::otherCommand(int n) {

	}
	

	void man::readOtherList() {

	}
}
