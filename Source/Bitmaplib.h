#pragma once
#include "Frame.h"
namespace game_framework {
	class Bitmaplib {
	public:
		Bitmaplib();
		void LoadBitmap();

		void selectByNum(int ch, int n,int index,int x, int y);

		void selectOpiont(int ch, int n, int index, int x, int y);
	private:
		CMovingBitmap tempPic[2][140];	//人物的圖片
		CMovingBitmap FirenPic[2][190];	//人物的圖片
		CMovingBitmap DeepPic[2][180];	//人物的圖片
		CMovingBitmap FreezePic[2][170];	//人物的圖片

		CMovingBitmap weapon[2][35];	//球棒的圖片

		CMovingBitmap deep_ball[2][8];	
		CMovingBitmap freeze_ball[2][8];
	};

	class Framelib {
	public:
		Framelib() {

		}
		void init();

		std::map<int, Frame>* getFrame(int n) {
			switch (n){
			case 0: {
				return &Frams_deep; 
				break;
			}
			case 1: {
				return &Frams_freeze; 
				break;
			}
			case 2: {
				return &Frams_firen; 
				break;
			}
			default: {
				return &Frams_t; 
				break;
			}
			}
		}

		std::map<int, Frame>* getWeaponFrame(int n) {
			switch (n) {
			case 0: {
				return &Frams_weapon0;
				break;
			}
			case 1: {
				return &Frams_weapon1;
				break;
			}
			default: {
				return &Frams_weapon7;
				break;
			}
			}
		}
	
		std::map<int, Frame>* getobjFrame(int n) {
			switch (n) {
			case 203: {
				return &deep_ball;
				break;
			}
			case 209: {
				return &freeze_ball;
				break;
			}
			default: {
				return &deep_ball;
				break;
			}
			}
		}
	private:
		int * extra(std::string &line, std::string *tar, int number);
		void  loadFrame();

		std::map<int, Frame> Frams_t;
		std::map<int, Frame> Frams_firen;
		std::map<int, Frame> Frams_deep;
		std::map<int, Frame> Frams_freeze;

		std::map<int, Frame> Frams_weapon0;
		std::map<int, Frame> Frams_weapon1;
		std::map<int, Frame> Frams_weapon7;

		std::map<int, Frame> deep_ball;
		std::map<int, Frame> freeze_ball;
	};
}