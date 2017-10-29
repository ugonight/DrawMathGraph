#pragma once
#include<vector>
#include<memory>

#define FONT_SIZE_C 15

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
	
	int mFontHandle;
	std::string mInfoStr;

	void ClickEvent();
	void InputEvent();
	void UpEvent();

	std::string getNodeInfo(Node* node);
	std::string getEdgeInfo(Edge* edge);

public:
	Control();
	~Control();

	void update();
	void draw();

};

