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
	int mDragNode, mDragEdge;			// �ړ������
	int mDrawingLineNode;				// ���������n�߂��n�_�̓_

	void ClickEvent();
	void InputEvent();
	void UpEvent();
public:
	Control();
	~Control();

	void update();
	void draw();

};

