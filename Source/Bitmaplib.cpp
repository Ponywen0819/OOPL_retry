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
			pic[0][1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\temp\\all\\" + std::to_string(140+i) + ".bmp";
			pic[0][0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\firen\\" + std::to_string(i) + ".bmp";
			pic[1][1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\firen\\" + std::to_string(140 + i) + ".bmp";
			pic[1][0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\deep\\" + std::to_string(i) + ".bmp";
			pic[2][1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\deep\\" + std::to_string(140 + i) + ".bmp";
			pic[2][0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}

		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\freeze\\" + std::to_string(i) + ".bmp";
			pic[3][1][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
		for (int i = 0; i < 140; i++) {
			path = ".\\Bitmaps\\freeze\\" + std::to_string(140 + i) + ".bmp";
			pic[3][0][i].LoadBitmap((char *)path.c_str(), RGB(0, 0, 0));
		}
	}

	void Bitmaplib::selectByNum(int ch,int n, int index, int x, int y) {
		pic[ch][index][n].SetTopLeft(x, y);
		pic[ch][index][n].ShowBitmap();
	}

	void Framelib::init() {
		loadFrame();
	}

	int* Framelib::extra(std::string &line, std::string *tar, int number) {
		int *value = new int[number];
		for (int i = 0; i < number; i++)	value[i] = -1;
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
		std::string path[4] = { ".\\data\\t.txt",".\\data\\firen.txt",".\\data\\deep.txt",".\\data\\freeze.txt" };
		for (int ch = 0; ch < 4; ch++) {
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
						std::string g[10] = { "pic","state","wait","next","dvx","dvy","centerx","centery","sound","mp" };
						int *temp_basic = extra(s, g, 10);
						a.setBasic(temp_basic); 
						// TRACE("%d\n", a._next);

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
								std::string btar[7] = { "kind","x","y","w","h","catchingact","caughtact" };
								a.setItr(extra(s, btar, 7));
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
						switch (ch){
						case 0: {
							Frams_t[a._id] = a;
							break;
						}
						case 1: {
							Frams_firen[a._id] = a;
							break;
						}
						case 2: {
							Frams_deep[a._id] = a;
							break;
						}
						case 3: {
							Frams_freeze[a._id] = a;
							break;
						}
						}
					}
				}
				ifs.close();
			}
			ifs.close();
		}
	}
}