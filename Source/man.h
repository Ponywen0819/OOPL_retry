#pragma once

#include "Bitmaplib.h"
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
			arestC = 0;
			Alive = true;
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

		// 物品各自有自己移動的方式
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;
		
		//
		// 動作更新函式
		//
		virtual void backToRandon() {};
		virtual void toMotion(int next) {};
		virtual void nextFrame() {};

		// 鍵盤動作 =>只有人物有(會改掉)
		virtual void	setComm(UINT comm) {}			// 設定指令
		virtual void	cComm(UINT comm) {}				// 取消指令					

		// 取得資料庫
		void init(Bitmaplib *l,obj** a,int n, std::map<int, Frame> *f) {
			Frams = f;
			this->all = a;
			numOfObj = n;
			lib = l;
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
			
			if (abs(z - _z) > 12) {
				return true;
			}

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
				//TRACE("%.1f %.1f %.1f %.1f\n", min_x, min_y, max_x, max_y);
				if (min_x > max_x || min_y > max_y) {
					continue;
				}
				else {
					return true;
				}
			}
			return false;
		}

		bool touch(obj * o) {
			if (abs(o->_z - this->_z) > 10) {
				return false;
			}
			//
			// 建立攻擊方判定區域
			//
			area att;
			att.init(o->_x, o->_y+o->_z, (*(o->Frams))[o->_mode]._i.getX(), (*(o->Frams))[o->_mode]._i.getY(),
				(*(o->Frams))[o->_mode]._i.getW(), (*(o->Frams))[o->_mode]._i.getH(), o->Face_to_Left, o->max);
			for (int i = 0; i < (*Frams)[_mode]._Num_of_hitbox; i++) {
				hitbox hit = *((*Frams)[_mode]._hitbox + i);
				area n;
				n.init(_x, _y+_z, hit.getX(), hit.getY(), hit.getW(), hit.getH(), this->Face_to_Left, this->max);
				if (n.touch(att)) {
					return true;
				}
			}
			return false;
		}
		//不重要
		void addBeaten(obj *who);
		bool checkBeenBeaten(obj *who);
		void restList();
		void bcount();
		void del(int n);
		

		virtual obj*	usingSkills() {
			return nullptr;
		}

		std::map<int, Frame> *Frams;	// 動作資料表
		//
		obj** all;						// 所有物品的列表
		int numOfObj;					// 所有物品的個數
		//	應該會改掉

		Bitmaplib *	lib;			// 圖片輸出
		bool	inMotion;			// 是否在特殊動作裡
		int		_mode;				// 現在的模式
		double	_x, _y, _z;			// 現在的位置
		bool	Face_to_Left;		// 面相方向

		obj*	Caught;				// 被抓住的人
		obj**	beatenList;			// 被打到的人

		int		max;				// 此物品圖片大小
		int*	beatenCount;		// 多久之後才可以再打一次
		int		numOfBeaten;		// 有多少人被打到
		int		cc;					// 抓人計數
		int		time;				// 計數
		int		arestC;				// 多久之後才可以打人
		bool	Alive;				
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

			for (int i = 0; i < 8; i++)SkillsMotion[i] = -1;
			SkillsMotion[0] = SkillsMotion[1] = 9;
			for (int i = 0; i < 7; i++)	flag[i] = false;
			for (int i = 0; i < 4; i++)	_dir[i] = false;
			first_att_animation = true;
			inSpecialMotion = false;
			walk_Ani_dir = true;
			run_Ani_dir = true;
			JumpUp = false;
			JumpDown = false;
			JumpFront = false;
			skills = nullptr;
			max = 79;
			//
			//	人物基本動作參數設定
			//
			wlaking_speed = 4;
			wlaking_speed_z = 2;

			running_speed = 8;
			running_speed_z = 1.3;

			heavy_walking = 3;
			heavy_walking_z = 1.5;

			heavy_running = 5;
			heavy_running_z = 0.8;

			jump_height = -16.3;
			jump_distance = 8;
			jump_distance_z = 3;

			dash_distance = 15;
			dash_distance_z = 3.75;
		}
		man(int ch) :man() {
			charector = ch;
			switch (ch){
			case 0: {
				SkillsMotion[2] = 235;
				SkillsMotion[3] = 290;
				//SkillsMotion[4] = 266; // 不做了
				SkillsMotion[6] = 260;
				break;
			}
			case 1: {
				SkillsMotion[2] = 235;
				SkillsMotion[3] = 245;
				SkillsMotion[4] = 260;
				SkillsMotion[5] = 270;
				break;
			}
			case 2: {
				SkillsMotion[2] = 235;
				SkillsMotion[3] = 255;
				SkillsMotion[4] = 285;
				SkillsMotion[5] = 267;
				break;
			}
			default:
				break;
			}
		}
		~man() {

		}	

		void	getFl(Framelib* a) {
			fl = a;
		}
		void	setComm(UINT comm);					// 設定指令
		void	cComm(UINT comm);					// 取消指令					

		obj*	usingSkills() {
			obj* a = skills;
			//TRACE("%d\n", a);
			skills = nullptr;
			return a;
		}

		void	checkbeenatt();						// 被攻擊偵測
		void	checkbeenatt(obj**, int);
		void	OnMove();							// 改變位置
		void	OnShow();							// 顯示
	protected:

		void getAllObj(obj** a, int n) {
			all = a;
			numOfObj = n;
		}		// 取得在場上的所有物品

		// 跳躍處理

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

			if (charector == 0) {
				if ((initG == 0) && (_mode == 267)) {
					toMotion(268);
				}
			}
		}
		void adjustPosition(int f_now,int f_next);

		//案件觸發處理
		void checkFlag();
		void checkBuff();
		void specialEvent();

		// 狀態更新處理
		void backToRandon();						// 回到原始的狀態
		void toMotion(int next);					// 處發動作
		void nextFrame();							// 動作中的下一個Frame

		// 計數器
		void setTimmer(int t) { time = t; }
		void Count() {
			if (arestC > 0)arestC--;
			if (fall < 100)fall ++;
			else if (fall < 45) fall = 45;
			if (time > 0) time--;
		}
		bool isTime() { return time == 0; }			

		// 指令輸入間隔
		void setCountDwon();						//連點倒數
		void resetCountDown();						//連點倒數歸零
		void CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }

		int	 getNextWalkMotion() {
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
	private:
		double	initG;								// 設定上升速度
		double	stepx, stepz;						// 跳躍移動距離
		double	fall;								// 暈眩值

		//
		//	腳色基本設定參數
		//
		double	wlaking_speed;
		double	wlaking_speed_z;

		double	running_speed;
		double	running_speed_z;

		double	heavy_walking;
		double	heavy_walking_z;

		double	heavy_running;
		double	heavy_running_z;

		double	jump_height;
		double	jump_distance;
		double	jump_distance_z;

		double	dash_distance;
		double	dash_distance_z;

		int		Walk_Ani_num;						// 下一個走路動作的號碼
		int		charector;							// 選擇之腳色
		int		_Double_Tap_Gap;					// 連點間隔
		int		NumOfMan;							// 在場上的人
		int		SkillsMotion[8];					

		bool	inSpecialMotion;					// 在特殊動作中
		bool	useSupperAtt;						// 可以使用終結季
		bool	JumpUp, JumpDown,JumpFront,JumpBack;// 斜跳
		bool	_dir[4];							// 方向
		bool	flag[7];							// keyboard input flag
		bool	first_att_animation;				// 是不是出左拳
		bool	Alive;								// 是否活著
		bool	walk_Ani_dir;						// 走路動作的方向
		bool	run_Ani_dir;						// 跑步動作的方向

		Framelib*	fl;
		obj*	skills;								// 出技能
		std::string commandBuffer;					// input command buffer
	};

	class weapon:public obj{
	public:
		weapon() { _mode = 0; }
		
		void init(std::map<int, Frame> *f,Bitmaplib* b){
			lib = b;
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

	class wp :public obj {
	public:
		wp() {
			oid = 0;
			time = 0;
		}

		wp(int id,int mode):wp(){
			oid = id;
			_mode = mode;
		}
		
		void init(std::map<int, Frame> *f, Bitmaplib* b) {
			lib = b;
			Frams = f;
			TRACE("%d\n", Frams);
		}

		void backToRandon();
		void toMotion(int next);
		void nextFrame();

		void OnMove();
		void OnShow();
	private:
		void adjustPosition(int f_now, int f_next);
		// 計數器
		void setTimmer(int t) { time = t; }
		void Count() {
			if (time > 0) time--;
		}
		bool isTime() { return time == 0; }

		int oid;			// 氣功的種類
		int time;			// 持續的時間
	};

	class ObjContainer {
	public:
		ObjContainer() {
			numOfObj = 0;
		}
		~ObjContainer() {
			delete[] all;
		}
		void init(int player1,int player2, Bitmaplib *l, Framelib* f);
		void creatWeapon(int n);
		void addobj(obj *n);

		void KeyUp(UINT nChar);
		void KeyDown(UINT nChar);
		
		void OnMove();
		void OnShow();
	private:
		int		state;				// 使用者選用腳色的形況
		int		numOfObj;			// 場上所有物品的數量
		obj**	all;				// 場上所有物品

		Bitmaplib* lib;				
		Framelib* fl;
	};
}
