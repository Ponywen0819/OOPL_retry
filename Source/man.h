#pragma once

#include "Bitmaplib.h"
#include "Area.h"
#include "CStateBar.h"
#include <string>
#include <map>
#include "Frame.h"

#define MaxHp 500
#define MaxMp 500

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
			stop = false;
			hit = holdinglt = holdingheavy = false;

			maxx = map_pos = upbond = underbond = 0;
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



		// 物品各自有自己移動的方式
		virtual void OnMove() = 0;

		void OnShow();
		

		//
		// 設定
		//
		void updateObj(obj** list, int n) {
			all = list;
			numOfObj = n;
		}
		void setmax(int x) {
			maxx = x;
		}

		void mapSetting(int* data) {
			maxx = data[0]; map_pos = data[1]; upbond = data[2]; underbond = data[3];
			mapdata = data;
		}


		virtual obj* getOwner() {
			return this;
		}

		virtual void holdingSth(obj* thing) {}

		virtual void hitSomeOne(obj* other) {}
		//
		// 動作更新函式
		//
		virtual void backToRandon() {};
		virtual void toMotion(int next) {};
		virtual void nextFrame() {};			

		void init(obj** a,int n) {
			this->all = a;
			numOfObj = n;
			Frams = fl->getFrame(id);
		}
		void setArest(int n);
		int getArest();

		Frame getNoFrame() {
			return (*Frams)[_mode];
		}

		bool touch(obj * o) {

			if (o->id == 213 || o->id == 215) {
				if (abs(o->_z - this->_z) > 40) {
					return false;
				}
			}
			else {
				if (abs(o->_z - this->_z) > 10) {
					return false;
				}
			}
			//
			// 建立攻擊方判定區域
			//
			area att;
			att.init(o->_x, o->_y, (*(o->Frams))[o->_mode]._i.getX(), (*(o->Frams))[o->_mode]._i.getY(),
				(*(o->Frams))[o->_mode]._i.getW(), (*(o->Frams))[o->_mode]._i.getH(), o->Face_to_Left, o->maxW);
			for (int i = 0; i < (*Frams)[_mode]._Num_of_hitbox; i++) {
				hitbox hit = *((*Frams)[_mode]._hitbox + i);
				area n;
				n.init(_x, _y, hit.getX(), hit.getY(), hit.getW(), hit.getH(), this->Face_to_Left, this->maxW);
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
		virtual void	setYstep(double G, double x, double z) {}
		virtual void	setdir(bool f) {}
		int	id;						//代表自己是什麼
		std::map<int, Frame> *Frams;// 動作資料表
		obj**	all;				// 所有物品的列表
		int		numOfObj;			// 所有物品的個數

		Bitmaplib*	lib;			// 圖片輸出
		Framelib*	fl;				// 為了要創造
		bool	inMotion;			// 是否在特殊動作裡
		int		_mode;				// 現在的模式
		double	_x, _y, _z;			// 現在的位置
		bool	Face_to_Left;		// 面相方向
		

		obj*	Caught;				// 被抓住的人
		obj**	beatenList;			// 被打到的人

		int		maxW,maxH;			// 此物品圖片大小
		int*	beatenCount;		// 多久之後才可以再打一次
		int		numOfBeaten;		// 有多少人被打到
		int		cc;					// 抓人計數
		int		time;				// 計數
		int		arestC;				// 多久之後才可以打人
		int		hp;					// 血量
		int		kind;				// 此物品的種類
		// 0: 人物 1: 招式 2: 物品
		
		//
		// 地圖設定
		//
		
		int		maxx, map_pos;			 // 地圖的最大值
		int		upbond, underbond;	 // 地圖的上下界線 
		
		int*	mapdata;				//地圖的資料 寬度 現在的位置 上屆 下屆
		
		bool	Alive;	
		bool	stop;	
		bool	hit;
		bool	holdinglt;
		bool	holdingheavy;
		
	};

	class allobj {
	public:
		allobj() {
			num = 0;
			all = nullptr;
		}
		~allobj() {
			delete[] all;
		}

		void init();

		void add(obj *);
		void del(int n);

		obj* getSortObj(int n);

		void so();
		obj* getobj(int n);
		int getN() {
			return num;
		}
	private:
		int num;
		obj** all;
		obj** s;
	};

	class man :public obj {
	public:
		man() :obj() {
			_Double_Tap_Gap = 30;
			initG = 0;
			time = 0;
			Walk_Ani_num = 5;
			fall = 100;
			mp = 500;
			HpRecover = 500;
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
			cantBeTouch = false;
			maxW = maxH = 79;
			_y = 79;
			cantBrTouchCount = 0;
			stepx = stepz = 0;

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

			hp = HpRecover= 500;
			kind = 0;

			mpGap = hpGap = 0;
			Alive = true;
		}
		man(int ch, Framelib *f, Bitmaplib* b, allobj* al) :man() {
			id = ch;
			lib = b;
			fl = f;
			_a = al;
			switch (ch) {
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
			Frams = fl->getFrame(id);
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
			skills = nullptr;
			return a;
		}

		void	checkbeenatt();						// 被攻擊偵測
		void	OnMove();							// 改變位置
		void	holdingSth(obj* thing) {
			holding = thing;
		}
		
		bool	isAlive() {
			return Alive;
		}

		void	setplayer(int p, CStateBar* b){
			player = p;
			bar = b;
		}

	protected:
		// 跳躍處理
		void setYstep(double G, double x, double z) {
			initG = G; stepx = x; stepz = z; jumping = true;
		}
		void moveY() {
			_y -= initG;
		
			if (JumpFront) {_x += stepx;}
			if (JumpBack) {_x -= stepx;}
			if (JumpUp) { _z -= stepz; }
			if (JumpDown) { _z += stepz; }

			if (_y <= (*Frams)[_mode]._centery) {
				stepx = stepz = initG = 0;
				JumpFront = JumpBack = JumpUp = JumpDown = false;
			}
			else{
				initG += 2;
			}

			if (id == 0) {
				if ((initG == 0) && (_mode == 267)) {
					toMotion(268);
				}
			}
		}

		// 調整位置
		void adjustPosition(int f_now,int f_next);

		void hitSomeOne(obj *thoer) { 
			who = thoer; 
			stop = true;
		}

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
			// 血量回復相關
			if (HpRecover > hp && --hpGap <= 0 && hp <MaxHp && hp > 0) {
				hp++;
				hpGap = 12;

			}

			// 魔力回復相關
			if (--mpGap <= 0 && mp < MaxMp) {
				if (hp > 400) {
					if (id == 2) {
						mp += 3;
					}
					else {
						mp++;
					}
				}
				else if (hp > 300) {
					if (id == 2) {
						mp += 4;
					}
					else {
						mp+=2;
					}
				}
				else if (hp > 200) {
					if (id == 2) {
						mp += 4;
					}
					else {
						mp+=3;
					}
				}
				else if (hp > 100) {
					if (id == 2) {
						mp += 5;
					}
					else {
						mp+=4;
					}
				}
				else {
					mp += 5;
				}
				mpGap = 3;
			}
			
			if (cantBrTouchCount > 0) { cantBrTouchCount--;}
			if (cantBrTouchCount == 0) cantBeTouch = false;
			if (arestC > 0)arestC--;

			// 暈眩值
			if (fall < 100)fall ++;
			else if (fall < 45) fall = 45;
			
			
			if (time > 0) time--;
		}
		bool isTime() { return time == 0; }			

		// 指令輸入間隔
		void setCountDwon();						//連點倒數
		void resetCountDown();						//連點倒數歸零
		void CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }


		void thw_obj();
		void injuredMotion(bool f) {
			if (fall < 35) {			// 擊飛
				if (f != this->Face_to_Left) {
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
				if (f != this->Face_to_Left) {
					toMotion(222);
				}
				else {
					toMotion(224);
				}
			}
			else {						// 被打到第一下
				toMotion(220);
			}

		}
		int	 getNextWalkMotion() {
			if (walk_Ani_dir) {
				if (++Walk_Ani_num >= 9) {
					Walk_Ani_num = 7;
					walk_Ani_dir = !walk_Ani_dir;
				}
			}
			else {
				if (--Walk_Ani_num <= 4) {
					Walk_Ani_num = 6;
					walk_Ani_dir = !walk_Ani_dir;
				}
			}
			return Walk_Ani_num;
		}
	
		void hurt(int d);

	private:
		double	initG;								// 設定上升速度
		double	stepx, stepz;						// 跳躍移動距離
		double	fall;								// 暈眩值
		double	defend;								//防禦直
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

		int		mp;									// 魔力
		int		HpRecover;					
		int		player;					
		int		Walk_Ani_num;						// 下一個走路動作的號碼
		int		_Double_Tap_Gap;					// 連點間隔
		int		NumOfMan;							// 在場上的人
		int		SkillsMotion[8];					
		int		cantBrTouchCount;				

		//
		// 計時相關
		//

		int		hpGap, mpGap;						//血量與魔力恢復

		bool	inSpecialMotion;					// 在特殊動作中
		bool	useSupperAtt;						// 可以使用終結季
		bool	JumpUp, JumpDown,JumpFront,JumpBack;// 斜跳
		bool	_dir[4];							// 方向
		bool	flag[7];							// keyboard input flag
		bool	first_att_animation;				// 是不是出左拳
		bool	Alive;								// 是否活著
		bool	walk_Ani_dir;						// 走路動作的方向
		bool	run_Ani_dir;						// 跑步動作的方向
		bool	jumping;							// 正在跳躍
		bool	cantBeTouch;						

		allobj* _a;									// 場上所有人
		obj*	holding;			
		obj*	who;								// 被打的那個
		obj*	skills;								// 出技能
		std::string commandBuffer;					// input command buffer
		CStateBar*	bar;
	};

	class weapon:public obj{
	public:
		weapon() { 
			_mode = 0; 
			JumpFront, JumpBack, JumpUp, JumpDown, jumping = false;
			stepx, stepz, initG = 0;
			throwing = false;

			kind = 2;
		}
		
		weapon(int n, int mode, Framelib *f, Bitmaplib* b, obj* ow,allobj * all) :weapon() {
			fl = f;
			lib = b;
			id = n;
			_mode = mode;
			switch (id){
			case 10: {
				maxH = maxW = 48;
				break;
			}
			case 11: {
				maxH = maxW = 58;
				break;
			}
			case 12: {
				maxH = maxW = 69;
				break;
			}
			default:
				break;
			}
			Frams = fl->getFrame(id);
			holding = ow;

			_a = all;

			stepx = stepz = initG = 0;
			JumpFront = JumpBack = JumpUp = JumpDown = false;
		}

		void checkbeenatt();
		void init(int x, int y, int z, bool fa) {
			_x = x;
			_y = y;
			_z = z;
			Face_to_Left = fa;
			if (fa) {
				_x = x - (maxW - (*Frams)[_mode]._centerx);
			}
			else {
				_x -= (*Frams)[_mode]._centerx;
			}
			_y += (*Frams)[_mode]._centery;
		}

		void hitSomeOne(obj *thoer) {

		}

		void backToRandon();
		void toMotion(int next);
		void nextFrame();

		void OnMove();

		void setYstep(double G, double x, double z) {
			initG = G; stepx = x; stepz = z; jumping = true;

		}
		
		void setdir(bool f) {
			if (!f) JumpFront = true;
			else JumpBack = true;

			throwing = true;
		}

		void holdingSth(obj* thing) {
			holding = thing;
		}
	private:
		void moveY() {
			int st = (*Frams)[_mode]._state;
			if ( st == 1002) {
				_y-=2;
				if (Face_to_Left) _x -= stepx;
				else _x += stepx;
			}
			else {
				_y -= initG;
				if (JumpFront) { _x += stepx; }
				if (JumpBack) { _x -= stepx; }
				if (JumpUp) { _z -= stepz; }
				if (JumpDown) { _z += stepz; }
			}
			
			if (_y <= (*Frams)[_mode]._centery) {
				stepx = stepz = initG = 0;
				JumpFront = JumpBack = JumpUp = JumpDown = false;
			}
			else {
				initG += 2;
			}

			if (id == 0) {
				if ((initG == 0) && (_mode == 267)) {
					toMotion(268);
				}
			}
		}

		void adjustPosition(int f_now, int f_next) {
			if (!Face_to_Left) _x = _x + (*Frams)[f_now]._centerx - (*Frams)[f_next]._centerx;
			else _x = _x - (*Frams)[f_now]._centerx + (*Frams)[f_next]._centerx;
		}
		// 計數器
		void setTimmer(int t) { time = t; }
		void Count() {
			if (arestC > 0)arestC--;
			if (time > 0) time--;
		}
		bool isTime() { return time <= 0; }

		allobj* _a;				//場上所有人
		obj*	holding;		//誰再拿他
		bool	IsHolding;		//有被拾取
		bool	throwing;		

		obj* getOwner() {
			return holding;
		}
		bool JumpFront, JumpBack, JumpUp, JumpDown, jumping;
		double stepx, stepz, initG;
	};

	class wp :public obj {
	public:
		wp():obj() {
			id = 0;
			hp = 500;
			time = 0;
			skills = nullptr;
			
			kind = 1;
		
		}

		wp(int n,int mode, Framelib *f, Bitmaplib* b,obj* ow):wp(){
			fl = f;
			lib = b;
			id = n;
			owner = ow;
			switch (id) {
			case 203: {
				maxW = 81;
				maxH = 82;
				break;
			}
			case 209: {
				maxW = 81;
				maxH = 82;
				break;
			}
			case 210: {
				maxW = 81;
				maxH = 82;
				break;
			}
			case 211: {
				maxW = 35;
				maxH = 49;
				break;
			}
			case 212: {
				maxW = 59;
				maxH = 63;
				break;
			}
			case 213: {
				maxW =159;
				maxH = 159;
				break;
			}
			case 214: {
				maxW = 109;
				maxH = 109;
				break;
			}
			case 215: {
				maxW = 159;
				maxH = 159;
				break;
			}
			default: {
				maxW = 81;
				maxH = 82;
				break;
			}
			}
			Frams = fl->getFrame(id);
			_mode = mode;
			setTimmer((*Frams)[_mode]._wait);
		}
		
		void init( int x, int y,int z,bool fa) {
			_x = x;
			_y = y;
			_z = z;
			Face_to_Left = fa;
			if (fa) {
				_x = x - (maxW - (*Frams)[_mode]._centerx);
			}
			else {
				_x -= (*Frams)[_mode]._centerx;
			}
				_y += (*Frams)[_mode]._centery;
		}

		obj* usingSkills() {
			obj* a = skills;
			skills = nullptr;
			return a;
		}

		obj* getOwner() {
			return owner;
		}

		void hitSomeOne(obj *thoer);
		void backToRandon();
		void toMotion(int next);
		void nextFrame();

		void OnMove();
	private:
		void adjustPosition(int f_now, int f_next);
		// 計數器
		void setTimmer(int t) { time = t; }
		void Count() {
			if (arestC > 0)arestC--;
			if (time > 0) time--;
		}
		bool isTime() { return time <= 0; }

		allobj* a;				//場上所有人
		obj*	who;			// 被打的那個
		obj*	skills;			// 心放的技能
		obj*	owner;			// 誰放的		
		int		stand;			// 持續的時間
	};

	class ObjContainer {
	public:
		ObjContainer() {
			mans = nullptr;
		}
		~ObjContainer() {

			delete[] mans;
		}
		
		void init(int player1,int player2);

		void load(Bitmaplib *l, Framelib* f) {
			lib = l;
			fl = f;
			bar.LoadBitmap();
		}
		
		void creatWeapon(int n);

		void KeyUp(UINT nChar);
		void KeyDown(UINT nChar);

		int  getX() {
			if (state == 0) {
				if (!mans[0]->isAlive()) {
					return int(mans[0]->_x);
				}
				else if (!mans[1]->isAlive()) {
					return int(mans[0]->_x);
				}
				else {
					return int(mans[0]->_x + mans[1]->_x) / 2;
				}
			}
			else {
				return int(mans[0]->_x);
			}
		}

		void check();


		void mapSetting(int* data);
		void OnMove();
		void OnShow();
	
		void creatEnemy(int type, int x, int y);
	private:
		int		state;				// 使用者選用腳色的形況
		allobj  a;					// 場上所有物品
		CStateBar bar;				// 狀態條
		man**	mans;				//人物
		Bitmaplib* lib;				
		Framelib* fl;
		int maxx, maxz;				// 地圖的最大值

		int* map_data;				// 地圖的最大值
	};

	
}
