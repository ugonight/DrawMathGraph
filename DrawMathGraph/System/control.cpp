#include<string>
#include"DxLib.h"

#include "control.h"
#include "node.h"
#include "cursor.h"
#include "edge.h"
#include "process.h"

Control::Control() : 
	mDragNode(-1),mDragEdge(-1),
	mDrawingLineNode(-1),
	mInfoStr(""), mProcessInfoStr(""),
	mCount(0),mInfoNodeNum(-1), mInfoEdgeNum(-1)
{
	//mNode.push_back(new Node(100, 100));
	mCursor = new Cursor();
	mProcess = new Process(this);
	mFontHandle = CreateFontToHandle(NULL, FONT_SIZE_C, 3);
	mInputHandle = 0;
}


Control::~Control()
{
	DeleteFontToHandle(mFontHandle);
	DeleteKeyInput(mInputHandle);
}

void Control::update() {
	mCursor->update();

	// �N���b�N�C�x���g
	if (mCursor->GetClickL()) ClickEvent();
	else if (mCursor->GetInputL()) InputEvent();
	else if (mCursor->GetUpL()) UpEvent();

	// �J�E���^�[
	if (mCount > 0) mCount++;
	if (mCount > 30)mCount = 0;

	// �l����
	if (CheckKeyInput(mInputHandle) && mInputHandle != 0) {
		char str[256];
		GetKeyInputString(str, mInputHandle);
		if (mInfoEdgeNum == -1) {
			mNode[mInfoNodeNum]->SetValue(str);
		}
		else {
			mEdge[mInfoEdgeNum]->SetValue(str);
		}
		DeleteKeyInput(mInputHandle);
		mInputHandle = 0;
	}
}

void Control::draw() {

	for (auto node : mNode)
		node->draw();
	for (auto edge : mEdge)
		edge->draw();

	mCursor->draw();

	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), mFontHandle, mInfoStr.c_str());

	//�l����
	if (!CheckKeyInput(mInputHandle)) {
		DrawKeyInputModeString(700, 0);
		DrawFormatStringToHandle(340, 0, GetColor(255, 255, 255), mFontHandle, "Value > ");
		DrawKeyInputString(400, 0, mInputHandle);
	}
	//run�{�^��
	if (mCursor->GetCursorNum() == 1) {
		DrawBox(0, 600 - 50, 80, 600, GetColor(255, 255, 255), TRUE);
		int w = GetDrawStringWidthToHandle("run", 3, mFontHandle);
		DrawStringToHandle(40 - w / 2, 600 - 25 - FONT_SIZE_C / 2, "run", GetColor(0, 0, 0), mFontHandle);
		DrawStringToHandle(90, 600 - 50, mProcessInfoStr.c_str(), GetColor(255, 255, 255), mFontHandle);
	}
}

void Control::ClickEvent() {
	//�_
	{
		// �_�̓��蔻��
		bool hit = false;
		int nodeNum, i = 0;
		for (auto node : mNode) {
			if (hit = node->ContainsPoint(mCursor->GetX(), mCursor->GetY())) {
				nodeNum = i;
				mInfoStr = getNodeInfo(node.get());
				mInfoNodeNum = i; mInfoEdgeNum = -1;
				break;
			}
			i++;
		}

		// �_�ǉ�
		if (mCursor->GetCursorNum() == 0 && !hit) {
			// id�����߂�
			int id = 0;
			{
				auto it = mNode.begin();
				while (it != mNode.end()) {
					if (id == it->get()->GetId()) {
						id++;
						it = mNode.begin();
					}
					else it++;
				}
			}
			// �_�𐶐�
			mNode.push_back(std::make_shared<Node>(id, mCursor->GetX(), mCursor->GetY()));
			return;
		}

		//�_������������n�߂�
		if (mCursor->GetCursorNum() == 0 && hit) {
			mDrawingLineNode = nodeNum;
			return;
		}
		else {
			mDrawingLineNode = -1;
		}

		//�_�ړ�
		if (mCursor->GetCursorNum() == 1 && hit) {
			mDragNode = nodeNum;
			return;
		}
		else {
			mDragNode = -1;
		}

		//�_�폜
		if (mCursor->GetCursorNum() == 2 && hit) {
			// �_��������ӂ��폜
			/*std::vector<std::shared_ptr<Edge>>::iterator*/ auto it = mEdge.begin();
			while (it != mEdge.end()) {
				if (it->get()->checkNode(mNode[nodeNum].get())) {
					//�ڑ��_����ӂ̊֌W���폜
					it->get()->getNode(0)->DeleteConnectedEdge(it->get());
					it->get()->getNode(1)->DeleteConnectedEdge(it->get());
					
					it = mEdge.erase(it);
				}
				else it++;
			}
			//�_������
			for (auto node : mNode[nodeNum]->GetNextNode()) {
				//�_�̊֌W���폜
				node->DeleteNextNode(mNode[nodeNum].get());
			}
			mNode.erase(mNode.begin() + nodeNum);
			return;
		}
	}

	//��
	{
		// �_�̓��蔻��
		bool hit = false;
		int edgeNum, i = 0;
		for (auto edge : mEdge) {
			if (hit = edge->ContainsPoint(mCursor->GetX(), mCursor->GetY())) {
				edgeNum = i;
				mInfoStr = getEdgeInfo(edge.get());
				mInfoEdgeNum = i; mInfoNodeNum = -1;
				break;
			}
			i++;
		}

		//�ӈړ�
		if (mCursor->GetCursorNum() == 1 && hit) {
			mDragEdge = edgeNum;
			return;
		}
		else {
			mDragEdge = -1;
		}

		//�Ӎ폜
		if (mCursor->GetCursorNum() == 2 && hit) {
			// �ڑ��_�̊֌W���폜
			mEdge[edgeNum]->getNode(0)->DeleteConnectedEdge(mEdge[edgeNum].get());
			mEdge[edgeNum]->getNode(0)->DeleteNextNode(mEdge[edgeNum]->getNode(1));
			mEdge[edgeNum]->getNode(1)->DeleteConnectedEdge(mEdge[edgeNum].get());
			mEdge[edgeNum]->getNode(1)->DeleteNextNode(mEdge[edgeNum]->getNode(0));

			mEdge.erase(mEdge.begin() + edgeNum);
			return;
		}
	}

	//�l����
	{
		int x, y, l;
		GetDrawStringSizeToHandle(&x, &y, &l, mInfoStr.c_str(), mInfoStr.length(), mFontHandle);
		if (mCursor->GetCursorNum() == 1 && mCursor->GetX() <= x + 30 && mCursor->GetY() <= y) {	//���\���̈���N���b�N������
			if (mCount == 0) {
				mCount++;
			}
			else {
				//KeyInputString(x, y - FONT_SIZE_C, 255, str, TRUE);
				mInputHandle = MakeKeyInput(256, TRUE, FALSE, FALSE);
				SetActiveKeyInput(mInputHandle);
			}
		}
	}

	//run�{�^��
	{
		if (mCursor->GetX() >= 0 && mCursor->GetX() <= 80 && mCursor->GetY() >= 600 - 50 && mCursor->GetY() <= 600) {
			mProcess->reset(mNode, mEdge);
			mProcess->run();

		}
	}
}

void Control::InputEvent() {
	// �_
	{
		int i = 0;
		for (auto node : mNode) {
			// �_���ړ�
			if (mCursor->GetCursorNum() == 1 && i == mDragNode) {
				node->SetX(mCursor->GetX());
				node->SetY(mCursor->GetY());
			}
			
			// ��������
			if (mCursor->GetCursorNum() == 0 && i == mDrawingLineNode) {
				DrawLine(node->GetX(), node->GetY(), mCursor->GetX(), mCursor->GetY(), GetColor(255, 255, 255));
			}
			i++;
		}
	}

	// ��
	{
		int i = 0;
		for (auto edge: mEdge) {
			// �����_���ړ�
			if (mCursor->GetCursorNum() == 1 && i == mDragEdge && mDragNode == -1) {
				edge->SetDPoint(mCursor->GetX(), mCursor->GetY());
			}
			i++;
		}
	}
}

void Control::UpEvent() {
	// �_
	{
		int i = 0;
		for (auto node : mNode) {
			if (node->ContainsPoint(mCursor->GetX(), mCursor->GetY())) {
				// ����ǉ�
				if (mCursor->GetCursorNum() == 0 && mDrawingLineNode != -1 && mDrawingLineNode != i) {
					// id�����߂�
					int id = 0;
					{
						auto it = mEdge.begin();
						while (it != mEdge.end()) {
							if (id == it->get()->GetId()) {
								id++;
								it = mEdge.begin();
							}
							else it++;
						}
					}
					// ���𐶐�
					auto newEdge = std::make_shared<Edge>(id, mNode[mDrawingLineNode].get(), node.get());
					mEdge.push_back(newEdge);
					// �ڑ��֌W��ǉ�
					mNode[mDrawingLineNode].get()->AddNextNode(node.get());
					mNode[mDrawingLineNode].get()->AddConnectedEdge(newEdge.get());
					node.get()->AddNextNode(mNode[mDrawingLineNode].get());
					node.get()->AddConnectedEdge(newEdge.get());
				}
				break;
			}
			i++;
		}

		mDrawingLineNode = -1;
		mDragNode = -1;
	}
}

std::string Control::getNodeInfo(Node* node) {
	std::string result = "V" + std::to_string(node->GetId());
	// �ڑ��_
	result += "\nNode:";
	for (auto n : node->GetNextNode()) {
		result += " V" + std::to_string(n->GetId());
	}
	// �ڑ���
	result += "\nEdge:";
	for (auto e : node->GetConnectedEdge()) {
		result += " E" + std::to_string(e->GetId());
	}
	// �l
	result += "\nValue:" + node->GetValue();

	return result;
}

std::string Control::getEdgeInfo(Edge* edge){
	std::string result = "E" + std::to_string(edge->GetId())
		+ "\nNode:V" + std::to_string(edge->getNode(0)->GetId()) + " V" + std::to_string(edge->getNode(1)->GetId());
	// �l
	result += "\nValue:" + edge->GetValue();

	return result;
}

void Control::SetProcessInfo(std::string str) { mProcessInfoStr = str; }