#pragma once

#define NODE_R 10

class Node
{
private:
	int mId;
	int mX, mY;
	int mFontHandle;

public:
	Node(int id,int x,int y);
	~Node();

	void update();
	void draw();

	int GetId();
	int GetX();
	int GetY();

	void SetX(int x);
	void SetY(int y);

	// ポイントがノードと接しているか返す
	bool ContainsPoint(int x,int y);
};

