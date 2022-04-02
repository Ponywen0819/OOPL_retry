#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "skills.h"
#include "Bitmaplib.h"
#include "man.h"
#include "Area.h"

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
		//TRACE("%d\n", numOfSkills);
		for (auto i = 0; i < numOfSkills; i++) {
			//TRACE("%d \t %d\n ", skills.at(i),i);
			skills.at(i)->onMove();
		}
	}

	void skillsContainer::onShow() {
		//TRACE("%d\n", numOfSkills);
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

	/*------------------------------------------------------------------------------------------------------------------------*/
	
	punch::punch() :Skills(25,15,nullptr){
		setPostion(0, 0, 0);
	}
	
	punch::punch(int x, int y, int z, bool FacetoLeft, bool LeftPunch, Bitmaplib *l,void *owner) : Skills(25, 15,owner) {
		if (FacetoLeft) {
			if (LeftPunch) setPostion(x, y + 35, z);
			else setPostion(x,y+35,z);
		}
		else{
			if (LeftPunch) setPostion(x + 54, y + 35, z);
			else setPostion(x + 59, y + 35, z);
		}
		lib = l;
		_ani.init(l);
		addBitmap(0);
		setLastTime(15);
	}

	void punch::init( bool f) {
		setDir(f);
		initPostion(_x, _y, 20, 15);
	}

	void punch::onMove() {
		last();
		_ani.onMove();
		setPostion(_x, _y, _z);
	}
	
	void punch::addBitmap(int i) {
		_ani.addBitmap(i);
	}

	void punch::onShow() {
		_ani.setTopLeft(_x, _y);
		_ani.onShow();
	}
}