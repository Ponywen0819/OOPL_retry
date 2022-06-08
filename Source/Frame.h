
#pragma once
#include "stdafx.h"


namespace game_framework {

	class itr {
	public:
		itr() {
			_kind = 0;
			_z_width = 0;
			_dvx = _dvy = 0;
			_fall = 0;
			_vrest = 0;
			_arest = 0;
			_bdefend = 0;
			_injury = 0;
			_catchingact = 0;
			_caughtact = 0;
			_effect = 0;
		}
		itr(int kind, int x, int y, int w, int h, int z_width,
			int dvx, int dvy, int fall, int vrest, int arest,int bdefend, int injury, int effect,int catchingact,int caughtact) :
			_kind{ kind }, _x{ x }, _y{ y }, _w{ w }, _h{ h }, _z_width{ z_width },_dvx{ dvx }, _dvy{ dvy },
			_fall{ fall }, _vrest{ vrest }, _arest{arest}, _bdefend{ bdefend }, _injury{ injury }, _effect{ effect }
			, _catchingact{ catchingact }, _caughtact{ caughtact }{}
		itr(const itr& ii) {
			_kind = ii._kind;
			_x = ii._x; 
			_y = ii._y; 
			_w = ii._w; 
			_h = ii._h;
			_z_width = ii._z_width;
			_dvx = ii._dvx; 
			_dvy = ii._dvy;
			_fall = ii._fall;
			_vrest = ii._vrest;
			_arest = ii._arest;
			_bdefend = ii._bdefend;
			_injury = ii._injury;
			_effect = ii._effect;
			_catchingact = ii._catchingact;
			_caughtact = ii._caughtact;
		}

		itr& operator=(const itr& ii) {
			if (this != &ii) { // 檢查自我賦值
				_kind = ii._kind;
				_x = ii._x; 
				_y = ii._y; 
				_w = ii._w; 
				_h = ii._h;
				_z_width = ii._z_width;
				_dvx = ii._dvx; 
				_dvy = ii._dvy;
				_fall = ii._fall;
				_vrest = ii._vrest;
				_arest = ii._arest;
				_bdefend = ii._bdefend;
				_injury = ii._injury;
				_effect = ii._effect;
				_catchingact = ii._catchingact;
				_caughtact = ii._caughtact;
			}

			return *this;
		}


		int getKind() { return _kind; }
		int getX() { return _x; }
		int getY() { return _y; }
		int getW() { return _w; }
		int getH() { return _h; }
		int getZ_width() { return _z_width; }
		int getDvx() { return _dvx; }
		int getDvy() { return _dvy; }
		int getFall() { return _fall; }
		int getVrest() { return _vrest; }
		int getArest() { return _arest; }
		int getBdefend() { return _bdefend; }
		int getInjury() { return _injury; }
		int getCatching() { return _catchingact; }
		int getCaught() {return _caughtact;}
		int get_effect() { return _effect; }

	private:
		int _kind;
		int _x, _y, _w, _h;
		int _z_width;
		int _dvx, _dvy;
		int _fall;
		int _vrest;
		int _arest;
		int _bdefend;
		int _injury;
		int _effect;
		int _catchingact;
		int _caughtact;
	};

	class opoint {
	public:
		opoint() :_kind{ -1 }, _x{ -1 }, _y{ -1 }, _action{ -1 }, _oid{ -1 }, _facing(-1){}

		opoint(const opoint& oo) {
			_kind = oo._kind;		// 發出氣功
			_x = oo._x;
			_y = oo._y;		// 發出氣功的位置
			_action = oo._action;		// 招式的第幾個frame
			_oid = oo._oid;		// 氣功的id
			_facing = oo._facing;		// 數量及正反
		}

		opoint& operator=(const opoint& oo) {
			if (this != &oo) { // 檢查自我賦值
				_kind = oo._kind;		// 發出氣功
				_x = oo._x;
				_y = oo._y;		// 發出氣功的位置
				_action = oo._action;		// 招式的第幾個frame
				_oid = oo._oid;		// 氣功的id
				_facing = oo._facing;		// 數量及正反
			}

			return *this;
		}
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

		wpoint& operator=(const wpoint& ww) {
			if (this != &ww) { // 檢查自我賦值
				_x = ww._x;
				_y = ww._y;
				_weaponact = ww._weaponact;
				_attacking = ww._attacking;
				_cover = ww._cover;
				_dvx = ww._dvx; _dvy = ww._dvy; _dvz = ww._dvz;
			}

			return *this;
		}

		int getX() { return _x; }
		int getY() { return _y; }
		int getf() { return _weaponact; }
		int get_weaponact() { return _weaponact; }
		int getattcking() { return _attacking; }
		int getcover() { return _cover; }
		int getdvx() { return _dvx; }
		int getdvy() { return _dvy; }
		int getdvz() { return _dvz; }
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

		cpoint& operator=(const cpoint& cc) {
			if (this != &cc) { // 檢查自我賦值
				_kind = cc._kind;
				_x = cc._x;
				_y = cc._y;
				_vaction = cc._vaction;
				_aaction = cc._aaction;
				_taction = cc._taction;
				_injury = cc._injury;
				_hurtable = cc._hurtable;
				_decrease = cc._decrease;
				_throwvx = cc._throwvx;
				_throwvy = cc._throwvy;
				_throwvz = cc._throwvz;
				_backhurtact = cc._backhurtact;
				_fronthurtact = cc._fronthurtact;
			}
			return *this;
		}

		void setKind(int k) {
			_kind = k;
		}
		void setLoation(int x, int y) {
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
		void setThrow(int x, int y, int z) {
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
		int _throwvx, _throwvy, _throwvz;
		int _backhurtact, _fronthurtact;
	};

	class hitbox {
	public:
		hitbox() {
			_x = _y = _w = _h = 0;
		}
		void copy(const hitbox *other) {
			if (other != this) {
				_x = other->_x;
				_y = other->_y;
				_w = other->_w;
				_h = other->_h;
			}
		}
		hitbox(const hitbox& hi) {
			_x = hi._x;
			_y = hi._y;
			_w = hi._w;
			_h = hi._h;
		}

		hitbox& operator=(const hitbox& hi) {
			if (this != &hi) { // 檢查自我賦值
				_x = hi._x;
				_y = hi._y;
				_w = hi._w;
				_h = hi._h;
			}

			return *this;
		}

		void set(int x, int y, int w, int h) {
			_x = x;
			_y = y;
			_w = w;
			_h = h;
		}

		int getX() { return _x; }
		int getY() { return _y; }
		int getW() { return _w; }
		int getH() { return _h; }
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
			_hitbox = nullptr;
		}
		~Frame() {
			if (_hitbox != nullptr) {
				delete _hitbox;
			}
		}

		Frame(const Frame &f) {
			_id = f._id;
			_pic = f._pic;
			_state = f._state;
			_wait = f._wait;
			_next = f._next;
			_mp = f._mp;
			_centerx = f._centerx;
			_centery = f._centery;
			_sound = f._sound;
			_dvx = f._dvx;
			_dvy = f._dvy;
			hit_a = f.hit_a;
			hit_d = f.hit_d;
			hit_j = f.hit_j;

			_Num_of_hitbox = f._Num_of_hitbox;
			_hitbox = new hitbox[_Num_of_hitbox];
			for (int i = 0; i < _Num_of_hitbox; i++) {
				*(_hitbox + i) = (*(f._hitbox + i));
			}
			_have_itr = f._have_itr;
			_i = f._i;

			_have_opiont = f._have_opiont;
			_op = f._op;

			_have_wpoint = f._have_wpoint;
			_wp = f._wp;

			_have_cpoint = f._have_cpoint;
			_cp = f._cp;

		}

		Frame& operator=(const Frame& f) {
			if (this != &f) { // 檢查自我賦值
				_id = f._id;
				_pic = f._pic; 
				_state = f._state;
				_wait = f._wait; 
				_next = f._next;
				_mp = f._mp; 
				_centerx = f._centerx; 
				_centery = f._centery;
				_sound = f._sound; 
				_dvx = f._dvx; 
				_dvy = f._dvy;
				hit_a = f.hit_a;
				hit_d = f.hit_d;
				hit_j = f.hit_j;

				_Num_of_hitbox = f._Num_of_hitbox;
				_hitbox = new hitbox[_Num_of_hitbox];
				for (int i = 0; i < _Num_of_hitbox; i++) {
					*(_hitbox + i) = *(f._hitbox + i);
				}
				_have_itr = f._have_itr;
				_i = f._i;

				_have_opiont = f._have_opiont;
				_op = f._op;

				_have_wpoint = f._have_wpoint;
				_wp = f._wp;

				_have_cpoint = f._have_cpoint;
				_cp = f._cp;
			}
			return *this;
		}

		void addBody(int *v) {
			_Num_of_hitbox++;
			if (_Num_of_hitbox == 1) {
				_hitbox = new hitbox();
				_hitbox[0].set(v[0], v[1], v[2], v[3]);
			}
			else {
				hitbox* temp = new hitbox[_Num_of_hitbox];
				int i;
				for (i = 0; i < _Num_of_hitbox - 1; i++) {
					temp[i] = _hitbox[i];
				}
				temp[i].set(v[0], v[1], v[2], v[3]);
				delete _hitbox;
				_hitbox = temp;
			}
			delete v;
		}

		void setBasic(int *data) {
			_pic = data[0];
			_state = data[1];
			_wait = data[2];
			_next = data[3];
			_dvx = data[4];
			_dvy = data[5];
			_centerx = data[6];
			_centery = data[7];
			hit_a = data[8];
			hit_d = data[9];
			hit_j = data[10];
			_mp = data[11];
			_sound = data[12];
			delete data;
		}

		void setItr(int *v) {
			_have_itr = true;
			_i = itr(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12],v[13],v[14],v[15]);
			delete v;
		}

		void setWpoint(int *v) {
			_have_wpoint = true;

			_wp = wpoint(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
			delete v;
		}

		void setCpoint(int *v) {
			_cp.setKind(v[0]);
			_cp.setLoation(v[1], v[2]);
			_cp.setVaction(v[3]);
			_cp.setAction(v[4], v[5]);
			_cp.setHurtable(v[6]);
			_cp.setThrow(v[7], v[8], v[9]);
			_cp.setInjury(v[10]);
			_cp.setDecrese(v[11]);
			delete v;
		}

		void setOpoint(int *v) {
			_have_opiont = true;
			_op.setKind(v[0]);
			_op.setLocation(v[1], v[2]);
			_op.setAction(v[3]);
			_op.setOid(v[4]);
			_op.setFacing(v[5]);
			delete v;
		}

		int _id;
		int _pic;		// 哪張圖片
		int _state;		// 狀態
		int _wait;		// 持續多久
		int _next;		// 下一格狀態
		int _mp;		// 消耗多少魔力
		int _centerx;	// 腳色中心
		int _centery;	// 腳色腳的部位
		int _sound;		// 聲音
		int _dvx, _dvy;	// 移動 
		int hit_a;		// 按下A的動作
		int hit_d;		// 按下D的動作
		int hit_j;		// 按下J的動作

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
