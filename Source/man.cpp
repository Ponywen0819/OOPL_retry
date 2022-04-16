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

	man::man(int x, int y) {
		charector = 0;
		_z = 0;
		_mode = 0;
		_Double_Tap_Gap = 30;
		for (int i = 0; i < 7; i++)	flag[i] = false;
		for (int i = 0; i < 4; i++)	_dir[i] = false;
		jumpAnimationGap = 0;
		initG = height;
		commandBuffer = "";
		setJumpCount();
		_outofctrl = false;
		first_att_animation = true;
		attAnimationGap = 0;
		_x = x;
		_y = y;
		now = nullptr;
		Fset = false;
		_Catch = false;
		time = 0;
	}

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

	void man::init(Bitmaplib *l,man *m,int n,CStateBar *state) {
		lib = l;
		mans = m;
		NumOfMan = n;
		Fset = false;
		_isDizzy = false;
		_Catch = false;
		_catching = false;
		_s = state;
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
					TRACE("%d\n", a._next);

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
					this->all[a._id] = a;
				}
			}
			ifs.close();
		}
		ifs.close();
	}

	void man::LoadBitmap() {
		if (TEST) {
			loadFrame();
		}
		else {
			test.LoadBitmap(".\\Bitmaps\\temp\\body.bmp");

			//站立動畫

			char *standLf[4] = { ".\\Bitmaps\\temp\\stand\\L\\0.bmp",".\\Bitmaps\\temp\\stand\\L\\1.bmp",".\\Bitmaps\\temp\\stand\\L\\2.bmp",".\\Bitmaps\\temp\\stand\\L\\3.bmp" };
			for (int i = 0; i < 4; i++)	stand[0].AddBitmap(standLf[i], RGB(0, 0, 0));
			char *standRf[4] = { ".\\Bitmaps\\temp\\stand\\R\\0.bmp",".\\Bitmaps\\temp\\stand\\R\\1.bmp",".\\Bitmaps\\temp\\stand\\R\\2.bmp",".\\Bitmaps\\temp\\stand\\R\\3.bmp" };
			for (int i = 0; i < 4; i++)	stand[1].AddBitmap(standRf[i], RGB(0, 0, 0));

			//走路動畫

			char *walkLf[6] = { ".\\Bitmaps\\temp\\walk\\L\\0.bmp",".\\Bitmaps\\temp\\walk\\L\\1.bmp",".\\Bitmaps\\temp\\walk\\L\\2.bmp",".\\Bitmaps\\temp\\walk\\L\\3.bmp",".\\Bitmaps\\temp\\walk\\L\\4.bmp",".\\Bitmaps\\temp\\walk\\L\\5.bmp" };
			for (int i = 0; i < 6; i++)	walk[0].AddBitmap(walkLf[i], RGB(0, 0, 0));
			char *walkRf[6] = { ".\\Bitmaps\\temp\\walk\\R\\0.bmp",".\\Bitmaps\\temp\\walk\\R\\1.bmp",".\\Bitmaps\\temp\\walk\\R\\2.bmp",".\\Bitmaps\\temp\\walk\\R\\3.bmp",".\\Bitmaps\\temp\\walk\\R\\4.bmp",".\\Bitmaps\\temp\\walk\\R\\5.bmp" };
			for (int i = 0; i < 6; i++)	walk[1].AddBitmap(walkRf[i], RGB(0, 0, 0));

			//跑步動作

			char *runLf[4] = { ".\\Bitmaps\\temp\\run\\L\\0.bmp",".\\Bitmaps\\temp\\run\\L\\1.bmp",".\\Bitmaps\\temp\\run\\L\\2.bmp",".\\Bitmaps\\temp\\run\\L\\3.bmp" };
			for (int i = 0; i < 4; i++)	run[0].AddBitmap(runLf[i], RGB(0, 0, 0));
			char *runRf[4] = { ".\\Bitmaps\\temp\\run\\R\\0.bmp",".\\Bitmaps\\temp\\run\\R\\1.bmp",".\\Bitmaps\\temp\\run\\R\\2.bmp",".\\Bitmaps\\temp\\run\\R\\3.bmp" };
			for (int i = 0; i < 4; i++)	run[1].AddBitmap(runRf[i], RGB(0, 0, 0));

			//跳躍蹲下動作

			squat[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\0.bmp", RGB(0, 0, 0));
			squat[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\0.bmp", RGB(0, 0, 0));

			//跳躍預備動作

			readyJump[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\1.bmp", RGB(0, 0, 0));
			readyJump[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\1.bmp", RGB(0, 0, 0));

			//小跳動作

			littleJump[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\2.bmp", RGB(0, 0, 0));
			littleJump[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\2.bmp", RGB(0, 0, 0));

			//大跳面右動作

			bigJumpR[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\6.bmp", RGB(0, 0, 0));
			bigJumpR[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\3.bmp", RGB(0, 0, 0));

			//大跳面左動作

			bigJumpL[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\3.bmp", RGB(0, 0, 0));
			bigJumpL[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\4.bmp", RGB(0, 0, 0));

			//攻擊動畫

			char *attL[4] = { ".\\Bitmaps\\temp\\att\\L\\0.bmp",".\\Bitmaps\\temp\\att\\L\\1.bmp",".\\Bitmaps\\temp\\att\\L\\2.bmp",".\\Bitmaps\\temp\\att\\L\\3.bmp" };
			for (int i = 0; i < 4; i++) att[0][i].LoadBitmap(attL[i], RGB(0, 0, 0));
			char *attR[4] = { ".\\Bitmaps\\temp\\att\\R\\0.bmp",".\\Bitmaps\\temp\\att\\R\\1.bmp",".\\Bitmaps\\temp\\att\\R\\2.bmp",".\\Bitmaps\\temp\\att\\R\\3.bmp" };
			for (int i = 0; i < 4; i++) att[1][i].LoadBitmap(attR[i], RGB(0, 0, 0));

			//衝攻動作
			char *bigattL[3] = { ".\\Bitmaps\\temp\\bigatt\\L\\0.bmp",".\\Bitmaps\\temp\\bigatt\\L\\1.bmp",".\\Bitmaps\\temp\\bigatt\\L\\2.bmp" };
			for (int i = 0; i < 3; i++) bigatt[0][i].LoadBitmap(bigattL[i], RGB(0, 0, 0));
			char *bigattR[3] = { ".\\Bitmaps\\temp\\bigatt\\R\\0.bmp",".\\Bitmaps\\temp\\bigatt\\R\\1.bmp",".\\Bitmaps\\temp\\bigatt\\R\\2.bmp" };
			for (int i = 0; i < 3; i++) bigatt[1][i].LoadBitmap(bigattR[i], RGB(0, 0, 0));

			//踢動作

			char *kickL[2] = { ".\\Bitmaps\\temp\\kick\\L\\0.bmp",".\\Bitmaps\\temp\\kick\\L\\1.bmp" };
			for (int i = 0; i < 2; i++) kick[0][i].LoadBitmap(kickL[i], RGB(0, 0, 0));
			char *kickR[2] = { ".\\Bitmaps\\temp\\kick\\R\\0.bmp",".\\Bitmaps\\temp\\kick\\R\\1.bmp" };
			for (int i = 0; i < 2; i++) kick[1][i].LoadBitmap(kickR[i], RGB(0, 0, 0));

			// 飛踢動作

			char *flykickL[2] = { ".\\Bitmaps\\temp\\kick\\L\\2.bmp",".\\Bitmaps\\temp\\kick\\L\\3.bmp" };
			for (int i = 0; i < 2; i++) flykick[0][i].LoadBitmap(flykickL[i], RGB(0, 0, 0));
			char *flykickR[2] = { ".\\Bitmaps\\temp\\kick\\R\\2.bmp",".\\Bitmaps\\temp\\kick\\R\\3.bmp" };
			for (int i = 0; i < 2; i++) flykick[1][i].LoadBitmap(flykickR[i], RGB(0, 0, 0));

			//讀取個別腳色技能表

			readCommand();
		}
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
		_y = y;
		Body.setPosetion(_x + 25, _y + 15);
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
	//這是留給子類別操控的func

	void man::otherCommand(int n) {

	}

	// 狀態更新函示

	void man::backToRandon() {
		inMotion = false;
		_mode = 0;
		setTimmer(all[_mode]._wait);
	}

	void man::toMotion(int f) {
		_mode = f;
		inMotion = true;
		setTimmer(all[_mode]._wait);
	}

	void man::nextFrame() {
		//TRACE("next : %d pic : %d\n", all[_mode]._next, all[_mode]._pic);
		int temp = all[_mode]._next;
		if (temp == 999) {
			backToRandon();
		}
		else if(temp != 0){
			_mode = temp;
			setTimmer(all[_mode]._wait);
		}
		else{

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

		if (comm == 5) {
			commandBuffer += '5';
		}

        if (comm == 6) {
			commandBuffer += '6';
		}

		if (comm == 7) {
			commandBuffer += '7';
		}
		
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
		if (TEST) {
			if (inMotion) {
				this->specialEvent();
			}
			else{
				if (flag[0]) {
					_dir[0] = true;
					_dir[1] = false;
				}
				else if (flag[1]) {
					_dir[0] = false;
					_dir[1] = true;
				}
				else{
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
					if(all[_mode]._state == 1)
						backToRandon();
				}
				else {
					if (all[_mode]._state == 0) {
						_mode = 5;
						setTimmer(3);
					}
				}
			}
		}
		else{

			if (_outofctrl) return;
			if (_isDizzy) return;
			if (_Catch) return;

			if (flag[0]) {
				if (_mode == 100) {
					if (!Face_to_Left) _mode = 0;
				}
				else if (_mode == 120 || _mode == 121) {
					if (!Face_to_Left) {
						gotCatch->_mode = 133;
						gotCatch->_Catch = false;
						setTimmer(9);
						_catching = false;
						_mode = 0;
					}
				}
				else if (_mode != 100) {
					bool finish = false;
					for (int i = 0; i < NumOfMan; i++) {
						//TRACE("qwe %d %d\n", NearBy(*(mans + i)), (mans + i)->isDizzy());
						if (NearBy(*(mans + i)) && (mans + i)->isDizzy()) {
							gotCatch = (mans + i);
							gotCatch->_mode = 131;
							gotCatch->_isDizzy = false;
							gotCatch->_Catch = true;
							gotCatch->Face_to_Left = !Face_to_Left;
							if (Face_to_Left) {
								gotCatch->_x = _x - 29;
							}
							else {
								gotCatch->_x = _x + 29;
							}
							_mode = 120;
							setTimmer(15);
							finish = true;
							_catching = true;
							setDizzyCount();
							break;
						}
					}
					if (!finish) {
						Face_to_Left = true;
						_dir[0] = true;
						_dir[1] = false;
					}
				}
			}

			if (flag[1]) {
				if (_mode == 100) {
					if (Face_to_Left) {
						_mode = 0;
					}
				}
				else if (_mode == 120 || _mode == 121) {
					if (Face_to_Left) {
						gotCatch->_mode = 133;
						gotCatch->_Catch = false;
						setTimmer(9);
						_catching = false;
						_mode = 0;
					}
				}
				else if (_mode != 100) {
					bool finish = false;
					for (int i = 0; i < NumOfMan; i++) {
						//TRACE("qwe %d %d\n", NearBy(*(mans + i)) , (mans + i)->isDizzy());
						if (NearBy(*(mans + i)) && (mans + i)->isDizzy()) {
							gotCatch = (mans + i);
							gotCatch->_mode = 131;
							gotCatch->_isDizzy = false;
							if (Face_to_Left) {
								gotCatch->_x = _x - 29;
							}
							else {
								gotCatch->_x = _x + 29;
							}
							gotCatch->Face_to_Left = !Face_to_Left;
							_mode = 120;
							setTimmer(15);
							finish = true;
							_catching = true;
							setDizzyCount();
							break;
						}
					}
					if (!finish) {
						Face_to_Left = false;
						_dir[0] = false;
						_dir[1] = true;
					}
				}
			}

			if (!(flag[0] || flag[1])) {
				if (_mode != 100)
					_dir[0] = _dir[1] = false;
			}

			if (flag[2]) {
				_dir[2] = true;
				_dir[3] = false;
			}

			if (flag[3]) {
				_dir[2] = false;
				_dir[3] = true;
			}

			if (!(flag[3] || flag[2])) {
				_dir[3] = _dir[2] = false;
			}

			if (flag[4]) {
				flag[4] = false;
				_mode = 210;
				setTimmer(3);
				jumpType = (_mode == 0);

				_outofctrl = true;
			}

			if (flag[5]) {
				flag[5] = false;
				if (_mode == 100) {
					_mode = 103;
					_outofctrl = true;
					_dir[2] = _dir[3] = false;
					setattCount();
				}
				else if (_mode == 120 || _mode == 121) {
					_mode = 122;
					gotCatch->_mode = 130;
					setTimmer(15);
				}
				else if (_mode == 122 || _mode == 123) {

				}
				else {
					bool finish = false;
					for (int i = 0; i < NumOfMan; i++) {
						if (NearBy(*(mans + i)) && FaceTo(*(mans + i)) && (mans + i)->isDizzy()) {
							setTimmer(10);
							finish = true;
							_outofctrl = true;
							_mode = 70;
							break;
						}
					}
					if (!finish) {
						if (first_att_animation) {
							_mode = 60;
						}
						else {
							_mode = 65;
						}
						_mode = 101;
						_outofctrl = true;
						first_att_animation = !first_att_animation;
						setattCount();
					}
				}
			}

			if (_mode <= 8) {
				bool temp = false;
				for (int i = 0; i < 4; i++) {
					if (flag[i]) {
						if (_mode < 5) {
							_mode = 5;
							setTimmer(9);
							walk_Ani_dir = true;
						}
						temp = true;
						break;
					}
				}
				if (!temp) {
					if (_mode > 3) {
						_mode = 0;
						setTimmer(9);
					}
					for (int i = 0; i < 4; i++) _dir[i] = false;
				}
			}
		}
	}

	void man::checkBuff() {
		if (_outofctrl) return;
		if (_isDizzy) return;
		if (_Catch) return;
		if (_catching) return;

		if (_Double_Tap_Gap <= 0) {
			setCountDwon();
			commandBuffer = "";
		}
		else{
			int index = 0;
			std::vector<std::string>::iterator i;
			for (i = commandList.begin(); i != commandList.end(); ++i) {
				if (*i == commandBuffer) break;
				index++;
			}
			if (index != commandList.size()) {
				commandBuffer = "";
				if (index == 0 || index == 1) {
					_mode = 9;
					_outofctrl = true;
					run_Ani_dir = true;
				}
				else{
					otherCommand(index);
				}
			}
		}

	}

	void man::specialEvent() {
		if (!_outofctrl) return;
		if (_isDizzy) return;
		if (_Catch) return;
		if (_catching) return;

		if (flag[0]) {
			// 跑步模式
			if (_mode > 8 && _mode < 12) {				
				if (!Face_to_Left) {
					_mode = 218;
					setTimmer(15);
				}
			}

			// 大跳中
			if (_mode == 213) {
				if (!Face_to_Left) {
					Face_to_Left = !Face_to_Left;
					_mode = 214;
				}
			}
			else if (_mode == 214) {
				if (!Face_to_Left) {
					Face_to_Left = !Face_to_Left;
					_mode = 213;
				}
			}

		}
		if (flag[1]) {
			// 跑步模式
			if (_mode > 8 && _mode < 12) {
				if (Face_to_Left) {
					_mode = 218;
					setTimmer(15);
				}
			}

			// 大跳中
			if (_mode == 213) {
				if (Face_to_Left) {
					Face_to_Left = !Face_to_Left;
					_mode = 214;
				}
			}
			else if (_mode == 214) {
				if (Face_to_Left) {
					Face_to_Left = !Face_to_Left;
					_mode = 213;
				}
			}
		}
		if (flag[4]) {
			if (_mode > 8 && _mode < 12) {
				_mode = 213;
				setTimmer(24);
				if (flag[2]) {
					if (Face_to_Left) caculateZ(33, -270, -60, -55);
					else caculateZ(33, 270, -60, -55);
				}
				else if (flag[3]) {
					if (Face_to_Left) caculateZ(33, -270, 60, -55);
					else caculateZ(33, 270, 60, -55);
				}
				else {
					if (Face_to_Left) caculateZ(33, -165, 0, -55);
					else caculateZ(33, 165, 0, -55);
				}
			}
		}
		if (flag[5]) {
			if (_mode > 8 && _mode < 12) {
				_mode = 85;
				setTimmer(15);
			}
			if (_mode == 213) {
				_mode = 90;
				setTimmer(9);
			}
		}
	}

	void man::checkbeenatt(skillsContainer &con) {
		int j = 0;
		while(j < con.getnum()) {
			if (con.getskills(j)->getowner() == this) {
				j++; continue;
			}
			if (con.getskills(j)->touch(Body)) {
				Skills* temp = con.getskills(j);
				stonkcount -= temp->getdizzy();	
				_outofctrl = true;
				if (stonkcount > 3) {
					_mode = 220;
					setTimmer(6);
				}
				else if (stonkcount > 0) {
					if(temp->getDir() != Face_to_Left){
						_mode = 222;
						setTimmer(6);
					}
					else{
						_mode = 224;
						setTimmer(6);
					}
				}
				else if(stonkcount == 0){
					_isDizzy = true;
					_mode = 226;							
					setTimmer(18);
				}
				else{
					_isDizzy = false;
					setTimmer(9);
					if (temp->getDir()) {
						_mode = 180;				// 擊飛左
					}
					else{
						_mode = 186;				// 擊飛右
					}
				}
				con.dleteSkills(j);
			}		
			j++;
		}
	}

	void man::caculateZ(int f, int x,int y, int z) {
		tempf = f;
		float temp = float(f) / 2;
		a1 =- z / (temp*temp);
		a2 = temp;
		a3 = float(z);
		a4 = float(x) / f;
		a5 = float(y) / f;
		FrameCount = 0;
		_z = 0;
		tempx = float(_x);
		tempy = float(_y);
		//TRACE("init %f %f %f", a1, a2, a3);
		Fset = true;
	}

	void man::setZ() {
		if (Fset) {
			FrameCount++;
			_z = int(a1 * ((FrameCount - a2) *(FrameCount - a2)) + a3);
			_x = int(tempx + a4);
			tempx += a4;
			_y = int(tempy + a5);
			tempy += a5;
			//TRACE("%d %f\n", _z, FrameCount);
			if (FrameCount == (2*a2)) Fset = false;
		}
	}

	Skills* man::usingSkill(){
		return now;
	}

	//人物狀態更新

	void man::OnMove() {
		//TRACE("dizzy %d  %d \n", stonkcount, recoverGap);
		//倒數
		if (TEST) {
			checkFlag();

			Count();
			int stateNow = all[_mode]._state;
			switch (stateNow){
			// 站立狀態
			case 0: {
				if (isTime()) {
					nextFrame();
				}
				break;
			}
			// 走路狀態
			case 1: {
				if (isTime()) {
					if (walk_Ani_dir) {
						if (++_mode == 9) {
							_mode = 7;
							walk_Ani_dir = !walk_Ani_dir;
						}
					}
					else{
						if (--_mode == 4) {
							_mode = 6;
							walk_Ani_dir = !walk_Ani_dir;
						}
					}
					
					setTimmer(3);
				}
				else{
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
				}
				break;
			}
			default:
				break;
			}
		}
		else {
			now = nullptr;
			if (_Double_Tap_Gap >= 0) _Double_Tap_Gap--;
			Count();

			JumpCount();
			attCount();
			beattenCount();
			recoverCount();

			//查看按鍵與輸入指令
			checkFlag();
			checkBuff();
			specialEvent();

			setZ();
			switch (_mode) {

				// 站立

			case 0: {
				if (isTime()) {
					_mode = 1;
					setTimmer(9);
				}
				break;
			}
			case 1: {
				if (isTime()) {
					_mode = 2;
					setTimmer(9);
				}
				break;
			}
			case 2: {
				if (isTime()) {
					_mode = 3;
					setTimmer(9);
				}
				break;
			}
			case 3: {
				if (isTime()) {
					_mode = 0;
					setTimmer(9);
				}
				break;
			}

					// 走路

			case 5: {
				setPosotion(1);
				if (isTime()) {
					_mode = 6;
					walk_Ani_dir = !walk_Ani_dir;
					setTimmer(9);
				}
				break;
			}
			case 6: {
				setPosotion(1);
				if (isTime()) {
					if (walk_Ani_dir) _mode = 7;
					else _mode = 5;
					setTimmer(9);
				}
				break;
			}
			case 7: {
				setPosotion(1);
				if (isTime()) {
					if (walk_Ani_dir) _mode = 8;
					else _mode = 6;
					setTimmer(9);
				}
				break;
			}
			case 8: {
				setPosotion(1);
				if (isTime()) {
					_mode = 7;
					walk_Ani_dir = !walk_Ani_dir;
					setTimmer(9);
				}
				break;
			}

					// 跑步

			case 9: {
				setPosotion(3);
				if (isTime()) {
					_mode = 10;
					run_Ani_dir = !run_Ani_dir;
					setTimmer(9);
				}
				break;
			}
			case 10: {
				setPosotion(3);
				if (isTime()) {
					if (run_Ani_dir)	_mode = 11;
					else _mode = 9;
					setTimmer(9);
				}
				break;
			}
			case 11: {
				setPosotion(3);
				if (isTime()) {
					_mode = 10;
					run_Ani_dir = !run_Ani_dir;
					setTimmer(9);
				}
				break;
			}

					 // 拿重物走路

			case 12: {
				break;
			}
			case 13: {
				break;
			}
			case 14: {
				break;
			}
			case 15: {
				break;
			}

					 // 拿重物跑步

			case 16: {
				break;
			}
			case 17: {
				break;
			}
			case 18: {
				break;
			}

					 // 拿重物跑步停止

			case 19: {
				break;
			}

					 // 普通武器攻擊

			case 20: {
				break;
			}
			case 21: {
				break;
			}
			case 22: {
				break;
			}
			case 23: {
				break;
			}

			case 25: {
				break;
			}
			case 26: {
				break;
			}
			case 27: {
				break;
			}
			case 28: {
				break;
			}

					 // 跳躍武器攻擊

			case 30: {
				break;
			}
			case 31: {
				break;
			}

					 // 拿武器跑步

			case 35: {
				break;
			}
			case 36: {
				break;
			}
			case 37: {
				break;
			}

					 // 武器衝攻

			case 40: {
				break;
			}
			case 41: {
				break;
			}

					 // 丟輕武器

			case 45: {
				break;
			}
			case 46: {
				break;
			}
			case 47: {
				break;
			}

					 // 丟重武器

			case 50: {
				break;
			}
			case 51: {
				break;
			}

					 // 跳時丟出輕武器

			case 52: {
				break;
			}
			case 53: {
				break;
			}
			case 54: {
				break;
			}

					 // 喝東西 

			case 55: {
				break;
			}
			case 56: {
				break;
			}
			case 57: {
				break;
			}
			case 58: {
				break;
			}

					 // 普通攻擊

			case 60: {
				if (isTime()) {
					setTimmer(9);
					_mode = 61;
					punch *temp = new punch(_x, _y, _z, Face_to_Left, true, lib, (void*)this);
					temp->setdizzy(2);
					temp->init(Face_to_Left);
					now = temp;
				}
				break;
			}
			case 61: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

			case 65: {
				if (isTime()) {
					setTimmer(9);
					_mode = 66;
					punch *temp = new punch(_x, _y, _z, Face_to_Left, false, lib, (void*)this);
					temp->setdizzy(2);
					temp->init(Face_to_Left);
					now = temp;
				}
				break;
			}
			case 66: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					 // 終結季

			case 70: {
				if (Face_to_Left) setInitPosotion(_x - 1, _y);
				else setInitPosotion(_x + 1, _y);
				if (isTime()) {
					setTimmer(6);
					_mode = 71;
				}
				break;
			}
			case 71: {
				if (Face_to_Left) setInitPosotion(_x - 1, _y);
				else setInitPosotion(_x + 1, _y);

				if (isTime()) {
					setTimmer(12);
					_mode = 72;
					super_att *temp = new super_att(_x, _y, _z, !Face_to_Left, (void*)this);
					temp->setdizzy(7);
					temp->init(Face_to_Left);
					now = temp;
				}
				break;
			}
			case 72: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					 //  衝攻

			case 85: {
				if (isTime()) {
					_mode = 86;
					setTimmer(15);
				}
				break;
			}
			case 86: {
				if (isTime()) {
					_mode = 87;
					setTimmer(9);
				}
				// 這裡放技能

				break;
			}
			case 87: {
				if (isTime()) {
					_mode = 0;
					walk_Ani_dir = true;
					_outofctrl = false;
				}
				break;
			}

					 // 衝跳攻

			case 90: {
				if (isTime()) {
					_mode = 91;
					// 這裡放技能
				}
				if (!Fset) {
					_mode = 0;
					walk_Ani_dir = true;
					_outofctrl = false;
				}
			}
			case 91: {
				if (!Fset) {
					_mode = 0;
					walk_Ani_dir = true;
					_outofctrl = false;
				}
			}

			case 100: {						//衝刺動作
				setPosotion(2);
				break;
			}
			case 101: {
				if (attCountisZero()) {		// 準備攻擊
					_mode = 102;
					setattCount();
					punch *temp = new punch(_x, _y, _z, Face_to_Left, first_att_animation, lib, (void*)this);
					temp->setdizzy(2);
					temp->init(Face_to_Left);
					now = temp;
				}
				break;
			}
			case 102: {
				if (attCountisZero()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}
			case 103: {
				setPosotion(2);
				if (attCountisZero()) {
					_mode = 104;
					setattCount();
				}
				break;
			}
			case 104: {
				setPosotion(2);
				if (attCountisZero()) {
					_mode = 105;
					setattCount();
				}
				break;
			}
			case 105: {
				setPosotion(2);
				if (attCountisZero()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}
			case 106: {
				if (attCountisZero()) {
					_mode = 107;
					setattCount();
				}
				setPosotion(2);
				if (jumping()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}
			case 107: {
				if (attCountisZero()) {
					_mode = 92;
				}
				setPosotion(2);
				if (jumping()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					  // 飛踢

			case 108: {
				if (attCountisZero()) {
					_mode = 110;
					setattCount();
				}
				setPosotion(4);
				if (jumping()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}
			case 109: {
				if (attCountisZero()) {
					_mode = 111;
					setattCount();
				}
				setPosotion(4);
				if (jumping()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}
			case 110: {
				setPosotion(4);
				if (jumping()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}
			case 111: {
				setPosotion(4);
				if (jumping()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					  // 捉住人的動作

			case 120: {
				dizzyCount -= -7;
				if (isTime()) {
					gotCatch->_mode = 130;
					_mode = 121;
				}
				break;
			}
			case 121: {
				dizzyCount -= 7;
				if (dizzyCount <= 0) {
					gotCatch->_mode = 133;
					gotCatch->_Catch = false;
					setTimmer(9);
					_catching = false;
					_mode = 0;
				}
				break;
			}


					  // 捉住人攻擊

			case 122: {
				dizzyCount -= 7;
				if (isTime()) {
					gotCatch->_mode = 132;
					_mode = 123;
					setTimmer(9);
				}
				break;
			}
			case 123: {
				dizzyCount -= 3;
				if (isTime()) {
					_mode = 121;
					// 補上受傷
				}
				break;
			}
					  // 被捉住

			case 130: {
				break;
			}
			case 131: {
				break;
			}
			case 132: {
				break;
			}

					  // 被捉結束

			case 133: {
				if (isTime()) {
					setTimmer(9);
					_mode = 134;
				}
				break;
			}
			case 134: {
				if (isTime()) {
					setTimmer(9);
					_mode = 135;
				}
				break;
			}
			case 135: {
				if (isTime()) {
					setTimmer(9);
					_mode = 136;
				}
				break;
			}
			case 136: {
				if (isTime()) {
					setTimmer(9);
					_mode = 137;
				}
				break;
			}
			case 137: {
				if (isTime()) {
					setTimmer(9);
					_mode = 138;
				}
				break;
			}
			case 138: {
				if (isTime()) {
					setTimmer(90);
					_mode = 230;
				}
				break;
			}
			case 139: {
				if (isTime()) {
					setTimmer(9);
					_mode = 140;
				}
				break;
			}
			case 140: {
				if (isTime()) {
					setTimmer(9);
					_mode = 141;
				}
				break;
			}
			case 141: {
				if (isTime()) {
					setTimmer(9);
					_mode = 142;
				}
				break;
			}
			case 142: {
				if (isTime()) {
					setTimmer(9);
					_mode = 143;
				}
				break;
			}
			case 143: {
				if (isTime()) {
					setTimmer(9);
					_mode = 144;
				}
				break;
			}
			case 144: {
				if (isTime()) {
					setTimmer(90);
					_mode = 231;
					break;
				}
			}

					  // 正面飛走

			case 180: {
				if (isTime()) {
					caculateZ(45, -50, 0, -12);
					setTimmer(9);
					_mode = 181;
				}
				break;
			}
			case 181: {
				if (isTime()) {
					setTimmer(9);
					_mode = 182;
				}
				break;
			}
			case 182: {
				if (isTime()) {
					setTimmer(9);
					_mode = 183;
				}
				break;
			}
			case 183: {
				if (isTime()) {
					setTimmer(9);
					_mode = 184;
				}
				break;
			}
			case 184: {
				if (isTime()) {
					setTimmer(9);
					_mode = 185;
				}
				break;
			}
			case 185: {
				if (isTime()) {
					setTimmer(90);
					_mode = 230;
				}
				break;
			}

					  // 背後擊飛

			case 186: {
				if (isTime()) {
					caculateZ(45, 50, 0, -12);
					setTimmer(9);
					_mode = 187;
				}
				break;
			}
			case 187: {
				setZ();
				if (isTime()) {
					setTimmer(9);
					_mode = 188;
				}
				break;
			}
			case 188: {
				setZ();
				if (isTime()) {
					setTimmer(9);
					_mode = 189;
				}
				break;
			}
			case 189: {
				setZ();
				if (isTime()) {
					setTimmer(9);
					_mode = 190;
				}
				break;
			}
			case 190: {
				setZ();
				if (isTime()) {
					setTimmer(9);
					_mode = 191;
				}
				break;
			}
			case 191: {
				setZ();
				if (isTime()) {
					setTimmer(90);
					_mode = 231;
				}
				break;
			}

					  // 跳躍

			case 210: {
				if (isTime()) {
					setTimmer(3);
					_mode = 211;
				}
				break;
			}
			case 211: {
				if (isTime()) {
					setTimmer(3);
					_mode = 212;
					if (Face_to_Left) {
						if (jumpType) {
							if (flag[2]) {
								caculateZ(40, -144, -40, -80);
							}
							else if (flag[3]) {
								caculateZ(40, -144, 40, -80);
							}
							else
							{
								caculateZ(40, -144, 0, -80);
							}
						}
						else
							caculateZ(40, 0, 0, -80);
					}
					else {
						if (jumpType)
							caculateZ(40, 144, 0, -80);
						else
							caculateZ(40, 0, 0, -80);
					}
				}
				break;
			}
			case 212: {
				if (!Fset) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					  // 衝跳

			case 213: {
				if (isTime()) {
					_mode = 216;
					setTimmer(6);
				}
				break;
			}
			case 214: {
				if (isTime()) {
					_mode = 217;
					setTimmer(6);
				}
				break;
			}

			case 216: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}
			case 217: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					  // 停止跑步

			case 218: {
				if (isTime()) {
					_mode = 0;
					walk_Ani_dir = true;
					_outofctrl = false;
				}
				break;
			}

					  // 打到向後退的動作

			case 220: {
				if (isTime()) {
					setTimmer(9);
					_mode = 221;
				}
				break;
			}
			case 221: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					  // 打到向前移的動作

			case 222: {
				if (isTime()) {
					setTimmer(9);
					_mode = 223;
				}
				break;
			}
			case 223: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					  // 打到第二個動作

			case 224: {
				if (isTime()) {
					setTimmer(9);
					_mode = 225;
				}
				break;
			}
			case 225: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					  // 暈眩

			case 226: {
				if (isTime()) {
					setTimmer(18);
					_mode = 227;
				}
				break;
			}
			case 227: {
				if (isTime()) {
					setTimmer(18);
					_mode = 228;
				}
				break;
			}
			case 228: {
				if (isTime()) {
					setTimmer(18);
					_mode = 229;
				}
				break;
			}
			case 229: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
					_isDizzy = false;
				}
				break;
			}

					  // 躺著倒地

			case 230: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}

					  // 趴著倒地

			case 231: {
				if (isTime()) {
					_mode = 0;
					_outofctrl = false;
				}
				break;
			}


			default:
				break;
			}
			Body.setPosetion(_x + 25, _y + 15);
		}
	}
	
	//人物顯示

	void man::onShow() {
		if (TEST) {
			int index;
			if (Face_to_Left) index = 0;
			else index = 1;
			TRACE("%d\n", all[_mode]._pic);
			lib->selectByNum(all[_mode]._pic, index, _x, _y + _z);
		}
		else {
			int index;
			if (Face_to_Left) index = 0;
			else index = 1;
			switch (_mode) {

				// 站立

			case 0: {
				lib->selectByNum(0, index, _x, _y + _z);
				break;
			}
			case 1: {
				lib->selectByNum(1, index, _x, _y + _z);
				break;
			}
			case 2: {
				lib->selectByNum(2, index, _x, _y + _z);
				break;
			}
			case 3: {
				lib->selectByNum(3, index, _x, _y + _z);
				break;
			}

					// 走路

			case 5: {
				lib->selectByNum(4, index, _x, _y + _z);
				break;
			}
			case 6: {
				lib->selectByNum(5, index, _x, _y + _z);
				break;
			}
			case 7: {
				lib->selectByNum(6, index, _x, _y + _z);
				break;
			}
			case 8: {
				lib->selectByNum(7, index, _x, _y + _z);
				break;
			}

					// 跑步

			case 9: {
				lib->selectByNum(20, index, _x, _y + _z);
				break;
			}
			case 10: {
				lib->selectByNum(21, index, _x, _y + _z);
				break;
			}
			case 11: {
				lib->selectByNum(22, index, _x, _y + _z);
				break;
			}

					 // 拿重物走路

			case 12: {
				lib->selectByNum(23, index, _x, _y + _z);
				break;
			}
			case 13: {
				lib->selectByNum(24, index, _x, _y + _z);
				break;
			}
			case 14: {
				lib->selectByNum(25, index, _x, _y + _z);
				break;
			}
			case 15: {
				lib->selectByNum(26, index, _x, _y + _z);
				break;
			}

					 // 拿重物跑步

			case 16: {
				lib->selectByNum(125, index, _x, _y + _z);
				break;
			}
			case 17: {
				lib->selectByNum(126, index, _x, _y + _z);
				break;
			}
			case 18: {
				lib->selectByNum(127, index, _x, _y + _z);
				break;
			}

					 // 拿重物跑步停止

			case 19: {
				lib->selectByNum(128, index, _x, _y + _z);
				break;
			}

					 // 普通武器攻擊

			case 20: {
				lib->selectByNum(70, index, _x, _y + _z);
				break;
			}
			case 21: {
				lib->selectByNum(71, index, _x, _y + _z);
				break;
			}
			case 22: {
				lib->selectByNum(72, index, _x, _y + _z);
				break;
			}
			case 23: {
				lib->selectByNum(73, index, _x, _y + _z);
				break;
			}

			case 25: {
				lib->selectByNum(74, index, _x, _y + _z);
				break;
			}
			case 26: {
				lib->selectByNum(75, index, _x, _y + _z);
				break;
			}
			case 27: {
				lib->selectByNum(76, index, _x, _y + _z);
				break;
			}
			case 28: {
				lib->selectByNum(77, index, _x, _y + _z);
				break;
			}

					 // 跳躍武器攻擊

			case 30: {
				lib->selectByNum(80, index, _x, _y + _z);
				break;
			}
			case 31: {
				lib->selectByNum(81, index, _x, _y + _z);
				break;
			}

					 // 拿武器跑步

			case 35: {
				lib->selectByNum(84, index, _x, _y + _z);
				break;
			}
			case 36: {
				lib->selectByNum(85, index, _x, _y + _z);
				break;
			}
			case 37: {
				lib->selectByNum(86, index, _x, _y + _z);
				break;
			}

					 // 武器衝攻

			case 40: {
				lib->selectByNum(90, index, _x, _y + _z);
				break;
			}
			case 41: {
				lib->selectByNum(92, index, _x, _y + _z);
				break;
			}

					 // 丟輕武器

			case 45: {
				lib->selectByNum(94, index, _x, _y + _z);
				break;
			}
			case 46: {
				lib->selectByNum(95, index, _x, _y + _z);
				break;
			}
			case 47: {
				lib->selectByNum(96, index, _x, _y + _z);
				break;
			}

					 // 丟重武器

			case 50: {
				lib->selectByNum(27, index, _x, _y + _z);
				break;
			}
			case 51: {
				lib->selectByNum(28, index, _x, _y + _z);
				break;
			}

					 // 跳時丟出輕武器

			case 52: {
				lib->selectByNum(97, index, _x, _y + _z);
				break;
			}
			case 53: {
				lib->selectByNum(98, index, _x, _y + _z);
				break;
			}
			case 54: {
				lib->selectByNum(99, index, _x, _y + _z);
				break;
			}

					 // 喝東西 

			case 55: {
				lib->selectByNum(132, index, _x, _y + _z);
				break;
			}
			case 56: {
				lib->selectByNum(133, index, _x, _y + _z);
				break;
			}
			case 57: {
				lib->selectByNum(134, index, _x, _y + _z);
				break;
			}
			case 58: {
				lib->selectByNum(133, index, _x, _y + _z);
				break;
			}

					 // 普通攻擊

			case 60: {
				lib->selectByNum(10, index, _x, _y + _z);
				break;
			}
			case 61: {
				lib->selectByNum(11, index, _x, _y + _z);
				break;
			}

			case 65: {
				lib->selectByNum(12, index, _x, _y + _z);
				break;
			}
			case 66: {
				lib->selectByNum(13, index, _x, _y + _z);
				break;
			}

					 // 終結季

			case 70: {
				lib->selectByNum(37, index, _x, _y + _z);
				break;
			}
			case 71: {
				lib->selectByNum(38, index, _x, _y + _z);
				break;
			}
			case 72: {
				lib->selectByNum(39, index, _x, _y + _z);
				break;
			}

					 // 跳攻擊

			case 80: {
				lib->selectByNum(14, index, _x, _y + _z);
				break;
			}
			case 81: {
				lib->selectByNum(15, index, _x, _y + _z);
				break;
			}

					 // 衝攻

			case 85: {
				lib->selectByNum(102, index, _x, _y + _z);
				break;
			}
			case 86: {
				lib->selectByNum(103, index, _x, _y + _z);
				break;
			}
			case 87: {
				lib->selectByNum(104, index, _x, _y + _z);
				break;
			}

					 // 跑跳攻擊

			case 90: {
				lib->selectByNum(106, index, _x, _y + _z);
				break;
			}
			case 91: {
				lib->selectByNum(107, index, _x, _y + _z);
				break;
			}


			case 92:									//跳躍小跳
				littleJump[index].SetTopLeft(_x, _y + _z);
				littleJump[index].ShowBitmap();
				break;
			case 93:									//跳躍大跳面右
				bigJumpR[index].SetTopLeft(_x, _y + _z);
				bigJumpR[index].ShowBitmap();
				break;
			case 94:									//跳躍大跳面左
				bigJumpL[index].SetTopLeft(_x, _y + _z);
				bigJumpL[index].ShowBitmap();
				break;
			case 100:									//奔跑
				run[index].OnMove();
				run[index].SetTopLeft(_x, _y + _z);
				run[index].OnShow();
				break;
			case 101:									//攻擊動作預備
				if (first_att_animation) {
					att[index][0].SetTopLeft(_x, _y + _z);
					att[index][0].ShowBitmap();
				}
				else {
					att[index][2].SetTopLeft(_x, _y + _z);
					att[index][2].ShowBitmap();
				}
				break;
			case 102:									//攻擊動作
				if (first_att_animation) {
					att[index][1].SetTopLeft(_x, _y + _z);
					att[index][1].ShowBitmap();
				}
				else {
					att[index][3].SetTopLeft(_x, _y + _z);
					att[index][3].ShowBitmap();
				}
				break;
			case 103:									//衝攻準備動作
				bigatt[index][0].SetTopLeft(_x, _y + _z);
				bigatt[index][0].ShowBitmap();
				break;
			case 104:									//衝攻動作
				bigatt[index][1].SetTopLeft(_x, _y + _z);
				bigatt[index][1].ShowBitmap();
				break;
			case 105:									//衝攻end動作
				bigatt[index][2].SetTopLeft(_x, _y + _z);
				bigatt[index][2].ShowBitmap();
				break;
			case 106:
				kick[index][0].SetTopLeft(_x, _y + _z);
				kick[index][0].ShowBitmap();
				break;
			case 107:
				kick[index][1].SetTopLeft(_x, _y + _z);
				kick[index][1].ShowBitmap();
				break;
			case 108:
			case 109:
				flykick[index][0].SetTopLeft(_x, _y + _z);
				flykick[index][0].ShowBitmap();
				break;
			case 110:
			case 111:
				flykick[index][1].SetTopLeft(_x, _y + _z);
				flykick[index][1].ShowBitmap();
				// 捉住人的動作

			case 120: {
				lib->selectByNum(135, index, _x, _y + _z);
				break;
			}
			case 121: {
				lib->selectByNum(50, index, _x, _y + _z);
				break;
			}

					  // 捉住人攻擊

			case 122: {
				lib->selectByNum(51, index, _x, _y + _z);
				break;
			}
			case 123: {
				lib->selectByNum(52, index, _x, _y + _z);
				break;
			}

					  // 被捉住

			case 130: {
				lib->selectByNum(53, index, _x, _y + _z);
				break;
			}
			case 131: {
				lib->selectByNum(54, index, _x, _y + _z);
				break;
			}

					  // 被捉住打

			case 132: {
				lib->selectByNum(55, index, _x, _y + _z);
				break;
			}
			case 133: {
				lib->selectByNum(30, index, _x, _y + _z);
				break;
			}
			case 134: {
				lib->selectByNum(31, index, _x, _y + _z);
				break;
			}
			case 135: {
				lib->selectByNum(32, index, _x, _y + _z);
				break;
			}
			case 136: {
				lib->selectByNum(33, index, _x, _y + _z);
				break;
			}
			case 137: {
				lib->selectByNum(34, index, _x, _y + _z);
				break;
			}
			case 138: {
				lib->selectByNum(35, index, _x, _y + _z);
				break;
			}
			case 139: {
				lib->selectByNum(40, index, _x, _y + _z);
				break;
			}
			case 140: {
				lib->selectByNum(41, index, _x, _y + _z);
				break;
			}
			case 141: {
				lib->selectByNum(42, index, _x, _y + _z);
				break;
			}
			case 142: {
				lib->selectByNum(43, index, _x, _y + _z);
				break;
			}
			case 143: {
				lib->selectByNum(44, index, _x, _y + _z);
				break;
			}
			case 144: {
				lib->selectByNum(45, index, _x, _y + _z);
				break;
			}

					  // falling

			case 180: {
				lib->Falling(0, index, 0, _x, _y + _z);
				break;
			}
			case 181: {
				lib->Falling(0, index, 1, _x, _y + _z);
				break;
			}
			case 182: {
				lib->Falling(0, index, 2, _x, _y + _z);
				break;
			}
			case 183: {
				lib->Falling(0, index, 3, _x, _y + _z);
				break;
			}
			case 184: {
				lib->Falling(0, index, 4, _x, _y + _z);
				break;
			}
			case 185: {
				lib->Falling(0, index, 5, _x, _y + _z);
				break;
			}

					  // 背後擊飛

			case 186: {
				lib->Falling(1, index, 0, _x, _y + _z);
				break;
			}
			case 187: {
				lib->Falling(1, index, 1, _x, _y + _z);
				break;
			}
			case 188: {
				lib->Falling(1, index, 2, _x, _y + _z);
				break;
			}
			case 189: {
				lib->Falling(1, index, 3, _x, _y + _z);
				break;
			}
			case 190: {
				lib->Falling(1, index, 5, _x, _y + _z);
				break;
			}
			case 191: {
				lib->Falling(1, index, 4, _x, _y + _z);
				break;
			}

					  // 跳躍

			case 210: {
				lib->selectByNum(60, index, _x, _y + _z);
				break;
			}
			case 211: {
				lib->selectByNum(61, index, _x, _y + _z);
				break;
			}
			case 212: {
				lib->selectByNum(62, index, _x, _y + _z);
				break;
			}

					  // 衝跳

			case 213: {
				lib->selectByNum(63, index, _x, _y + _z);
				break;
			}
			case 214: {
				lib->selectByNum(64, index, _x, _y + _z);
				break;
			}

			case 216: {
				lib->selectByNum(112, index, _x, _y + _z);
				break;
			}
			case 217: {
				lib->selectByNum(113, index, _x, _y + _z);
				break;
			}

					  // 停止跑步

			case 218: {
				lib->selectByNum(114, index, _x, _y + _z);
				break;
			}

					  // 被打到向後退

			case 220: {
				lib->selectByNum(120, index, _x, _y + _z);
				break;
			}
			case 221: {
				lib->selectByNum(121, index, _x, _y + _z);
				break;
			}

					  // 被打到向前移

			case 222: {
				lib->selectByNum(123, index, _x, _y + _z);
				break;
			}
			case 223: {
				lib->selectByNum(124, index, _x, _y + _z);
				break;
			}

					  // 被打到向前移的第二個動作

			case 224: {
				lib->selectByNum(130, index, _x, _y + _z);
				break;
			}
			case 225: {
				lib->selectByNum(131, index, _x, _y + _z);
				break;
			}

					  // 暈眩

			case 226: {
				lib->selectByNum(120, index, _x, _y + _z);
				break;
			}
			case 227: {
				lib->selectByNum(122, index, _x, _y + _z);
				break;
			}
			case 228: {
				lib->selectByNum(121, index, _x, _y + _z);
				break;
			}
			case 229: {
				lib->selectByNum(122, index, _x, _y + _z);
				break;
			}

					  // 躺下

			case 230: {
				lib->Falling(0, index, 5, _x, _y + _z);
				break;
			}

					  // 趴下

			case 231: {
				lib->Falling(1, index, 5, _x, _y + _z);
				break;
			}

			default:
				break;
			}

			// test.SetTopLeft(Body.get_x(), Body.get_y());
			// test.ShowBitmap();
		}
	}

	//處理指令輸入時間間隔

	void man::setCountDwon() {
		_Double_Tap_Gap = 75;
	}

	void man::resetCountDown() {
		_Double_Tap_Gap = -1;
	}

	//處理跳躍動作與座標

	bool man::jumping() {
		//TRACE("%d %d %d %d\n", _dir[0], _dir[1], _dir[2], _dir[3]);
		_z -= int(initG / 5);
		--initG;
		if (initG == -height - 1) {
			initG = height;
			return true;
		}
		return false;
	}

	void man::setJumpCount() {
		jumpAnimationGap = 6;
	}

	void man::JumpCount() {
		if (jumpAnimationGap > 0) jumpAnimationGap--;
	}

	bool man::JumpCountisZero() {
		return jumpAnimationGap == 0;
	}

	// 處理攻擊動作

	void man::setattCount() {
		attAnimationGap = 15;
	}

	bool man::attCountisZero() {
		return attAnimationGap == 0;
	}

	void man::attCount() {
		if (attAnimationGap > 0) attAnimationGap--;

	}

	// 處理暈眩動作

	void man::setbeattenCount(int t=10) {
		beatenMotionGap = t;
	}
	void man::beattenCount() {
		if (beatenMotionGap > 0)beatenMotionGap--;
	}
	bool man::beattenCountisZero() {
		return beatenMotionGap == 0;
	}


	void man::recoverCount() {
		if (stonkcount < 0) stonkcount = 6;
		if (recoverGap == 0) {
			recoverGap = 80;
			stonkcount = 6;
		}
		else{
			recoverGap--;
		}
	}
}
