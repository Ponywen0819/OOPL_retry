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
		//TRACE("numOf skills %d\n", numOfSkills);
		for (auto i = 0; i < numOfSkills; i++) {
			skills.at(i)->onMove();
		}
	}

	void skillsContainer::onShow() {
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
		/*_ani.setTopLeft(_x, _y);
		_ani.onShow();*/
	}

	super_att::super_att(int x, int y, int z, bool f, void *owner) : Skills(41,51, owner) {
		if (f) {
			setPostion(x + 40, y - 2, z);
		}
		else {
			setPostion(x - 2, y - 2, z);
		}
		setLastTime(12);
		
	}

	void super_att::init(bool f) {
		setDir(f);
		initPostion(_x, _y, 41, 51);
	}

	void super_att::onMove() {
		last();
	}

	void super_att::onShow() {
		//CDC *pDC = CDDraw::GetBackCDC();
		//CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
		//pp = pDC->SelectObject(&p);

		//CBrush *pb, b(RGB(0, 255, 0));				// 畫綠色 progress框
		//pb = pDC->SelectObject(&b);
		//pDC->Rectangle(_x, _y, _x + _w, _y + _h);
		//pDC->SelectObject(pp);						// 釋放 pen
		//pDC->SelectObject(pb);						// 釋放 brush
		//CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}