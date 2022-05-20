#pragma once
namespace game_framework {


	class Cchose{
	public:
		Cchose();
		~Cchose();
		void LoadBitmap();
		void OnShowMenu(int index);											
		void OnShowSelect(int index);
		void OnShowStage(int index);
		void OnShowChar1(int index);
		void OnShowChar2(int index);
		void OnShowCharAni(int player1_lock, int player2_lock);
		void OnShowCharLock(int player, int index);
		bool OnShowCountDown(int player1_lock, int player2_lock);
		int Get_player1(int player1_index);
		int Get_player2(int player2_index);
	protected:
		bool is_end;
		CMovingBitmap charmenu;                    
		CMovingBitmap character[3];		
		CMovingBitmap logo;								
		CMovingBitmap back;						
		CMovingBitmap title;						
		CMovingBitmap team;
		CMovingBitmap option[6];						
		CMovingBitmap player[2];
		CMovingBitmap lock[3];
		CMovingBitmap how[2];
		CMovingBitmap stage[2];
		CAnimation cma_ani;
		CAnimation CountDown;
		CAnimation name[3];

	private:
		int cma_x[4],cma_y[2];
		int player1, player2;
		
	};

	







}