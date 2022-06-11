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
			_mode = 0; 
			arestC = 0;
			beatenCount = 0;
			numOfBeaten = 0;
			_x = _y = _z = 0.0; 
			Frams = nullptr; 
			beatenList = nullptr;
			beatenCount = nullptr;
			Caught = nullptr;
			Alive = true;
			Face_to_Left = true;
			stop = false;
			inMotion = false;
			hit = holdinglt = holdingheavy = false;

			maxx = map_pos = upbond = underbond = 0;
		}
		obj(const obj& o) {
			Frams = o.Frams; _mode = o._mode; _x = o._x; _y = o._y; _z = o._z; Face_to_Left = o.Face_to_Left;
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
		
		~obj() {
			if (beatenCount != nullptr) {
				delete beatenCount;
			}
			if (beatenList != nullptr) {
				delete beatenList;
			}
		}
		
		void del(int n);
		void OnShow();
		void bcount();
		void restList();
		void showShadow();
		void setArest(int n);
		void addBeaten(obj *who);
		void mapSetting(int* data) {
			maxx = data[0]; 
			map_pos = data[1]; 
			upbond = data[2]; 
			underbond = data[3];
			mapdata = data;
		}

		int  getArest();
		
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
		bool checkBeenBeaten(obj *who);

		Frame getNoFrame() { return (*Frams)[_mode]; }
		

		virtual void OnMove() = 0;
		virtual void setdir(bool f) {}
		virtual void nextFrame() {};
		virtual void backToRandon() {};
		virtual void toMotion(int next) {};
		virtual void holdingSth(obj* thing) {}
		virtual void hitSomeOne(obj* other) {}
		virtual void setYstep(double G, double x, double z) {}

		bool isAlive() { return Alive; }
		
		virtual obj* getOwner() { return this; }
		virtual obj* usingSkills() { return nullptr; }



		std::map<int, Frame> *Frams;// 動作資料表
		
		obj*	Caught;				// 被抓住的人
		obj**	beatenList;			// 被打到的人

		int		id;					// 代表自己是什麼
		int		_mode;				// 現在的模式
		int		numOfBeaten;		// 有多少人被打到
		int		cc;					// 抓人計數
		int		time;				// 計數
		int		arestC;				// 多久之後才可以打人
		int		hp;					// 血量
		int		kind;				// 此物品的種類
		int		maxW,maxH;			// 此物品圖片大小
		int		maxx, map_pos;		// 地圖的最大值
		int		upbond, underbond;	// 地圖的上下界線 
		
		int*	beatenCount;		// 多久之後才可以再打一次
		int*	mapdata;			//地圖的資料 寬度 現在的位置 上屆 下屆
		
		bool	Face_to_Left;		// 面相方向
		bool	inMotion;			// 是否在特殊動作裡
		bool	Alive;	
		bool	stop;	
		bool	hit;
		bool	holdinglt;
		bool	holdingheavy;
		
		double	_x, _y, _z;			// 現在的位置
	};

	class allobj {
	public:
		allobj() {
			num = 0;
			all = s = nullptr;
		}
		~allobj() {
			for (int i = 0; i < num; i++)
				delete *(all + i);
			delete all;
		}

		void init();

		void reset() {
			for (int i = 0; i < num; i++)
				delete *(all + i);
			delete all;

			num = 0;
			all = s = nullptr;
		}

		void add(obj *);
		void del(int n);

		obj* getSortObj(int n);

		void so();
		
		obj* getobj(int n);

		obj** getall() { return all; }

		int getN() { return num; }
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

			total_hpcost = total_mpcost = total_damage = 0;
		}
		man(int ch,allobj* al) :man() {
			id = ch;
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
			Frams = Framelib::Instance()->getFrame(id);
		}
		~man() {

		}
		void	setComm(UINT comm);					// 設定指令
		void	cComm(UINT comm);					// 取消指令					
		void	checkbeenatt();						// 被攻擊偵測
		void	OnMove();							// 改變位置
		void	holdingSth(obj* thing) { holding = thing; }
		void	setHP(){ hp = 0; }
		void	setplayer(int p, CStateBar* b){
			player = p;
			bar = b;
		}
		// 跳躍處理
		void	setYstep(double G, double x, double z) {
			initG = G; stepx = x; stepz = z; jumping = true;
		}
		void	moveY() {
			_y -= initG;
		
			if (JumpFront) {_x += stepx;}
			if (JumpBack) {_x -= stepx;}
			if (JumpUp) { _z -= stepz; }
			if (JumpDown) { _z += stepz; }

			if (_y <= (*Frams)[_mode]._centery) {
				_y = maxH;
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
		void	adjustPosition(int f_now,int f_next);
		void	hitSomeOne(obj *thoer) { 
			total_damage += (*Frams)[_mode]._i.getInjury();
			who = thoer; 
			stop = true;
		}
		//案件觸發處理
		void	checkFlag();
		void	checkBuff();
		void	specialEvent();
		// 狀態更新處理
		void	backToRandon();						// 回到原始的狀態
		void	toMotion(int next);					// 處發動作
		void	nextFrame();						// 動作中的下一個Frame
		// 計數器
		void	setTimmer(int t) { time = t; }
		void	Count() {
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
		// 指令輸入間隔
		void	setCountDwon();						//連點倒數
		void	resetCountDown();					//連點倒數歸零
		void	CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }
		void	thw_obj();
		void	injuredMotion(bool f) {
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
		void	hurt(int d);
		
		bool	isTime() { return time == 0; }			
		
		int		getX() { return int(_x); }
		int		getZ() { return int(_z); }
		int		getID() { return id; }
		int		getHP() {
			if (hp > 0)
				return hp;
			else
				return 0;
		}
		int		getTotalHpCost() { return total_hpcost; }
		int		getTotalMpCost() { return total_mpcost; }
		int		getTotalDamage() { return total_damage; }
		int		getNextWalkMotion() {
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

		obj*	usingSkills() {
			obj* a = skills;
			skills = nullptr;
			return a;
		}
	private:
		double	initG;								// 設定上升速度
		double	stepx, stepz;						// 跳躍移動距離
		double	fall;								// 暈眩值
		double	defend;								//防禦直

		//	腳色基本設定參數
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
		int		hpGap, mpGap;						//血量與魔力恢復
		int		total_hpcost, total_mpcost,total_damage;			// 血量與魔力總號耗損

		//
		// 計時相關
		//


		bool	inSpecialMotion;					// 在特殊動作中
		bool	useSupperAtt;						// 可以使用終結季
		bool	JumpUp, JumpDown,JumpFront,JumpBack;// 斜跳
		bool	_dir[4];							// 方向
		bool	flag[7];							// keyboard input flag
		bool	first_att_animation;				// 是不是出左拳
		bool	walk_Ani_dir;						// 走路動作的方向
		bool	run_Ani_dir;						// 跑步動作的方向
		bool	jumping;							// 正在跳躍
		bool	cantBeTouch;						

		obj*	holding;			
		obj*	who;								// 被打的那個
		obj*	skills;								// 出技能
		allobj* _a;				//場上所有人
		CStateBar*	bar;
		std::string commandBuffer;					// input command buffer
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
		
		weapon(int n, int mode, obj* ow,allobj * all) :weapon() {
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
			case 201: {
				maxH = maxW = 48;
			}
			default:
				break;
			}
			Frams = Framelib::Instance()->getFrame(id);
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
		void hitSomeOne(obj *thoer);
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
		void holdingSth(obj* thing) { holding = thing; }
	
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

		obj* getOwner() {
			return holding;
		}
		

		bool	IsHolding;		//有被拾取
		bool	throwing;		
		bool	JumpFront, JumpBack, JumpUp, JumpDown, jumping;

		double	stepx, stepz, initG;
		
		obj*	holding;		//誰再拿他
		allobj* _a;				//場上所有人
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

		wp(int n,int mode,obj* ow, allobj * all):wp(){
			id = n;
			owner = ow;
			this->_a = all;
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
			Frams = Framelib::Instance()->getFrame(id);
			_mode = mode;
			setTimmer((*Frams)[_mode]._wait);
		}
		
		~wp() {
			if (skills != nullptr) {
				delete skills;
			}
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
		void hitSomeOne(obj *thoer);
		void backToRandon();
		void toMotion(int next);
		void nextFrame();
		void OnMove();

		obj* usingSkills() {
			obj* a = skills;
			skills = nullptr;
			return a;
		}
		obj* getOwner() {
			return owner;
		}
	private:
		void adjustPosition(int f_now, int f_next);
		void setTimmer(int t) { time = t; }
		void Count() {
			if (arestC > 0)arestC--;
			if (time > 0) time--;
		}
		
		bool isTime() { return time <= 0; }

		int		stand;			// 持續的時間
		allobj* _a;				//場上所有人
		obj*	skills;			// 心放的技能
		obj*	owner;			// 誰放的		
	};

	class  AI{
	public:
		AI() {
			n = numOfTarget = 0;
			self = Target = nullptr;
			commandFinish = nullptr;
			commandState = nullptr;
			commandType = _x = _z = nullptr;
		}

		~AI() {
			if (self != nullptr)
				delete self;
			if (Target != nullptr)
				//delete Target;
			if(commandType != nullptr)
				delete commandType;
			if (commandFinish != nullptr)
				delete commandFinish;
			if (commandState != nullptr)
				delete commandState;
		}
		void add(man* newone);	// 創造電腦
		void check();			// 檢查死了沒
		void del(int n);		// 刪除此電腦
		void del(obj* shit);
		void reset() {
			if (self != nullptr)
				delete self;
			if (commandType != nullptr)
				delete commandType;
			if (commandFinish != nullptr)
				delete commandFinish;
			if (commandState != nullptr)
				delete commandState;

			n = numOfTarget = 0;
			self = nullptr;
			commandFinish = nullptr;
			commandState = nullptr;
			commandType = _x = _z = nullptr;
		}
		void updateEnemy(int n,man** mans);
		void OnMove();

		int  getTotalHP();
		int getComnum() { return n; }
	private:
		int		n;				// 電腦的數量	
		int		numOfTarget;	// 目標的數量
		
		int*	commandType;		// 打哪個種類
		int*	commandState;		
		int*	_x;				//用於紀錄電腦指令移動
		int*	_z;		
		
		bool*	commandFinish;		//指令完成
		
		man**	self;			// 電腦本人
		man**	Target;			// 攻擊目標
	};

	class ObjContainer {
	public:
		ObjContainer() {
			mans = nullptr;
			com = new AI();
		}
		~ObjContainer() {
			if(mans != nullptr)
				delete mans;
			delete com;
		}
		
		void initOfinit(int player1, int player2) {
			bar.init(player1, player2);
		}
		void init(int player1,int player2);
		void load() {
			bar.LoadBitmap();
		}
		void reset() {
			if (mans != nullptr)
				delete mans;
			mans = nullptr;
			a.reset();
			com->reset();
		}
		void check();
		void OnMove();
		void OnShow();
		void KeyUp(UINT nChar);
		void KeyDown(UINT nChar);
		void mapSetting(int* data);
		void creatWeapon(int n,int x,int z);
		void creatEnemy(int type, int x, int y);

		int	 getState() { return state; }
		int  getX() {
			if (mans == nullptr) return 0;
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
			else if (state == 3) {
				return 0;
			}
			else{
				return int(mans[0]->_x);
			}
		}
		int  getEnemyHP();
		int	 getHP();

		bool end();

		std::string getendInfo() {
			if (mans == nullptr) return std::string("");
			
			std::string temp = "";
			temp+= std::to_string(state);
			temp += ",";
			if (state == 0) {
				if ((mans[0]->getHP() > 0) || (mans[1]->getHP() > 0)) {
					temp += '1';
				}
				else {
					temp += '0';
				}
				temp += ',';

				for (int i = 0; i < 2; i++) {
					temp += std::to_string(mans[i]->getID());
					temp += ",";
					temp += std::to_string(mans[i]->getTotalDamage());
					temp += ",";
					temp += std::to_string(mans[i]->getTotalHpCost());
					temp += ",";
					temp += std::to_string(mans[i]->getTotalMpCost());
					temp += ",";
					temp += std::to_string(mans[i]->isAlive());
					temp += ",";
				}
			}
			else {
				if (mans[0]->getHP() >0) {
					temp += '1';
				}
				else {
					temp += '0';
				}
				temp += ',';
				temp+= std::to_string(mans[0]->getID());
				temp += ",";
				temp += std::to_string(mans[0]->getTotalDamage());
				temp += ",";
				temp += std::to_string(mans[0]->getTotalHpCost());
				temp += ",";
				temp += std::to_string(mans[0]->getTotalMpCost());
				temp += ",";
				temp += std::to_string(mans[0]->isAlive());
				temp += ",";
			}
			return temp;
		}
	private:
		int		state;				// 使用者選用腳色的形況
		int*	map_data;			// 地圖的設定值
		AI*		com;				// 電腦
		man**	mans;				// 人物
		allobj  a;					// 場上所有物品
		CStateBar bar;				// 狀態條		
	};

	
}
