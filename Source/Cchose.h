#pragma once
namespace game_framework {


	class Cchose{
	public:
		Cchose();
		~Cchose();
		void LoadBitmap();
		void OnShowMenu(int index);											// 將圖形貼到畫面
		void OnShowSelect(int index);
		void OnShowChar1(int index);
		void OnShowChar2(int index);
		bool OnShowCountDown(int player2);
		bool IsEnd();											//End chosing Charactor
		void cal_1(int player1_index);
		void cal_2(int player2_index);
		int Get_player1();
		int Get_player2();
	protected:
		bool is_end;
		CMovingBitmap charmenu;                         //選角背景
		CMovingBitmap character[3];						//角色
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap back;								//背景色塊
		CMovingBitmap title;							//標題
		CMovingBitmap option[4];						//正反
		CMovingBitmap player[2];
		CAnimation cma_ani;
		CAnimation CountDown;
		CAnimation name[3];

	private:
		int cma_x[4],cma_y[2];
		int player1, player2;
		
	};

	







}