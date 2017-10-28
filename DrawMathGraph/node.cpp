#include <DxLib.h>
#include <math.h>
#include "node.h"

Node::Node(int id,int x,int y) : mId(id), mX(x), mY(y)
{
	mFontHandle = CreateFontToHandle(NULL, 10, 3);

}


Node::~Node()
{

}

void Node::update() {

}

void Node::draw() {
	DrawCircleAA(mX, mY, NODE_R, 16, GetColor(255, 255, 255), TRUE);
	DrawCircleAA(mX, mY, NODE_R + 1, 32, GetColor(100, 100, 100), FALSE);
	DrawFormatStringToHandle(mX + NODE_R, mY + NODE_R, GetColor(200, 200, 200), mFontHandle, "%d", mId);
}

bool Node::ContainsPoint(int x, int y) {
	return  sqrt(pow(x - mX,2) + pow(y-mY,2)) <= NODE_R*2;
}

int Node::GetId() { return mId; }
int Node::GetX() { return mX; }
int Node::GetY() { return mY; }

void Node::SetX(int x) { mX = x; }
void Node::SetY(int y) { mY = y; }