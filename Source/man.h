#pragma once

#include "Bitmaplib.h"
#include "skills.h"
#include "Area.h"
#include "CStateBar.h"
#include <string>
#include <map>
#include "Frame.h"

#define TEST true

namespace game_framework {

	#define height 28
	#define MAN_DIZZY 903
	class man{
	public:
		man() {
			Body.init(_x+25, _y+15, 25, 64);
			charector = 0;
			_x = _y = _z = 0;
			_mode = 0;
			jumpAnimationGap = 0;
			attAnimationGap = 0;
			recoverGap = 50;
			_Double_Tap_Gap = 30;
			stonkcount = 6;
			punch_fall = 2;
			initG = height;
			time = 0;
			
			commandBuffer = "";
			setJumpCount();

			for (int i = 0; i < 7; i++)	flag[i] = false;
			for (int i = 0; i < 4; i++)	_dir[i] = false;
			first_att_animation = true;
			_outofctrl = false;
			_isDizzy = false;
			jumpType = false;
			walk_Ani_dir = true;
			run_Ani_dir = true;
		}
		man(int x, int y);
		~man() {

		}
		void init(Bitmaplib *l, man *m, int n,CStateBar *state);		// 設定初始庫
		void setInitPosotion(int x, int y);			// 設定初始位置
		void LoadBitmap();							// 載入圖形

		void setComm(UINT comm);					// 設定指令
		void cComm(UINT comm);						// 取消指令

		void OnMove();								// 改變位置
		void onShow();								// 顯示

		void checkbeenatt(skillsContainer &con);	// 被攻擊偵測
		Skills* usingSkill();						// 有無使用招式
		bool NearBy(const man &other);				// 在旁邊
		bool FaceTo(const man &other);
		bool out() { return _outofctrl; }
		bool isDizzy() { return _isDizzy; }
		bool iscatch() { return _catching; }
		bool gotc() { return _Catch; }
		int gotMode() { return _mode; }
		int getx() { return _x; }
		int gety() { return _y; }
		int getz() { return _z; }
		int getNext() { return all[_mode]._next; }

	protected:
		bool inMotion;			// 是否在特殊動作裡


		int * extra(std::string &line, std::string *tar,int number);
		virtual void otherCommand(int n);
		virtual void readOtherList();
		vector<std::string> commandList;		// 被讀取的指令列表
		int _mode;								// 目前動作
		bool _outofctrl;					
	
		void setPosotion(int n);
		void caculateZ(int f, int x, int y, int z);
		void setZ();


		void checkFlag();
		void checkBuff();
		void specialEvent();
		void readCommand();

		void setDizzyCount() { dizzyCount = MAN_DIZZY; }

		// 計數器

		void setTimmer(int t) { time = t; }
		void Count() {if (time > 0) time--;}
		bool isTime() { return time == 0; }

		// 讀取Frame資料
		void loadFrame();				

		void backToRandon();			// 回到原始的狀態
		void toMotion(int next);				// 處發動作
		void nextFrame();				// 動作中的下一個Frame
		
		// 攻擊動作計數

		void attCount();
		bool attCountisZero();
		void setattCount();

		// 暈眩恢復計數

		void recoverCount();
		int recoverGap;							// 恢復計數
		int stonkcount;							// 暈眩指數

		// 跳躍計數

		void setJumpCount();
		void JumpCount();
		bool JumpCountisZero();
		bool jumping();

		// 一般受傷動作計數

		void setbeattenCount(int t);
		void beattenCount();
		bool beattenCountisZero();

		// 擊飛動作

		// 指令輸入間隔

		void setCountDwon();					//連點倒數
		void resetCountDown();					//連點倒數歸零

	private:

		int		charector;						// 選擇之腳色
		int		_x, _y,_z;						// 人物位置
		// 代表 前後 天地 上下
		int		_Double_Tap_Gap;				// 連點間隔
		int		jumpAnimationGap;					
		int		jumpMotionStand;				// 跳躍動作時間
		int		initG;							// 設定上升速度
		int		attAnimationGap;
		int		beatenMotionGap;
		int		punch_fall;
		int		dizzyGap;
		int		NumOfMan;						// 在場上的人
		int		time;							// 計數
		int		tempf;							//
		int		dizzyCount;						//

		float	a1, a2, a3,a4,a5;						// 曲線方程項
		float	tempx, tempy;
		float	FrameCount;						// 曲線方城參數

		bool	jumpType;
		bool	Face_to_Left;					// 面相方向
		bool	_dir[4];						// 方向
		bool	first_att_animation;
		bool	is_jumping;						// 是否在跳躍
		bool	flag[7];						// keyboard input flag
		bool	Alive;							// 是否活著
		bool	Fset;							// 是否要計算方城
		bool	_catching;						// 抓住別人
		bool	_Catch;							// 被抓住的狀態
		bool	_isDizzy;						// 暈眩狀態
		bool	_untouch;						// 無敵狀態
		bool	walk_Ani_dir;					// 走路動作的方向
		bool	run_Ani_dir;					// 跑步動作的方向

		area	Body;							// 身體HitBox

		std::string commandBuffer;				// input command buffer
		
		CAnimation stand[2];					// 站的動作
		CAnimation walk[2];						// 走的動作
		CAnimation run[2];						// 跑的動作
		
		CMovingBitmap test;
		CMovingBitmap squat[2];					// 蹲下動作
		CMovingBitmap readyJump[2];				// 準備跳動作
		CMovingBitmap littleJump[2];			// 原地跳動作
		CMovingBitmap bigJumpR[2];				// 衝刺跳動作
		CMovingBitmap bigJumpL[2];				// 衝刺跳動作
		CMovingBitmap kick[2][2];				// 踢動作
		CMovingBitmap flykick[2][2];			// 飛踢
		CMovingBitmap att[2][4];				// 攻擊動作
		CMovingBitmap bigatt[2][3];				// 衝攻動作

		Skills*		now;						// 現在的招式
		
		Bitmaplib *	lib;						// 圖片輸出

		CStateBar *	_s;							// 血量條

		man *		mans;						// 在場上的人	
		man *		gotCatch;					// 被抓的人
		
		std::map<int, Frame> all;
	};
}
