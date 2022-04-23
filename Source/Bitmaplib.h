#pragma once
namespace game_framework {
	class Bitmaplib {
	public:
		Bitmaplib();
		void LoadBitmap();

		void selectByNum(int n,int index,int x, int y);
	private:
		CMovingBitmap pic[4][2][140];	//人物的圖片
		CMovingBitmap weapon[2][35];	//球棒的圖片
	};

	class Framelib {
	public:
		Framelib();
		void init();
	private:
		std::map<int, Frame> Frams[4]
	};
}