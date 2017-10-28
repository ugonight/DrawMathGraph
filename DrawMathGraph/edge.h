#pragma once

class Node;

class Edge
{
private:
	int mId;
	Node* mNode[2];
	int mFontHandle;
	int mDPointX, mDPointY;	//方向点

public:
	Edge(int id,Node* start, Node* end);
	~Edge();

	void update();
	void draw();

	int GetId();

	void SetDPoint(int x,int y);


	bool checkNode( Node* node);		// 指定した点が端点にあるか確認する					
	bool ContainsPoint(int x, int y);	// ポイントが辺と接しているか返す
};

