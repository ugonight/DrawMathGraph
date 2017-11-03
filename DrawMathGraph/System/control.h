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
	int mDragNode, mDragEdge;			// �ړ������
	int mDrawingLineNode;				// ���������n�߂��n�_�̓_
	
	int mFontHandle, mInputHandle;
	std::string mInfoStr;
	std::string mProcessInfoStr;
	int mCount, mInfoNodeNum, mInfoEdgeNum;
	std::string mScsho; int mInputP;

	void ClickEvent();	// �}�E�X���N���b�N���ꂽ�Ƃ��̃C�x���g
	void InputEvent();	// �}�E�X��������Ă��鎞�̃C�x���g
	void UpEvent();		// �}�E�X�������ꂽ���̃C�x���g
	void command();		// �R�}���h����

	std::string getNodeInfo(Node* node);
	std::string getEdgeInfo(Edge* edge);

public:
	Control();
	~Control();

	void update();
	void draw();

	void SetProcessInfo(std::string str);
};

