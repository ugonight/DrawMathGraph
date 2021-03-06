#pragma once
#include<vector>
#include<memory>

#define FONT_SIZE_C 15

class Node;
class Cursor;
class Edge;
class Process;

class Control
{
private:
	std::vector<std::shared_ptr<Node>> mNode;
	std::vector<std::shared_ptr<Edge>> mEdge;
	Cursor *mCursor;
	Process *mProcess;
	int mDragNode, mDragEdge;			// 移動する辺
	int mDrawingLineNode;				// 線を引き始めた始点の点
	
	int mFontHandle, mInputHandle;
	std::string mInfoStr;
	std::string mProcessInfoStr;
	int mCount, mInfoNodeNum, mInfoEdgeNum;
	std::string mScsho; int mInputP;

	void ClickEvent();	// マウスがクリックされたときのイベント
	void InputEvent();	// マウスが押されている時のイベント
	void UpEvent();		// マウスが離された時のイベント
	void command();		// コマンド処理

	std::string getNodeInfo(Node* node);
	std::string getEdgeInfo(Edge* edge);

public:
	Control();
	~Control();

	void update();
	void draw();

	void SetProcessInfo(std::string str);
};

