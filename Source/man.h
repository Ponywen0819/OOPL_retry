#pragma once

#include "Bitmaplib.h"
#include "skills.h"

namespace game_framework {

	class man{
	public:
		man();
		man(int x, int y);
		void init(Bitmaplib *l);
		void LoadBitmap();							// 載入圖形
		void setComm(UINT comm);					// 設定指令
		void cComm(UINT comm);						// 取消指令
		void setInitPosotion(int x,int y);			// 設定初始位置
		void OnMove();								// 改變位置
		void onShow();								// 顯示
		void checkbeenatt(skillsContainer &con);	// 被攻擊偵測
		Skills* usingSkill();						// 在此偵有無使用招式
	protected:
		virtual void otherCommand(int n);
		virtual void readOtherList();
		vector<std::string> commandList;		// 被讀取的指令列表
		int _mode;								// 目前動作
		bool _outofctrl;					
	
		void setPosotion(int n);
			
		void checkFlag();
		void checkBuff();
		void specialEvent();
		void readCommand();

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

		bool fly();

		// 指令輸入間隔

		void setCountDwon();					//連點倒數
		void resetCountDown();					//連點倒數歸零

	private:
		int body_x, body_y, body_w, body_h;
		int charector;							//選擇之腳色
		int _x, _y,_z;							//人物位置
		bool flag[7];							//keyboard input flag
		std::string commandBuffer;				//input command buffer
		int _Double_Tap_Gap;					//連點間隔
		bool Face_to_Left;						//面相方向
		bool _dir[4];							//方向
		int jumpAnimationGap;					
		int jumpMotionStand;					//跳躍動作時間
		bool is_jumping;						//是否在跳躍
		int initG;								//設定上升速度
		bool first_att_animation;
		int attAnimationGap;
		int beatenMotionGap;
		
		CAnimation stand[2];					// 站的動作
		CAnimation walk[2];						// 走的動作
		CAnimation run[2];						// 跑的動作
		CMovingBitmap squat[2];					// 蹲下動作
		CMovingBitmap readyJump[2];				// 準備跳動作
		CMovingBitmap littleJump[2];			// 原地跳動作
		CMovingBitmap bigJumpR[2];				// 衝刺跳動作
		CMovingBitmap bigJumpL[2];				// 衝刺跳動作
		CMovingBitmap kick[2][2];				// 踢動作
		CMovingBitmap flykick[2][2];			// 飛踢
		CMovingBitmap att[2][4];				//攻擊動作
		CMovingBitmap bigatt[2][3];				//衝攻動作
		Skills* now;							//現在的招式
		Bitmaplib *lib;
		
		int punch_fall;
		bool isStonk;
		int dizzyGap;
	};
}
