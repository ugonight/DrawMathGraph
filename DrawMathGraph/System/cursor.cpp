#include "DxLib.h"

#include "cursor.h"


Cursor::Cursor() : 
	mX(0),mY(0),
	mInputL(false),mInputR(false),
	mClickL(false),mClickR(false),
	mUpL(false),mUpR(false),
	mCursorNum(0)
{
	LoadDivGraph("cursor.png", 3, 3, 1, 32, 32, mCursorGraph);
}


Cursor::~Cursor()
{
}

void Cursor::update() {
	// É}ÉEÉXèÛë‘éÊìæ
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		mClickL = !mInputL;
		mInputL = true;
	}
	else {
		mUpL = mInputL;
		mInputL = false;
	}
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		mClickR = !mInputR;
		if (mClickR) mCursorNum++; mCursorNum %= 3;
		mInputR = true;
	}
	else {
		mUpR = mInputR;
		mInputR = false;
	}

	GetMousePoint(&mX, &mY);
}

void Cursor::draw() {
	DrawGraph(mX, mY, mCursorGraph[mCursorNum], TRUE);
}

int Cursor::GetX() { return mX; }
int Cursor::GetY() { return mY; }
bool Cursor::GetInputL() { return mInputL; }
bool Cursor::GetInputR() { return mInputR; }
bool Cursor::GetClickL() { return mClickL; }
bool Cursor::GetClickR() { return mClickR; }
bool Cursor::GetUpL() { return mUpL; }
bool Cursor::GetUpR() { return mUpR; }
int Cursor::GetCursorNum() { return mCursorNum; }