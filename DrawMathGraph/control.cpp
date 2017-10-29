#include<string>
#include"DxLib.h"

#include "control.h"
#include "node.h"
#include "cursor.h"
#include "edge.h"

Control::Control() : 
	mDragNode(-1),mDragEdge(-1),
	mDrawingLineNode(-1),
	mInfoStr("")
{
	//mNode.push_back(new Node(100, 100));
	mCursor = new Cursor();
	mFontHandle = CreateFontToHandle(NULL, FONT_SIZE_C, 3);
}


Control::~Control()
{
	DeleteFontToHandle(mFontHandle);
}

void Control::update() {
	mCursor->update();
	if (mCursor->GetClickL()) ClickEvent();
	else if (mCursor->GetInputL()) InputEvent();
	else if (mCursor->GetUpL()) UpEvent();
}

void Control::draw() {

	for (auto node : mNode)
		node->draw();
	for (auto edge : mEdge)
		edge->draw();

	mCursor->draw();

	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), mFontHandle, mInfoStr.c_str());

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
	return result;
}

std::string Control::getEdgeInfo(Edge* edge){
	std::string result = "E" + std::to_string(edge->GetId())
		+ "\nNode:V" + std::to_string(edge->getNode(0)->GetId()) + " V" + std::to_string(edge->getNode(1)->GetId());

	return result;
}