#include"DxLib.h"
#include<math.h>

#include "edge.h"
#include "node.h"

Edge::Edge(int id, Node* start, Node* end) :
	mId(id) {
	mNode[0] = start;
	mNode[1] = end;

	mDPointX = -1;	//(mNode[0]->GetX() + mNode[1]->GetX()) / 2;
	mDPointY = -1;	//(mNode[0]->GetY() + mNode[1]->GetY()) / 2;

	mFontHandle = CreateFontToHandle(NULL, FONT_SIZE_E, 3);
}


Edge::~Edge()
{
	DeleteFontToHandle(mFontHandle);
}

void Edge::update(){

}

void Edge::draw() {
	if (mDPointX == -1 || mDPointY == -1) {
		// 方向点が無いときは普通の直線
		DrawLine(mNode[0]->GetX(), mNode[0]->GetY(), mNode[1]->GetX(), mNode[1]->GetY(), GetColor(255, 255, 255));
		DrawFormatStringToHandle((mNode[0]->GetX() + mNode[1]->GetX()) / 2, (mNode[0]->GetY() + mNode[1]->GetY()) / 2, GetColor(100, 100, 100), mFontHandle, "%d", mId);
	}
	else {
		// ベジェ曲線
		const int T = 200;
		float a, b;
		float x, y, px = mNode[0]->GetX(), py = mNode[0]->GetY();
		for (int t = 0; t < T; t++) {
			b = (float)t / T;
			a = 1 - b;
			x = a*a*mNode[0]->GetX() + 2 * a * b * mDPointX + b*b*mNode[1]->GetX();
			y = a*a*mNode[0]->GetY() + 2 * a * b * mDPointY + b*b*mNode[1]->GetY();
			DrawLine(px, py, x, y, GetColor(255, 255, 255));
			if (t == 100) {
				DrawFormatStringToHandle(x, y, GetColor(100, 100, 100), mFontHandle, "%d", mId);
			}
			px = x;
			py = y;
		}
	}
}

bool Edge::checkNode(Node* node) {
	return mNode[0] == node || mNode[1] == node;
}

bool Edge::ContainsPoint(int x, int y) {
	if (mDPointX == -1 || mDPointY == -1) {
		// 直線
		int x0 = mNode[0]->GetX(), x1 = mNode[1]->GetX();
		int y0 = mNode[0]->GetY(), y1 = mNode[1]->GetY();
		int L1 = sqrt(pow(x1 - x0, 2.0) + pow(y1 - y0, 2.0));
		int L2 = sqrt(pow(x - x0, 2.0) + pow(y - y0, 2.0));
		return abs(((x1 - x0)*(y - y0) - (y1 - y0)*(x - x0)) / L1) <= 10;
	}
	else {
		// ベジェ曲線
		const int T = 200;
		float a, b;
		float tx, ty;
		for (int t = 0; t < T; t++) {
			b = (float)t / T;
			a = 1 - b;
			tx = a*a*mNode[0]->GetX() + 2 * a * b * mDPointX + b*b*mNode[1]->GetX();
			ty = a*a*mNode[0]->GetY() + 2 * a * b * mDPointY + b*b*mNode[1]->GetY();
			if (sqrt(pow(tx - x, 2.0) + pow(ty - y, 2.0)) < 10)
				return true;
		}
		return false;
	}
}

int Edge::GetId() { return mId; }
Node* Edge::getNode(int i) { return mNode[i]; }

void Edge::SetDPoint(int x,int y) { 
	// 始点と終点の真ん中の点
	int x1 = (mNode[0]->GetX() + mNode[1]->GetX()) / 2;
	int y1 = (mNode[0]->GetY() + mNode[1]->GetY()) / 2;
	// この点から方向点まで
	int dx = x - x1;
	int dy = y - y1;

	mDPointX = x1 + dx * 2;
	mDPointY = y1 + dy * 2;
}
