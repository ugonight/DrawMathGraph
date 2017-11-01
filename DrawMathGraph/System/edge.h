#pragma once
#include<string>

#define FONT_SIZE_E 15

class Node;

class Edge
{
private:
	int mId;
	Node* mNode[2];
	int mFontHandle, mColor;
	int mDPointX, mDPointY;	//方向点
	std::string mValue;

public:
	Edge(int id,Node* start, Node* end);
	~Edge();

	void update();
	void draw();

	int GetId();
	Node* getNode(int i);
	std::string GetValue();
	int GetEdgeColor();

	void SetDPoint(int x,int y);
	void SetValue(std::string value);
	void SetColor(int r, int g, int b);

	bool checkNode( Node* node);		// 指定した点が端点にあるか確認する					
	bool ContainsPoint(int x, int y);	// ポイントが辺と接しているか返す
};

