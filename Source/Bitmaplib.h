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
		CMovingBitmap FreezePic[2][170];//人物的圖片
		CMovingBitmap HunterPic[2][140];//人物的圖片
		CMovingBitmap BanditPic[2][140];//人物的圖片

		CMovingBitmap weapon0[2][40];	//球棒的圖片
		CMovingBitmap weapon1[2][6];	//石頭的圖片
		CMovingBitmap weapon7[2][40];	//冰劍的圖片

		
		CMovingBitmap deep_ball[2][8];	

		CMovingBitmap fire_ball[2][12];
		CMovingBitmap gf[2][16];
		CMovingBitmap fla[2][18];
		CMovingBitmap exp[2][15];

		CMovingBitmap freeze_ball[2][8];
		CMovingBitmap clo[2][28];
		CMovingBitmap ww[2][11];
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
			case 10: {
				return &Frams_weapon0;
				break;
			}
			case 11: {
				return &Frams_weapon1;
				break;
			}
			case 12: {
				return &Frams_weapon7;
				break;
			}
			case 203: {
				return &deep_ball;
				break;
			}
			case 209: {
				return &freeze_ball;
				break;
			}
			case 210: {
				return &fire_ball;
				break;
			}
			case 211: {
				return &gf;
				break;
			}
			case 212: {
				return &flame;
				break;
			} 
			case 213: {
				return &explosion;
				break;
			}
			case 214: {
				return &clo;
				break;
			}
			case 215: {
				return &ww;
				break;
			}
			default: {
				return &Frams_t; 
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
		std::map<int, Frame> clo;
		std::map<int, Frame> ww;
		std::map<int, Frame> explosion;
		std::map<int, Frame> flame;
		std::map<int, Frame> gf;
		std::map<int, Frame> fire_ball;

	};
}