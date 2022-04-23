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

#define height 28
#define File ".\\data\\t.txt"
namespace game_framework {

	//初始化
	int* man::extra(std::string &line, std::string *tar, int number) {
		int *value = new int[number];
		for (int i = 0; i < number; i++)	value[i] = -1;
		for (int i = 0; i < number; i++) {
			unsigned int temp = 0;
			temp = line.find(tar[i], temp);
			if (temp != std::string::npos) {
				temp += tar[i].length() + 2;
				std::string temp_id = "";
				while (line[temp] != ' ' && (temp < line.size())) {
					temp_id += line[temp++];
				}
				value[i] = std::stoi(temp_id);
			}
		}
		return value;
	}

	void man::init(Bitmaplib *l, man *m, int n, CStateBar *state, std::map<int, Frame> *f) {
		lib = l;
		mans = m;
		NumOfMan = n;
		Frams = f;

		_s = state;
		readCommand();
	}

	void man::loadFrame() {
		std::ifstream ifs(File, std::ios::in);
		if (!ifs.is_open()) {
			TRACE("Failed to open file.");
		}
		else {
			std::string s;
			while (std::getline(ifs, s)) {
				if (s.substr(0, 7) == "<frame>") {
					Frame a;
					int b = 8;
					std::string id = "";
					while (s[b] != ' ') {
						id += s[b++];
					}
					a._id = std::stoi(id);
					std::getline(ifs, s);
					std::string g[10] = { "pic","state","wait","next","dvx","dvy","centerx","centery","sound","mp" };
					int *temp_basic = extra(s, g, 10);
					a.setBasic(temp_basic);
					// TRACE("%d\n", a._next);

					std::getline(ifs, s);       //換下一行
					while (s != "<frame_end>") {
						if (s == "   wpoint:") {
							std::getline(ifs, s);
							std::string w[8] = { "x","y","weaponact","attacking","cover","dvx","dvy","dvz" };
							
							a.setWpoint(extra(s, w, 8));
						}
						else if (s == "   bdy:") {
							std::getline(ifs, s);
							std::string btar[4] = { "x","y","w","h" };

							a.addBody(extra(s, btar, 4));
						}
						else if (s == "   itr:") {
							std::getline(ifs, s);
							std::string btar[7] = { "kind","x","y","w","h","catchingact","caughtact" };
							a.setItr(extra(s, btar, 7));
						}
						else if (s == "   opoint:") {
							std::getline(ifs, s);
							std::string btar[6] = { "kind","x","y","action","oid","facing" };
							a.setOpoint(extra(s, btar, 6));
						}
						else if (s == "   cpoint:") {
							std::getline(ifs, s);
							std::string btar[12] = { "kind","x","y","vaction","aaction","taction"
							,"hurtable","throwx","throwy","throwz","throwinjury","decrease" };
							a.setCpoint(extra(s, btar, 12));
						}
						std::getline(ifs, s);       //換下一行
					}
					(*Frams)[a._id] = a;
				}
			}
			ifs.close();
		}
		ifs.close();
	}

	void man::LoadBitmap() {
		loadFrame();
	}

	void man::readCommand() {
		commandList.push_back("11");
		commandList.push_back("22");
		readOtherList();
	}

	void man::readOtherList() {

	}

	void man::setInitPosotion(int x, int y) {
		_x = x;
		_z = y;
		Body.setPosetion(_x + 25, _z + 15);
	}

	// 人物狀態確認

	bool man::NearBy(const man &other) {
		area temp,temp2;
		temp.init(_x, _y, 79, 79);
		temp2.init(other._x, other._y,79,79);
		if (temp.touch(temp2)) {
			return true;
		}
		else {
			return false;
		}
	}
	
	bool man::FaceTo(const man &other) {
		if (Face_to_Left) {
			return _x > other._x;
		}
		else{
			return _x < other._x;
		}
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
		int temp = (*Frams)[_mode]._next;
		if (temp == 999) {
			if ((*Frams)[_mode]._state == 3) {
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
			default:
				break;
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
		
		//if (_mode <  5) {
		//	if (comm == 1 && Face_to_Left == false)	Face_to_Left = true;
		//	else if (comm == 2 && Face_to_Left)	Face_to_Left = false;
		//}
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
				if (first_att_animation)
					toMotion(60);
				else {
					toMotion(65);
				}
				first_att_animation = !first_att_animation;
			}
			else if (flag[4]) {
				flag[4] = false;
				rising = true;
				initG = -16;
				if (_dir[0] || _dir[1]) { JumpFront = true; }
				else { JumpFront = false; }

				if (_dir[2]) { JumpUp = true; }
				else { JumpUp = false; }

				if (_dir[3]) { JumpDown = true; }
				else { JumpDown = false; }
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
			if (flag[1] && Face_to_Left) {
				toMotion(218);
			}
			if (flag[4]) {
				initG = -11;
				if (Face_to_Left) { JumpFront = true; }
				else { JumpFront = false; }
				if (_dir[2]) { JumpUp = true; }
				else { JumpUp = false; }
				if (_dir[3]) { JumpDown = true; }
				else { JumpDown = false; }
				toMotion(213);
			}
			if (flag[5]) {
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
			break;
		}
		
		default:
			break;
		}
	}

	void man::checkbeenatt(skillsContainer &con) {
		
	}

	//人物狀態更新

	void man::OnMove() {

		int stateNow = (*Frams)[_mode]._state;
		int nextF = (*Frams)[_mode]._next;
		// 負責動作變更
		if (isTime()) {
			nextFrame();
		}
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
				_z -= 2;
			}
			if (_dir[3]) {
				_z += 2;
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

		case 3: {
			_y += initG;
			initG += 2;
			if (_y >= 0) {
				_y = 0;
				backToRandon();
			}

			if (JumpFront) {
				if (Face_to_Left) { _x -= 8; }
				else { _x += 8; }
			}
			if (JumpUp) { _z -= 3; }
			if (JumpDown) { _z += 3; }
			break;
		}
				//
		case 4: {
			if (nextF == 0) {
				_y += initG;
				initG += 2;
				if (_y >= 0) {
					_y = 0;
					backToRandon();
				}

				if (JumpFront) {
					if (Face_to_Left) { _x -= 8; }
					else { _x += 8; }
				}
				if (JumpUp) { _z -= 3; }
				if (JumpDown) { _z += 3; }
			}
			break;
		}

		case 5: {
			_y += initG;
			initG += 2;
			if (_y >= 0) {
				_y = 0;
				backToRandon();
			}
			if (JumpFront) { _x -= 15; }
			else _x += 15;
			if (JumpUp) { _z -= 4; }
			if (JumpDown) { _z += 4; }
			break;
		}

		default: {
			if (Face_to_Left)
				_x -= (*Frams)[_mode]._dvx;
			else
				_x += (*Frams)[_mode]._dvx;
			_z += (*Frams)[_mode]._dvy;

			break;
		}
		}


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
		// TRACE("%d\n", (*Frams)[_mode]._pic);
		lib->selectByNum((*Frams)[_mode]._pic, index, _x, _y + _z - (*Frams)[_mode]._centery);
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
}
