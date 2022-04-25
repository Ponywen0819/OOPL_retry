#pragma once

#include "Bitmaplib.h"
#include "skills.h"
#include "Area.h"
#include "CStateBar.h"
#include <string>
#include <map>
#include "Frame.h"


namespace game_framework {
	class obj{
	public:
		obj() { 
			Frams = nullptr; 
			_mode = 0; 
			_x = _y = _z = 0.0; 
			beatenCount = 0;
			beatenCount = nullptr;
			beatenList = nullptr;
			numOfBeaten = 0;
			Face_to_Left = true;
			inMotion = false;
			Caught = nullptr;
		}
		obj(const obj& o) {
			Frams = o.Frams; _mode = o._mode; _x = o._x; _y = o._y; _z = o._z; Face_to_Left = o.Face_to_Left;
		}
		~obj() {
			if (beatenCount != nullptr) {
				delete beatenCount;
			}
			if (beatenList != nullptr) {
				delete beatenList;
			}
		}

		obj& operator=(const obj& o) {
			if (this != &o) {
				Frams = o.Frams; 
				_mode = o._mode; 
				_x = o._x; 
				_y = o._y; 
				_z = o._z; 
				Face_to_Left = o.Face_to_Left;
				beatenList = o.beatenList;
				beatenCount = o.beatenCount;

			}
			return *this;
		}

		obj(std::map<int, Frame> *f) {
			Frams = f;
		}

		bool touch(itr i,bool _Face_to_left, double x, double y, double z) {
			// 攻擊作用範圍
			double Lx, Ly, Rx, Ry;
			if (_Face_to_left) {
				Rx = 79 + x - i.getX();
				Lx = Rx - i.getW();
				
				Ly = i.getY() + y;
				Ry = Ly + i.getH();
			}
			else {
				Lx = i.getX() + x;
				Ly = i.getY() + y;
				Rx = Lx + i.getW();
				Ry = Ly + i.getH();
			}
			int n = (*Frams)[_mode]._Num_of_hitbox;

			for (int i = 0; i < n; i++) {
				hitbox hit = *((*Frams)[_mode]._hitbox + i);
				double _Lx, _Ly, _Rx, _Ry;
				if (this->Face_to_Left) {
					_Rx = 79 + _x - hit.getX();
					_Lx = _Rx - hit.getW();

					_Ly = hit.getY() + _y;
					_Ry = _Ly + hit.getH();
				}
				else {
					_Lx = hit.getX() + _x;
					_Ly = hit.getY() + _y;
					_Rx = _Lx + hit.getW();
					_Ry = _Ly + hit.getH();
				}
				double min_x = _Lx > Lx ? _Lx : Lx;
				double min_y = _Ly > Ly ? _Ly : Ly;
				double max_x = _Rx < Rx ? _Rx : Rx;
				double max_y = _Ry < Ry ? _Ry : Ry;
				if (min_x > max_x || min_y > max_y) {
					continue;
				}
				else {
					return true;
				}
			}
			return false;
		}

		void addBeaten(obj *who);

		bool checkBeenBeaten(obj *who);
		void restList();
		void bcount();
		void del(int n);

		bool	inMotion;			// 是否在特殊動作裡
		std::map<int, Frame> *Frams;
		int		_mode;				// 現在的模式
		double	_x, _y, _z;			// 現在的位置
		bool	Face_to_Left;		// 面相方向
		obj*	Caught;				// 被抓住的人

		obj**	beatenList;			// 被打到的人
		int*	beatenCount;		// 多久之後才可以再打一次
		int		numOfBeaten;		// 有多少人被打到
	};


	class man:public obj{
	public:
		man() {
			charector = 0;
			_Double_Tap_Gap = 30;
			initG = 0;
			time = 0;
			Walk_Ani_num = 5;
			fall = 100;
			commandBuffer = "";

			for (int i = 0; i < 7; i++)	flag[i] = false;
			for (int i = 0; i < 4; i++)	_dir[i] = false;
			first_att_animation = true;
			jumpType = false;
			walk_Ani_dir = true;
			run_Ani_dir = true;
			JumpUp = false;
			JumpDown = false;
			JumpFront = false;
		}
		~man() {

		}
		
		// 設定初始庫
		void	init(Bitmaplib *l, man *m, int n,CStateBar *state, std::map<int, Frame> *f);		

		void	getAllObj(obj** a, int n) {
			all = a;
			numofobj = n;
		}

		void	setInitPosotion(int x, int y);		// 設定初始位置	

		void	setComm(UINT comm);					// 設定指令
		void	cComm(UINT comm);					// 取消指令					

		void	checkbeenatt();						// 被攻擊偵測
		void	OnMove();							// 改變位置
		void	onShow();							// 顯示

		void	setCH(int ch) {						//設定是哪個腳色
			charector = ch;
		}

		bool	out() { return inMotion; }
		int		gotMode() { return _mode; }
		int		getx() { return int(_x); }
		int		gety() { return int(_y); }
		int		getz() { return int(_z); }
		int		getNext() { return (*Frams)[_mode]._next; }
		int		getState() { return (*Frams)[_mode]._state; }

	protected:
		int		getNextWalkMotion() {
			if (walk_Ani_dir) {
				if (++Walk_Ani_num == 9) {
					Walk_Ani_num = 7;
					walk_Ani_dir = !walk_Ani_dir;
				}
			}
			else {
				if (--Walk_Ani_num == 4) {
					Walk_Ani_num = 6;
					walk_Ani_dir = !walk_Ani_dir;
				}
			}
			return Walk_Ani_num;
		}
		void	adjustPosition(int f_now,int f_next);
		

		virtual void otherCommand(int n);
		virtual void readOtherList();

		vector<std::string> commandList;			// 被讀取的指令列表
		
		void setPosotion(int n);
		void setYstep(double G, double x, double z) {
			_y += G++; initG = G; stepx = x; stepz = z;
		}
		void moveY() {
			if (_y >= 0) { 
				return; 
			}
			_y += initG++;
			initG += 1;
			if (JumpFront) {_x += stepx;}
			if (JumpBack) {_x -= stepx;}
			if (JumpUp) { _z -= stepz; }
			if (JumpDown) { _z += stepz; }
		}

		void checkFlag();
		void checkBuff();
		void specialEvent();
		void readCommand();

		// 計數器
		void setTimmer(int t) { time = t; }
		void Count() {
			if (fall < 100)fall ++;
			else if (fall < 45) fall = 45;
			if (time > 0) time--;
		}
		bool isTime() { return time == 0; }			

		void backToRandon();						// 回到原始的狀態
		void toMotion(int next);					// 處發動作
		void nextFrame();							// 動作中的下一個Frame
		

		// 指令輸入間隔
		void setCountDwon();						//連點倒數
		void resetCountDown();						//連點倒數歸零
		void CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }

	private:
		double	initG;								// 設定上升速度
		double	stepx, stepz;						// 跳躍移動距離
		double	fall;								// 暈眩值

		int		Walk_Ani_num;						// 下一個走路動作的號碼
		int		charector;							// 選擇之腳色
		int		_Double_Tap_Gap;					// 連點間隔
		int		NumOfMan;							// 在場上的人
		int		time;								// 計數

		bool	useSupperAtt;						// 可以使用終結季
		bool	JumpUp, JumpDown,JumpFront,JumpBack;			// 斜跳
		bool	jumpType;
		bool	_dir[4];							// 方向
		bool	flag[7];							// keyboard input flag
		bool	first_att_animation;				// 是不是出左拳
		bool	Alive;								// 是否活著
		bool	walk_Ani_dir;						// 走路動作的方向
		bool	run_Ani_dir;						// 跑步動作的方向
			
		std::string commandBuffer;					// input command buffer
		
		obj*	beaten;								//

		Bitmaplib *	lib;							// 圖片輸出
		CStateBar *	_s;								// 血量條
		obj **all;									// 場上的物品人物
		int numofobj;								// 場上的物品人物數量
		man *		mans;							// 在場上的人	
		man *		gotCatch;						// 被抓的人
	};

	class weapon:public obj{
	public:
		weapon() { _mode = 0; }
		
		void init(std::map<int, Frame> *f){
			Frams = f;
			hp = 200;
		}

		void OnMove() {
			if (IsHolding) {
				//獲取man的位置與更新位置
			}
		}
		void OnShow();
	private:
		man*	holding;		//誰再拿他
		bool	IsHolding;		//有被拾取

		int hp;
	};

}
