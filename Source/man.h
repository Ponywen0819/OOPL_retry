#pragma once

#include "Bitmaplib.h"
#include "skills.h"
#include "Area.h"

#define height 28

namespace game_framework {

	class man{
	public:
		man() {
			charector = 0;
			_x = _y = _z = 0;
			_mode = 0;
			for (int i = 0; i < 7; i++)	flag[i] = false;
			for (int i = 0; i < 4; i++)	_dir[i] = false;
			jumpAnimationGap = 0;
			attAnimationGap = 0;
			recoverGap = 50;
			_Double_Tap_Gap = 30;
			initG = height;
			commandBuffer = "";
			setJumpCount();
			_outofctrl = false;
			first_att_animation = true;
			stonkcount = 6;
			punch_fall = 2;
			isStonk = false;
			Body.init(_x+25, _y+15, 25, 64);
		}
		man(int x, int y);
		void init(Bitmaplib *l, man *m, int n);		// 設定初始庫
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
		bool isDizzy() {								
			return isStonk;
		}						
	protected:
		virtual void otherCommand(int n);
		virtual void readOtherList();
		vector<std::string> commandList;		// 被讀取的指令列表
		int _mode;								// 目前動作
		bool _outofctrl;					
	
		void setPosotion(int n);
		void caculateZ(int frame,int x,int z);
		void setZ();


		void checkFlag();
		void checkBuff();
		void specialEvent();
		void readCommand();

		// 計數器

		void setTimmer(int t) {
			time = t;
		}
		void Count() {
			if (time > 0) time--;
		}
		bool isTime() {
			return time == 0;
		}

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

		// 處理暈眩計數

		void setdizzyCount(int t);
		void dizzyCount();
		bool dizzyCountisZero();
		// 擊飛動作

		// 指令輸入間隔

		void setCountDwon();					//連點倒數
		void resetCountDown();					//連點倒數歸零

	private:
		int		body_x, body_y, body_w, body_h;
		int		charector;						// 選擇之腳色
		int		_x, _y,_z;						// 人物位置
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
		int		tempf;								

		float	a1, a2, a3,a4;						// 曲線方程項
		float	tempx;
		float	FrameCount;						// 曲線方城參數

		bool	isStonk;
		bool	Face_to_Left;					// 面相方向
		bool	_dir[4];						// 方向
		bool	first_att_animation;
		bool	is_jumping;						// 是否在跳躍
		bool	flag[7];						// keyboard input flag
		bool	Alive;							// 是否活著
		
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
		Bitmaplib *	lib;
		man *		mans;						// 在場上的人	
	};
}
