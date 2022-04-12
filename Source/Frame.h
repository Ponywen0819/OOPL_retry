#pragma once

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Area.h"

namespace game_framework {
	class itr {
	public:
		itr() {
			_kind = 0;
			_z_width = 0;
			_dvx = _dvy = 0;
			_fall = 0;
			_vrest = 0;
			_bdefend = 0;
			_injury = 0;
		}
		itr(int kind, int x, int y, int w, int h, int z_width,
			int dvx, int dvy, int fall, int vrest, int bdefend, int injury, int effect) :
			_kind{ kind }, _x{ x }, _y{ y }, _w{ w }, _h{ h }, _z_width{ z_width }, 
			_dvx{ dvx }, _dvy{ dvy }, _fall{ fall }, _vrest{ vrest }, _bdefend{ bdefend }, _injury{ injury }, _effect{effect}{}

		int getKind() {
			return _kind;
		}
		int getX() {
			return _x;
		}
		int getY() {
			return _y;
		}
		int getW() {
			return _w;
		}
		int getH() {
			return _h;
		}
		int getZ_width() {
			return _z_width;
		}
		int getDvx() {
			return _dvx;
		}
		int getDvy() {
			return _dvy;
		}
		int getFall() {
			return _fall;
		}
		int getVrest() {
			return _vrest;
		}
		int getBdefend() {
			return _bdefend;
		}
		int  getInjury() {
			return _injury;
		}

	private:
		int _kind;
		int _x, _y, _w, _h;
		int _z_width;
		int _dvx, _dvy;
		int _fall;
		int _vrest;
		int _bdefend;
		int _injury;
		int _effect;
	};
	
	class opoint {
	public:
		opoint() :_kind{ -1 }, _x{ -1 }, _y{ -1 }, _action{ -1 }, _oid{ -1 }, _facing(-1){}

		void setKind(int k) { _kind = k; }
		void setLocation(int x, int y) { _x = x; _y = y; }
		void setAction(int a) { _action = a; }
		void setOid(int i) { _oid = i; }
		void setFacing(int f) { _facing = f; }
	
		int getKind() { return _kind; }
		int getX() { return _x; }
		int getY() { return _y; }
		int getAction() { return _action; }
		int getOid() { return _oid; }
		int getFacing() { return _facing; }

	private:
		int _kind;		// 發出氣功
		int _x, _y;		// 發出氣功的位置
		int _action;		// 招式的第幾個frame
		int _oid;		// 氣功的id
		int _facing;		// 數量及正反
	};

	class wpoint {
	public:
		wpoint() :_x{ -1 }, _y{ -1 }, _weaponact{ -1 }, _attacking{ -1 }, _cover{ -1 },
			_dvx{ -1 }, _dvy{ -1 }, _dvz{ -1 }{}
		wpoint(int x, int y, int weaponact, int attacking, int cover, int dvx, int dvy, int dvz) :
			_x{ x }, _y{ y }, _weaponact{ weaponact }, _attacking{ attacking }, _cover{ cover },
			_dvx{ dvx }, _dvy{ dvy }, _dvz{ dvz }{}
	private:
		int _x, _y;			// 物品的位置
		int _weaponact;		// 物品的frame
		int _attacking;		// 此武器是否具有攻擊性
		int _cover;			// 是否覆蓋人物
		int _dvx, _dvy, _dvz;	// 丟出時的飛行
	};

	class cpoint {
	public:
		cpoint() :_kind{ -1 }, _x{ -1 }, _y{ -1 }, _vaction{ -1 }, _aaction{ -1 }, _taction{ -1 },
			_injury{ -1 }, _hurtable{ -1 }, _decrease{ -1 }, _throwvx{ -1 }, _throwvy{ -1 }, _throwvz{ -1 },
			_backhurtact{ -1 }, _fronthurtact{ -1 }{}
		
		void setKind(int k) {
			_kind = k;
		}
		void setLoation(int x,int y) {
			_x = x; _y = y;
		}
		void setVaction(int v) {
			_vaction = v;
		}
		void setAction(int a, int t) {
			_aaction = a; _taction = t;
		}
		void setInjury(int j) {
			_injury = j;
		}
		void setHurtable(int h) {
			_hurtable = h;
		}
		void setDecrese(int d) {
			_decrease = d;
		}
		void setThrow(int x,int y,int z) {
			_throwvx = x;
			_throwvy = y;
			_throwvz = z;
		}
		void setHurtAct(int b, int f) {
			_backhurtact = b;
			_fronthurtact = f;
		}

		int getKind() { return _kind; }
		int getX() { return _x; }
		int getY() { return _y; }
		int getVaction() { return _vaction; }
		int getAaction() { return _aaction; }
		int getTaction() { return _taction; }
		int getInjury() { return _injury; }
		int getHurtable() { return _hurtable; }
		int getDecrese() { return _decrease; }
		int getThrowvx() { return _throwvx; }
		int getThrowvy() { return _throwvy; }
		int getThrowvz() { return _throwvz; }
		int getFHurtAct() { return _fronthurtact; }
		int getBHurtAct() { return _backhurtact; }

	private:
		int _kind;
		int _x, _y;
		int _vaction;
		int _aaction, _taction;
		int _injury;
		int _hurtable;
		int _decrease;
		int _throwvx,_throwvy,_throwvz;
		int _backhurtact, _fronthurtact;
	};

	class hitbox{
	public:
		hitbox() {
			_x = _y = _w = _h = 0;
		}
		void copy(const hitbox &other) {
			if (&other != this) {
				_x = other._x;
				_y = other._y;
				_w = other._w;
				_h = other._h;
			}
		}

		void set(int x,int y,int w,int h) {
			_x = x;
			_y = y;
			_w = w;
			_h = h;
		}

		int getX() {
			return _x;
		}
		int getY() {
			return _y;
		}
		int getW() {
			return _w;
		}
		int getH() {
			return _h;
		}
	private:
		int _x, _y, _w, _h;
	};

	class Frame {
	public:	
		Frame() {
			_id = 0;
			_Num_of_hitbox = 0;
			_have_itr = false;
			_have_cpoint = false;
			_have_wpoint = false;
			_have_opiont = false;
		}

		~Frame() {
			delete _hitbox;
		}


		void addBody(int x,int y,int w,int h) {
			_Num_of_hitbox++;
			if (_Num_of_hitbox == 1) {
				hitbox* _hitbox = new hitbox();
				_hitbox->set(x, y, w, h);
			}
			else{
				hitbox* temp = new hitbox[_Num_of_hitbox];
				int i;
				for (i = 0; i < _Num_of_hitbox - 1; i++) {
					(temp + i)->copy(*(_hitbox + i));
				}
				(temp + i)->set(x, y, w, h);
				delete _hitbox;
				_hitbox = temp;
			}
		}

		void setBasic(int id, int pic, int wait, int next, int mp, int x, int y, int sound) {
			_id = id;_pic = pic;_wait = wait;_next = next;
			_mp = mp;_center_x = x;_center_y = y;_sound = sound;		// 聲音
		}

		void setItr(int kind, int _x, int _y, int _w, int _h, int z_width, 
			int dvx, int dvy, int fall, int vrest, int bdefend, int injury,int effect) {
			_have_itr = true;
			_i = itr(kind,_x,_y,_w,_h,z_width,dvx,dvy,fall,vrest,bdefend,injury,effect);
		}
		
		void setWpoint(int x, int y, int weaponact, int attacking, int cover, int dvx, int dvy, int dvz) {
			_have_wpoint = true;
			_wp = wpoint(x, y, weaponact, attacking, cover, dvx, dvy, dvz);
		}

		void setCpointBasic(int kind, int x, int y) {
			_have_cpoint = true;
			_cp.setKind(kind);
			_cp.setLoation(x, y);
		}
		void setCpointING(int vaction, int decrease, int hurtable) {
			_cp.setVaction(vaction);
			_cp.setDecrese(decrease);
			_cp.setHurtable(hurtable);
		}
		void setCpointAction(int aaction, int taction) {
			_cp.setAction(aaction, taction);
		}
		void setCpointThrow(int injury, int throwvx, int throwvy, int throwvz) {
			_cp.setInjury(injury);
			_cp.setThrow(throwvx, throwvy, throwvz);
		}
		void setCpiontED(int backhurtact, int fronthurtact) {
			_cp.setHurtAct(backhurtact, fronthurtact);
		}

		void setOpoint(int kind, int x, int y, int action, int oid, int facing) {
			_have_opiont = true;
			_op.setKind(kind);
			_op.setLocation(x, y);
			_op.setAction(action);
			_op.setOid(oid);
			_op.setFacing(facing);
		}

		int _id;
		int _pic;		// 哪張圖片
		int _wait;		// 持續多久
		int _next;		// 下一格狀態
		int _mp;			// 消耗多少魔力
		int _center_x;	// 腳色中心
		int _center_y;	// 腳色腳的部位
		int _sound;		// 聲音

		int _Num_of_hitbox;	//hitbox的數量
		hitbox* _hitbox;
		
		bool _have_itr;		// 是否有攻擊判定
		itr _i;

		bool _have_opiont;	// 是否有氣功類的攻擊
		opoint _op;

		bool _have_wpoint;
		wpoint _wp;

		bool _have_cpoint;
		cpoint _cp;
	};


}