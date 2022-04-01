#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "skills.h"
#include "Bitmaplib.h"
#include "man.h"

namespace game_framework {
	skillsContainer::skillsContainer():
		numOfSkills{ 0 }{
		skills = {};
	}

	skillsContainer::~skillsContainer() {
		for (int i = 0; i < numOfSkills; i++) {
			delete skills.at(i);
		}

	}

	void skillsContainer::addSkills(Skills *new_skill) {
		if (new_skill != nullptr) {
			skills.push_back(new_skill);
			numOfSkills++;
		}
	}
	
	void skillsContainer::dleteSkills(int n) {
		if (n > numOfSkills) {
			return;
		}
		else {
			numOfSkills--;
			skills.erase(skills.begin()+n);
		}
	}

	void skillsContainer::onMove() {
		TRACE("%d\n", numOfSkills);
		for (auto i = 0; i < numOfSkills; i++) {
			//TRACE("%d \t %d\n ", skills.at(i),i);
			skills.at(i)->onMove();
		}
	}

	void skillsContainer::onShow() {
		TRACE("%d\n", numOfSkills);
		for (auto i = 0; i < numOfSkills; i++) {
			skills.at(i)->onShow();
		}
	}

	void skillsContainer::check() {
		int i = 0;
		while (i < numOfSkills){
			if (skills.at(i)->getLastTime() <= 0) {
				delete skills.at(i);
				skills.erase(skills.begin() + i);
				numOfSkills--;
			}
			else{
				i++;
			}
		}
	}

	Skills* skillsContainer::getskills(int n) {
		if (n >= numOfSkills) {
			return nullptr;
		}
		else{
			return skills.at(n);
		}
	}

	/*------------------------------------------------------------------------------------------------------------------------*/

	Skills::Skills():_dizzy{ 0 }, _cost{ 0 }, _danmage{ 0 }, _x{ 0 }, _y{ 0 }, _z{ 0 }, _w{ 0 }, _h{ 0 }{}

	Skills::Skills(const Skills &out) {
		_dizzy = out._dizzy; _cost = out._cost; _danmage = out._danmage; 
		_x = out._x; _y = out._y; _z = out._z;
		_w = out._w; _h = out._h;
	}
	
	Skills::Skills(int w, int h, void * owner) :_dizzy{ 0 }, _cost{ 0 }, _danmage{ 0 }, _x{ 0 }, _y{ 0 }, _z{ 0 }, _w{ w }, _h{ h }, _owner{owner}{
		_dizzy = 2;
	}
	
	void Skills::LoadBitmap() {
		
	}

	void Skills::onMove() {
		TRACE("basic Skill lunch\n");
	}

	void Skills::onShow() {
		TRACE("basic Skill show\n");
	}

	void Skills::last() {
		LastTime--;
	}

	//setter
	void Skills::setXY(int x,int y,int z) {
		_x = x; _y = y; _z = z;
	}
	void Skills::setDanmage(int danmage) {
		_danmage = danmage;
	}
	void Skills::setdizzy(int dizzy) {
		_dizzy = dizzy;
	}
	void Skills::setcost(int cost) {
		_cost = cost;
	}
	void Skills::setLastTime(int t) {
		LastTime = t;
	}

	//getter
	int Skills::getx() {
		return _x;
	}
	int Skills::gety() {
		return _y;
	}
	int Skills::getz() {
		return _z;
	}
	int Skills::getDanmage() {
		return _danmage;
	}
	int Skills::getdizzy() {
		return _dizzy;
	}
	int Skills::getcost() {
		return _cost;
	}

	int Skills::getLastTime() {
		return LastTime;
	}
	void * Skills::getowner() {
		return _owner;
	}

	/*------------------------------------------------------------------------------------------------------------------------*/
	
	punch::punch() :Skills(25,15,nullptr){
		setXY(0, 0, 0);
	}
	
	punch::punch(int x, int y, int z, bool FacetoLeft, bool LeftPunch, Bitmaplib *l,void *owner) : Skills(25, 15,owner) {
		if (FacetoLeft) {
			if (LeftPunch) setXY(x, y + 35, z);
			else setXY(x,y+35,z);
		}
		else{
			if (LeftPunch) setXY(x + 54, y + 35, z);
			else setXY(x + 59, y + 35, z);
		}
		lib = l;
		_ani.init(l);
		addBitmap(0);
		setLastTime(15);
	}

	void punch::init(Bitmaplib *l) {
		lib = l;
		_ani.init(l);
		addBitmap(0);
	}

	void punch::onMove() {
		TRACE("normal punch\n");
		last();
		_ani.onMove();
	}
	
	void punch::addBitmap(int i) {
		TRACE("normal punch load bitmap\n");
		_ani.addBitmap(i);
	}

	void punch::onShow() {
		TRACE("normal punch show\n");
		_ani.setTopLeft(getx(), gety());
		_ani.onShow();
	}


}