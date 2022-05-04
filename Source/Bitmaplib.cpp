#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <string>
#include <map>
#include "Frame.h"
#include <fstream>
#include <sstream>
#include "Bitmaplib.h"

namespace game_framework {

	Bitmaplib::Bitmaplib() {}

	void Bitmaplib::LoadBitmap() {
		std::string path;
		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\temp\\all\\" + std::to_string(i) + ".bmp";
			tempPic[1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\temp\\all\\" + std::to_string(140+i) + ".bmp";
			tempPic[0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

		for (int i = 0; i < 190; i++) {
			path = ".\\Bitmaps\\firen\\" + std::to_string(i) + ".bmp";
			FirenPic[1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 190; i++) {
			path = ".\\Bitmaps\\firen\\" + std::to_string(190 + i) + ".bmp";
			FirenPic[0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

		for (int i = 0; i < 180; i++) {
			path = ".\\Bitmaps\\deep\\" + std::to_string(i) + ".bmp";
			DeepPic[1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 180; i++) {
			path = ".\\Bitmaps\\deep\\" + std::to_string(180 + i) + ".bmp";
			DeepPic[0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

		for (int i = 0; i < 170; i++) {
			path = ".\\Bitmaps\\freeze\\" + std::to_string(i) + ".bmp";
			FreezePic[1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 170; i++) {
			path = ".\\Bitmaps\\freeze\\" + std::to_string(170 + i) + ".bmp";
			FreezePic[0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

		for (int i = 0; i < 4; i++) {
			path = ".\\Bitmaps\\freeze_ball\\" + std::to_string(i) + ".bmp";
			freeze_ball[1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 4; i++) {
			path = ".\\Bitmaps\\freeze_ball\\" + std::to_string(4 + i) + ".bmp";
			freeze_ball[0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

		for (int i = 0; i < 4; i++) {
			path = ".\\Bitmaps\\deep_ball\\" + std::to_string(i) + ".bmp";
			deep_ball[1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 4; i++) {
			path = ".\\Bitmaps\\deep_ball\\" + std::to_string(4 + i) + ".bmp";
			deep_ball[0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

	}

	void Bitmaplib::selectByNum(int ch,int n, int index, int x, int y) {
		switch (ch){
		case 0: {
			DeepPic[index][n].SetTopLeft(x, y);
			DeepPic[index][n].ShowBitmap();
			break;
		}
		case 1: {
			FreezePic[index][n].SetTopLeft(x, y);
			FreezePic[index][n].ShowBitmap();
			break;
		}
		case 2: {
			FirenPic[index][n].SetTopLeft(x, y);
			FirenPic[index][n].ShowBitmap();
			break;
		}
		default:
			tempPic[index][n].SetTopLeft(x, y);
			tempPic[index][n].ShowBitmap();
			break;
		}
	}

	void Bitmaplib::selectOpiont(int ch, int n, int index, int x, int y) {
		switch (ch){
		case 203: {
			deep_ball[index][n].SetTopLeft(x, y);
			deep_ball[index][n].ShowBitmap();
			break;
		}
		case 209: {
			freeze_ball[index][n].SetTopLeft(x, y);
			freeze_ball[index][n].ShowBitmap();
			break;
		}
		default:
			break;
		}
	}
	void Framelib::init() {
		loadFrame();
	}

	int* Framelib::extra(std::string &line, std::string *tar, int number) {
		int *value = new int[number];
		for (int i = 0; i < number; i++)	value[i] = 0;
		for (int i = 0; i < number; i++) {
			unsigned int temp = 0;
			temp = line.find(tar[i], temp);
			if (temp != std::string::npos) {
				temp += tar[i].length() + 2;
				std::string temp_id = "";
				while (line[temp] != ' ' && (temp < line.size())) {
					temp_id += line[temp++];
				}
				value[i] = std::stoi(temp_id);
			}
		}
		return value;
	}

	void Framelib::loadFrame() {
		std::string path[9] = { ".\\data\\t.txt",".\\data\\firen.txt",".\\data\\deep.txt",".\\data\\freeze.txt",
			".\\data\\weapon0.txt",".\\data\\weapon1.txt",".\\data\\weapon7.txt",
			".\\data\\deep_ball.txt",".\\data\\freeze_ball.txt" };
		std::map<int, Frame>* f[9] = {&Frams_t,&Frams_firen,&Frams_deep,&Frams_freeze,
			&Frams_weapon0,&Frams_weapon1,&Frams_weapon7,
			&deep_ball ,&freeze_ball };
		for (int ch = 0; ch < 9; ch++) {
			std::ifstream ifs(path[ch].c_str(), std::ios::in);
			if (!ifs.is_open()) {
				TRACE("Failed to open file.");
			}
			else {
				std::string s;
				while (std::getline(ifs, s)) {
					if (s.substr(0, 7) == "<frame>") {
						Frame a;
						int b = 8;
						std::string id = "";
						while (s[b] != ' ') {
							id += s[b++];
						}
						a._id = std::stoi(id);
						std::getline(ifs, s);
						std::string g[13] = { "pic","state","wait","next","dvx","dvy","centerx","centery",
							"hit_a","hit_d","hit_j","mp","sound"};
						int *temp_basic = extra(s, g, 13);
						a.setBasic(temp_basic); 

						std::getline(ifs, s);       //換下一行
						while (s != "<frame_end>") {
							if (s == "   wpoint:") {
								std::getline(ifs, s);
								std::string w[8] = { "x","y","weaponact","attacking","cover","dvx","dvy","dvz" };

								a.setWpoint(extra(s, w, 8));
							}
							else if (s == "   bdy:") {
								std::getline(ifs, s);
								std::string btar[4] = { "x","y","w","h" };

								a.addBody(extra(s, btar, 4));
							}
							else if (s == "   itr:") {
								std::getline(ifs, s);
								std::string btar[16] = { "kind","x","y","w","h","z_width","dvx","dvy","fall","vrest","arest"
									,"bdefend","injury","effect","catchingact","caughtact" };
								a.setItr(extra(s, btar, 16));
							}
							else if (s == "   opoint:") {
								std::getline(ifs, s);
								std::string btar[6] = { "kind","x","y","action","oid","facing" };
								a.setOpoint(extra(s, btar, 6));
							}
							else if (s == "   cpoint:") {
								std::getline(ifs, s);
								std::string btar[12] = { "kind","x","y","vaction","aaction","taction"
								,"hurtable","throwx","throwy","throwz","throwinjury","decrease" };
								a.setCpoint(extra(s, btar, 12));
							}
							std::getline(ifs, s);       //換下一行
						}
						(*(f[ch]))[a._id] = a;
					}
				}
				ifs.close();
			}
			ifs.close();
		}
		TRACE("%d\n", deep_ball[0]._pic);
	}
}