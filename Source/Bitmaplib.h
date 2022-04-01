#pragma once
namespace game_framework {
	class Bitmaplib {
	public:
		Bitmaplib();
		void LoadBitmap();

		void showBynumber(int i,int x,int y);
		// getter
		//CMovingBitmap *getpunch();
		void setPunchTopLeft(int x,int y);
		void showPunch();

		void setbeatenTopLeft(int step, bool FaceToLeft, int index,int x,int y);
		void showBeaten(int step, bool FaceToLeft, int index);

	private:
		CMovingBitmap punch;
		CMovingBitmap beaten1[2][2];
		CMovingBitmap beatenL2[2][2];
		CMovingBitmap beatenR2[2][2];
		CMovingBitmap dizzy[2];

	};

	class PAnimation{
	public:
		PAnimation() {}
		PAnimation(Bitmaplib *l);
		void init(Bitmaplib *l) {
			lib = l;
			num = 0;
			index = 0;
			_x = 0;
			_y = 0;
		}
		void addBitmap(int i);
		void setTopLeft(int x,int y);
		void onMove();
		void onShow();
	private:
		int num;
		int index;
		int _x, _y;
		std::vector<int> bitmapnumbers;
		Bitmaplib *lib;
	};
}