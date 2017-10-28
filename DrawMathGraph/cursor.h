#pragma once
class Cursor
{
private:
	int mX, mY;
	bool mInputL, mInputR;
	bool mClickL, mClickR;
	bool mUpL, mUpR;
	int mCursorGraph[3];
	int mCursorNum;

public:
	Cursor();
	~Cursor();

	void update();
	void draw();

	int GetX(); int GetY();
	bool GetInputL();
	bool GetInputR();
	bool GetClickL();
	bool GetClickR();
	bool GetUpL();
	bool GetUpR();
	int GetCursorNum();	//0:‰”•M 1:–îˆó 2:Á‚µƒSƒ€
};

