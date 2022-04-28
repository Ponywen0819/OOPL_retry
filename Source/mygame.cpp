/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "man.h"
#include "skills.h"
#include "Bitmaplib.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////
int player1 = -1, player2 = -1,pos = 0;
boolean a = FALSE;

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g){
}

void CGameStateInit::OnInit(){
	ShowInitProgress(0);
	
	menu.LoadBitmap();
}

void CGameStateInit::OnBeginState(){
	chose = 0;
	windows = 0;			//0為開始結束,1為選角畫面
	checkin_1 = 0;
	checkin_2 = 0;
	player1_index = 0;
	player2_index = 0;
	lock_1 = -1;
	lock_2 = -1;
	CountDown = FALSE;
	start = FALSE;
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
	const char KEY_UP = 0x26;	// keyboard上箭頭
	const char KEY_DOWN = 0x28;	// keyboard下箭頭
	const char KEY_SPACE = 0x20; // keyboard空白
	const char KEY_S = 0x53;	// keyboard S
	const char KEY_A = 0x41;	// keyboard A
	const char KEY_D = 0x44; // keyboard D
	const char KEY_K = 75; // keyboard D
	const char KEY_LEFT = 37; // keyboard D
	const char KEY_RIGHT = 39; // keyboard D
	// TRACE("button key  %d\n", nChar);

	if (windows == 0) {
		if (nChar == KEY_UP && chose == 1) {
			chose = 0;
		}
		if (nChar == KEY_DOWN && chose == 0) {
			chose = 1;
		}
		if (nChar == KEY_SPACE && chose == 0) {
			windows = 1;
		}
		if (nChar == KEY_SPACE && chose == 1) {
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
		}
	}


	else if (windows == 1 && CountDown == FALSE) {
		if (nChar == KEY_S && checkin_1 == 0) {
			checkin_1 = 1;
			player1 = 0;
		}
		if (nChar == KEY_K && checkin_2 == 0) {
			checkin_2 = 1;
			player2 = 0;
		}

		if (checkin_1 == 1 && lock_1 < 1) {
			if (nChar == KEY_A) {
				player1_index--;
			}
			if (nChar == KEY_D) {
				player1_index++;
			}
			if (nChar == KEY_S) {
				lock_1++;
			}
			player1 = menu.Get_player1(player1_index);
		}
		if (checkin_2 == 1 && lock_2 < 1) {
			if (nChar == KEY_LEFT) {
				player2_index--;
			}
			if (nChar == KEY_RIGHT) {
				player2_index++;
			}
			if (nChar == KEY_K) {
				lock_2++;
			}
			player2 = menu.Get_player2(player2_index);
		}

		if ((lock_1 == 1 && lock_2 == 1) || (lock_1 == 1 && lock_2 == -1) || (lock_1 == -1 && lock_2 == 1)) {
			CountDown = TRUE;
		}

	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point){  //滑鼠處理
	//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow(){

	if (windows == 0) {
		menu.OnShowMenu(1);
		chose == 0 ? menu.OnShowSelect(0) : menu.OnShowSelect(1);
	}
	else if (windows == 1) {
		menu.OnShowMenu(2);
		if (checkin_1 == 1) {
			menu.OnShowChar1(player1);
		}
		if (checkin_2 == 1) {
			menu.OnShowChar2(player2);
		}
		menu.OnShowCharLock(lock_1, lock_2);
		if (CountDown) {
			start = menu.OnShowCountDown(lock_1, lock_2);
			if (start) {
				GotoGameState(GAME_STATE_RUN);
			}
		}
	}
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g){
}

void CGameStateOver::OnMove(){
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState(){
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit(){
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow(){
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g){
	
}

CGameStateRun::~CGameStateRun(){
	delete[] all;
}

void CGameStateRun::OnBeginState(){
	Man[0].setInitPosotion(300, 450);
	Man[1].setInitPosotion(550, 450);
	Man[0].setCH(3);
	Man[0].init(&Blib, Man,2,&bar,Flib.getFrame(3));
	
	Man[1].setCH(0);
	Man[1].init(&Blib, Man,2,&bar,Flib.getFrame(0));
}	

void CGameStateRun::OnMove(){
	skills.check();
	Man[0].OnMove();
	Man[1].OnMove();
	skills.onMove();
}

void CGameStateRun::OnInit(){
	bar.LoadBitmap();

	ShowInitProgress(33);	
	Blib.LoadBitmap();

	ShowInitProgress(70);
	Flib.init();
	
	all = new obj*[2];
	numOfObj = 2;
	all[0] = Man;
	all[1] = (Man + 1);

	Man[0].getAllObj(all, 2);
	Man[1].getAllObj(all, 2);
	lf.init();
	temp1.init();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	const char KEY_LEFT  = 0x25;	// keyboard左箭頭
	const char KEY_UP    = 0x26;	// keyboard上箭頭
	const char KEY_RIGHT = 0x27;	// keyboard右箭頭
	const char KEY_DOWN  = 0x28;	// keyboard下箭頭
	const char KEY_SPACE = 0x20;	// keyboard空白鍵
	const char KEY_Z = 90;			// keyboard Z

	// TRACE("button key  %d", nChar);

	if (nChar == KEY_LEFT) {
		Man[0].setComm(1);
	}
	else if (nChar == KEY_RIGHT) {
		Man[0].setComm(2);
	}
	else if (nChar == KEY_UP) {
		Man[0].setComm(3);
	}
	else if (nChar == KEY_DOWN) {
		Man[0].setComm(4);
	}
	else if (nChar == KEY_SPACE) {
		Man[0].setComm(5);
	}
	else if (nChar == KEY_Z) {
		Man[0].setComm(6);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
	const char KEY_LEFT =	0x25;	// keyboard左箭頭
	const char KEY_UP =		0x26;	// keyboard上箭頭
	const char KEY_RIGHT =	0x27;	// keyboard右箭頭
	const char KEY_DOWN =	0x28;	// keyboard下箭頭
	const char KEY_SPACE =	0x20;	// keyboard空白鍵
	const char KEY_Z =		90;		// keyboard Z

		
	//haha
	//Hie
	//豬威比ＮＩＣＩ
	//SIMPLELIFE超柔抽取衛生紙
	//臣女喜歡忠貞之鳥
	
	if (nChar == KEY_LEFT) {
		Man[0].cComm(1);
	}
	else if (nChar == KEY_RIGHT) {
		Man[0].cComm(2);
	}
	else if (nChar == KEY_UP) {
		Man[0].cComm(3);
	}
	else if (nChar == KEY_DOWN) {
		Man[0].cComm(4);
	}
	else if (nChar == KEY_SPACE) {
		Man[0].cComm(5);
	}
	else if (nChar == KEY_Z) {
		Man[0].cComm(6);
	}
}

// 處理滑鼠的動作
void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  {
	bar.Player1HPState(20, 10);
	bar.Player1MPState(90);
}


// 處理滑鼠的動作
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	{
	
}

// 處理滑鼠的動作
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

// 處理滑鼠的動作
void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  {
	bar.Player2HPState(20, 10);
	bar.Player2MPState(90);
}

// 處理滑鼠的動作
void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	{
}

// 顯示
void CGameStateRun::OnShow() {

	lf.showmap(pos);

	Man[0].onShow();
	Man[1].onShow();
	skills.onShow();
	bar.OnShowBar(player1, player2);
	
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f, *fp;
	f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 255, 0));
	char str[500];								// Demo 數字對字串的轉換
	sprintf(str, "MAN1 _out : %d  X : %d Y : %d Z : %d  mode : %d next : %d state: %d"
		, Man[0].out(), Man[0].getx(), Man[0].gety(), Man[0].getz(),Man[0].gotMode(),Man[0].getNext(),Man[0].getState());
	pDC->TextOut(0, 50, str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();

	
}

}