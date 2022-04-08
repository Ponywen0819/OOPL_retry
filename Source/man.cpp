#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "man.h"
#include "skills.h"
#include "Area.h"

#define height 28

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
	}

	void man::init(Bitmaplib *l,man *m,int n) {
		lib = l;
		mans = m;
		NumOfMan = n;
		Fset = false;
		_isDizzy = false;
		_Catch = false;
		_catching = false;
	}

	void man::LoadBitmap() {

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

		char *runLf[4] = { ".\\Bitmaps\\temp\\run\\L\\0.bmp",".\\Bitmaps\\temp\\run\\L\\1.bmp",".\\Bitmaps\\temp\\run\\L\\2.bmp",".\\Bitmaps\\temp\\run\\L\\3.bmp"};
		for (int i = 0; i < 4; i++)	run[0].AddBitmap(runLf[i], RGB(0, 0, 0));
		char *runRf[4] = { ".\\Bitmaps\\temp\\run\\R\\0.bmp",".\\Bitmaps\\temp\\run\\R\\1.bmp",".\\Bitmaps\\temp\\run\\R\\2.bmp",".\\Bitmaps\\temp\\run\\R\\3.bmp" };
		for (int i = 0; i < 4; i++)	run[1].AddBitmap(runRf[i], RGB(0, 0, 0));

		//跳躍蹲下動作

		squat[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\0.bmp",RGB(0, 0, 0));
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
		char *bigattL[3] = { ".\\Bitmaps\\temp\\bigatt\\L\\0.bmp",".\\Bitmaps\\temp\\bigatt\\L\\1.bmp",".\\Bitmaps\\temp\\bigatt\\L\\2.bmp"};
		for (int i = 0; i < 3; i++) bigatt[0][i].LoadBitmap(bigattL[i], RGB(0, 0, 0));
		char *bigattR[3] = { ".\\Bitmaps\\temp\\bigatt\\R\\0.bmp",".\\Bitmaps\\temp\\bigatt\\R\\1.bmp",".\\Bitmaps\\temp\\bigatt\\R\\2.bmp"};
		for (int i = 0; i < 3; i++) bigatt[1][i].LoadBitmap(bigattR[i], RGB(0, 0, 0));

		//踢動作

		char *kickL[2] = { ".\\Bitmaps\\temp\\kick\\L\\0.bmp",".\\Bitmaps\\temp\\kick\\L\\1.bmp"};
		for (int i = 0; i < 2; i++) kick[0][i].LoadBitmap(kickL[i], RGB(0, 0, 0));
		char *kickR[2] = { ".\\Bitmaps\\temp\\kick\\R\\0.bmp",".\\Bitmaps\\temp\\kick\\R\\1.bmp"};
		for (int i = 0; i < 2; i++) kick[1][i].LoadBitmap(kickR[i], RGB(0, 0, 0));

		// 飛踢動作

		char *flykickL[2] = { ".\\Bitmaps\\temp\\kick\\L\\2.bmp",".\\Bitmaps\\temp\\kick\\L\\3.bmp" };
		for (int i = 0; i < 2; i++) flykick[0][i].LoadBitmap(flykickL[i], RGB(0, 0, 0));
		char *flykickR[2] = { ".\\Bitmaps\\temp\\kick\\R\\2.bmp",".\\Bitmaps\\temp\\kick\\R\\3.bmp" };
		for (int i = 0; i < 2; i++) flykick[1][i].LoadBitmap(flykickR[i], RGB(0, 0, 0));

		//讀取個別腳色技能表

		readCommand();
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
		
		if (_mode <  5) {
			if (comm == 1 && Face_to_Left == false)	Face_to_Left = true;
			else if (comm == 2 && Face_to_Left)	Face_to_Left = false;
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
		//TRACE("%d", _outofctrl);
		//TRACE("check flag %d %d %d\n", _outofctrl, _isDizzy, _Catch);
		if (_outofctrl) return;
		//if (_isDizzy) return;
		//if (_Catch) return;

		if (flag[0]) {
			if ((!Face_to_Left) && (_mode == 100)) {
				_mode = 0;
			}
			else if ((_mode == 120 || _mode == 121) && !Face_to_Left) {
				gotCatch->_mode = 133;
				gotCatch->_Catch = false;
				setTimmer(9);
				_catching = false;
				_mode = 0;
			}
			else if(_mode!=100) {
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
			if ((Face_to_Left) && (_mode == 100)) {
				_mode = 0;
			}
			else if ((_mode == 120 || _mode == 121) && Face_to_Left) {
				gotCatch->_mode = 133;
				gotCatch->_Catch = false;
				setTimmer(9);
				_catching = false;
				_mode = 0;
			}
			else if (_mode != 100) {
				bool finish = false;
				for (int i = 0; i < NumOfMan; i++) {
					//TRACE("qwe %d %d\n", NearBy(*(mans + i)) , (mans + i)->isDizzy());
					if (NearBy(*(mans + i)) && (mans + i)->isDizzy()) {
						gotCatch = (mans + i);
						gotCatch->_mode = 131;
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
			if(_mode !=100)
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
			if (_mode == 100) {
				if(Face_to_Left) _mode = 94;
				else _mode = 93;
			}
			else {
				_mode = 90;
			}
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
			else{
				bool finish=false;
				for (int i = 0; i < NumOfMan; i++) {
					//TRACE("finish skills %d %d %d\n", NearBy(*(mans + i)) , FaceTo(*(mans + i)) , (mans + i)->isDizzy());
					if ( NearBy(*(mans + i)) && FaceTo(*(mans + i)) && (mans+i)->isDizzy() ) {
						setTimmer(10);
						finish = true;
						_outofctrl = true;
						_mode = 70;
						break;
					}
				}
				if (!finish) {
					_mode = 101;
					_outofctrl = true;
					first_att_animation = !first_att_animation;
					setattCount();
				}
			}
		}

		if (_mode < 5) {
			for (int i = 0; i < 4; i++) {
				if (flag[i]) {
					_mode = 1;
					break;
				}
				else {
					_mode = 0;
					_dir[i] = false;
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
					_mode = 100;
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
		//TRACE("%d %d \n", flag[4], flag[5]);
		if (flag[5]) {
			if (_mode == 92) {
				setattCount();
				_mode = 106;
			}
			else if (_mode == 93 ) {
				setattCount();
				_mode = 108;
			}
			else if (_mode == 94) {
				setattCount();
				_mode = 109;
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
				TRACE("%d\n", stonkcount);
				if (stonkcount > 3) {
					_mode = 220;
					setTimmer(6);
				}
				else if (stonkcount > 0) {
					if(temp->getDir() != Face_to_Left){
						_mode = 224;
						setTimmer(6);
					}
					else{
						setTimmer(6);
						_mode = 222;
					}
				}
				else if(stonkcount == 0){
					TRACE("dizzy \n");
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

	void man::caculateZ(int f, int x, int z) {
		tempf = f;
		float temp = float(f) / 2;
		a1 =- z / (temp*temp);
		a2 = temp;
		a3 = float(z);
		a4 = float(x) / f;
		FrameCount = 0;
		_z = 0;
		tempx = float(_x);
		//TRACE("init %f %f %f", a1, a2, a3);
		Fset = true;
	}

	void man::setZ() {
		if (Fset) {
			FrameCount++;
			_z = int(a1 * ((FrameCount - a2) *(FrameCount - a2)) + a3);
			_x = int(tempx + a4);
			tempx += a4;
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
		now = nullptr;
		if(_Double_Tap_Gap>=0) _Double_Tap_Gap--;
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
		switch (_mode){
		case 1:
			setPosotion(1);
			break;
		case 70:
			if(Face_to_Left) setInitPosotion(_x - 1, _y);
			else setInitPosotion(_x + 1, _y);
			if (isTime()) {
				setTimmer(6);
				_mode = 71;
			}
			break;
		case 71:
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
		case 72:
			if (isTime()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 90:
			if (JumpCountisZero()) {
				_mode = 91; setJumpCount();
			}
			break;
		case 91:
			if (JumpCountisZero()) {
				_mode = 92; 
			}
			break;
		case 92:
			setPosotion(2);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 93:
		case 94:
			setPosotion(4);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 100:						//衝刺動作
			setPosotion(2);
			break;

		case 101:
			if (attCountisZero()) {		// 準備攻擊
				_mode = 102;
				setattCount();
				punch *temp = new punch(_x, _y, _z, Face_to_Left, first_att_animation, lib, (void*)this);
				temp->setdizzy(2);
				temp->init(Face_to_Left);
				now = temp;
			}
			break;
		case 102:						
			if (attCountisZero()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 103:
			setPosotion(2);
			if (attCountisZero()) {
				_mode = 104;
				setattCount();
			}
			break;
		case 104:
			setPosotion(2);
			if (attCountisZero()) {
				_mode = 105;
				setattCount();
			}
			break;
		case 105:
			setPosotion(2);
			if (attCountisZero()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 106:
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
		case 107:
			if (attCountisZero()) {
				_mode = 92;
			}
			setPosotion(2);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;

		// 飛踢

		case 108:
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
		case 109:
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
		case 110:
			setPosotion(4);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 111:								
			setPosotion(4);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;

		// 捉住人的動作

		case 120:
			dizzyCount -= -7;
			if (isTime()) {
				gotCatch->_mode = 130;
				_mode = 121;
			}
			break;
		case 121:
			dizzyCount -= 7;
			if (dizzyCount <= 0) {
				gotCatch->_mode = 133;
				gotCatch->_Catch = false;
				setTimmer(9);
				_catching = false;
				_mode = 0;
			}
			break;

		// 捉住人攻擊

		case 122:
			break;
		case 123:
			break;

		// 被捉住

		case 130:
			break;
		case 131:
			break;
		case 132:
			break;

		// 被捉結束

		case 133:
			if (isTime()) {
				setTimmer(9);
				_mode = 134;
			}
			break;
		case 134:
			if (isTime()) {
				setTimmer(9);
				_mode = 135;
			}
			break;
		case 135:
			if (isTime()) {
				setTimmer(9);
				_mode = 136;
			}
			break;
		case 136:
			if (isTime()) {
				setTimmer(9);
				_mode = 137;
			}
			break;
		case 137:
			if (isTime()) {
				setTimmer(9);
				_mode = 138;
			}
			break;
		case 138:
			if (isTime()) {
				setTimmer(90);
				_mode = 230;
			}
			break;
		case 139:
			if (isTime()) {
				setTimmer(9);
				_mode = 140;
			}
			break;
		case 140:
			if (isTime()) {
				setTimmer(9);
				_mode = 141;
			}
			break;
		case 141:
			if (isTime()) {
				setTimmer(9);
				_mode = 142;
			}
			break;
		case 142:
			if (isTime()) {
				setTimmer(9);
				_mode = 143;
			}
			break;
		case 143:
			if (isTime()) {
				setTimmer(9);
				_mode = 144;
			}
			break;
		case 144:if (isTime()) {
			setTimmer(90);
			_mode = 231;
		}
			break;

		// 正面飛走

		case 180:						
			if (isTime()) {
				caculateZ(45, -50, -12);
				setTimmer(9);
				_mode = 181;
			}
			break;
		case 181:
			if (isTime()) {
				setTimmer(9);
				_mode = 182;
			}
			break;
		case 182:
			if (isTime()) {
				setTimmer(9);
				_mode = 183;
			}
			break;
		case 183:
			if (isTime()) {
				setTimmer(9);
				_mode = 184;
			}
			break;
		case 184:
			if (isTime()) {
				setTimmer(9);
				_mode = 185;
			}
			break;
		case 185:
			if (isTime()) {
				setTimmer(90);
				_mode = 230;
			}
			break;

		// 背後擊飛

		case 186:
			if (isTime()) {
				caculateZ(45, 50, -12);
				setTimmer(9);
				_mode = 187;
			}
			break;
		case 187:
			setZ();
			if (isTime()) {
				setTimmer(9);
				_mode = 188;
			}
			break;
		case 188:
			setZ();
			if (isTime()) {
				setTimmer(9);
				_mode = 189;
			}
			break;
		case 189:
			setZ();
			if (isTime()) {
				setTimmer(9);
				_mode = 190;
			}
			break;
		case 190:
			setZ();
			if (isTime()) {
				setTimmer(9);
				_mode = 191;
			}
			break;
		case 191:
			setZ();
			if (isTime()) {
				setTimmer(90);
				_mode = 231;
			}
			break;

		// 打到向後退的動作

		case 220:
			if (isTime()) {
				setTimmer(9);
				_mode = 221;
			}
			break;
		case 221:
			if (isTime()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;

		// 打到向前移的動作

		case 222:
			if (isTime()) {
				setTimmer(9);
				_mode = 223;
			}
			break;
		case 223:
			if (isTime()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		
		// 打到第二個動作
		
		case 224:
			if (isTime()) {
				setTimmer(9);
				_mode = 225;
			}
			break;
		case 225:
			if (isTime()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		
		// 暈眩
		
		case 226:
			if (isTime()) {
				setTimmer(18);
				_mode = 227;
			}
			break;
		case 227:
			if (isTime()) {
				setTimmer(18);
				_mode = 228;
			}
			break;
		case 228:
			if (isTime()) {
				setTimmer(18);
				_mode = 229;
			}
			break;
		case 229:
			if (isTime()) {
				_mode = 0;
				_outofctrl = false;
				_isDizzy = false;
			}
			break;

		// 躺著倒地

		case 230:
			if (isTime()) {
				_mode = 0;
			}
			break;
		
		// 趴著倒地
		
		case 231:
			if (isTime()) {
				_mode = 0;
			}
			break;


		default:
			break;
		}
		Body.setPosetion(_x+25, _y+15);
	}
	
	//人物顯示

	void man::onShow() {
		int index;
		if (Face_to_Left) index = 0;
		else index = 1;
		switch (_mode){
		case 0:
			stand[index].OnMove();
			stand[index].SetTopLeft(_x, _y+_z);
			stand[index].OnShow();
			break;
		case 1:
			walk[index].OnMove();
			walk[index].SetTopLeft(_x, _y + _z);
			walk[index].OnShow();
			break;
		case 70:
			lib->setSuper_attTopLeft(index, 0, _x, _y + _z);
			lib->showSuper_att(index,0);
			break;
		case 71:
			lib->setSuper_attTopLeft(index, 1, _x, _y + _z);
			lib->showSuper_att(index, 1);
			break;
		case 72:
			lib->setSuper_attTopLeft(index, 2, _x, _y + _z);
			lib->showSuper_att(index, 2);
			break;
		case 90:									//跳躍蹲下
			squat[index].SetTopLeft(_x, _y+_z);
			squat[index].ShowBitmap();
			break;
		case 91:									//跳躍準備
			readyJump[index].SetTopLeft(_x, _y+_z);
			readyJump[index].ShowBitmap();
			break;
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
			run[index].SetTopLeft(_x, _y+_z);
			run[index].OnShow();
			break;
		case 101:									//攻擊動作預備
			if (first_att_animation) {
				att[index][0].SetTopLeft(_x,_y+_z);
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

		case 120:
			lib->selectByNum(135,index,_x,_y+_z);
			break;
		case 121:
			lib->selectByNum(50, index, _x, _y + _z);
			break;

			// 捉住人攻擊

		case 122:
			lib->selectByNum(51, index, _x, _y + _z);
			break;
		case 123:
			lib->selectByNum(52, index, _x, _y + _z);
			break;

			// 被捉住

		case 130:
			lib->selectByNum(53, index, _x, _y + _z);
			break;
		case 131:
			lib->selectByNum(54, index, _x, _y + _z);
			break;

			// 被捉住打

		case 132:
			lib->selectByNum(55, index, _x, _y + _z);
			break;
		case 133:
			lib->selectByNum(30, index, _x, _y + _z);
			break;
		case 134:
			lib->selectByNum(31, index, _x, _y + _z);
			break;
		case 135:
			lib->selectByNum(32, index, _x, _y + _z);
			break;
		case 136:
			lib->selectByNum(33, index, _x, _y + _z);
			break;
		case 137:
			lib->selectByNum(34, index, _x, _y + _z);
			break;
		case 138:
			lib->selectByNum(35, index, _x, _y + _z);
			break;
		case 139:
			lib->selectByNum(40, index, _x, _y + _z);
			break;
		case 140:
			lib->selectByNum(41, index, _x, _y + _z);
			break;
		case 141:
			lib->selectByNum(42, index, _x, _y + _z);
			break;
		case 142:
			lib->selectByNum(43, index, _x, _y + _z);
			break;
		case 143:
			lib->selectByNum(44, index, _x, _y + _z);
			break;
		case 144:
			lib->selectByNum(45, index, _x, _y + _z);
			break;

		// 被打到向後退

		case 220:
			lib->selectByNum(120, index, _x, _y + _z);
			break;
		case 221:
			lib->selectByNum(121, index, _x, _y + _z);
			break;

		// 被打到向前移

		case 222:
			lib->selectByNum(123, index, _x, _y + _z);
			break;
		case 223:
			lib->selectByNum(124, index, _x, _y + _z);
			break;

		// 被打到向前移的第二個動作

		case 224:
			lib->selectByNum(130, index, _x, _y + _z);
			break;
		case 225:
			lib->selectByNum(131, index, _x, _y + _z);
			break;

		// falling

		case 180:
			lib->Falling(0, index, 0, _x, _y + _z);
			break;
		case 181:
			lib->Falling(0, index, 1, _x, _y + _z);
			break;
		case 182:
			lib->Falling(0, index, 2, _x, _y + _z);
			break;
		case 183:
			lib->Falling(0, index, 3, _x, _y + _z);
			break;
		case 184:
			lib->Falling(0, index, 4, _x, _y + _z);
			break;
		case 185:
			lib->Falling(0, index, 5, _x, _y + _z);
			break;

		// 背後擊飛

		case 186:
			lib->Falling(1, index, 0, _x, _y + _z);
			break;
		case 187:
			lib->Falling(1, index, 1, _x, _y + _z);
			break;
		case 188:
			lib->Falling(1, index, 2, _x, _y + _z);
			break;
		case 189:
			lib->Falling(1, index, 3, _x, _y + _z);
			break;
		case 190:
			lib->Falling(1, index, 5, _x, _y + _z);
			break;
		case 191:
			lib->Falling(1, index, 4, _x, _y + _z);
			break;

		// 暈眩

		case 226:
			lib->selectByNum(120, index, _x, _y + _z);
			break;
		case 227:
			lib->selectByNum(122, index, _x, _y + _z);
			break;
		case 228:
			lib->selectByNum(121, index, _x, _y + _z);
			break;
		case 229:
			lib->selectByNum(122, index, _x, _y + _z);
			break;

		// 躺下

		case 230:
			lib->Falling(0, index, 5, _x, _y + _z);
			break;
		
		// 趴下
		
		case 231:
			lib->Falling(1, index, 5, _x, _y + _z);
			break;
		default:
			break;
		}	

		// test.SetTopLeft(Body.get_x(), Body.get_y());
		// test.ShowBitmap();
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