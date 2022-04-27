#pragma once
#include "Frame.h"
namespace game_framework {
	class Bitmaplib {
	public:
		Bitmaplib();
		void LoadBitmap();

		void selectByNum(int ch, int n,int index,int x, int y);
	private:
		CMovingBitmap tempPic[2][140];	//人物的圖片
		CMovingBitmap FirenPic[2][190];	//人物的圖片
		CMovingBitmap DeepPic[2][180];	//人物的圖片
		CMovingBitmap FreezePic[2][170];	//人物的圖片

		CMovingBitmap weapon[2][35];	//球棒的圖片
	};

	class Framelib {
	public:
		Framelib() {

		}
		void init();

		std::map<int, Frame>* getFrame(int n) {
			switch (n){
			case 0: {
				return &Frams_t; 
			}
			case 1: {
				return &Frams_firen; 
			}
			case 2: {
				return &Frams_deep; 
			}
			default: {
				return &Frams_freeze; 
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

	};
}