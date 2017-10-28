#pragma once
#include<vector>
#include<memory>

class Node;
class Cursor;
class Edge;

class Control
{
private:
	std::vector<std::shared_ptr<Node>> mNode;
	std::vector<std::shared_ptr<Edge>> mEdge;
	Cursor *mCursor;
	int mDragNode, mDragEdge;			// 移動する辺
	int mDrawingLineNode;				// 線を引き始めた始点の点

	void ClickEvent();
	void InputEvent();
	void UpEvent();
public:
	Control();
	~Control();

	void update();
	void draw();

};

