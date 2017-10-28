#include"DxLib.h"

#include "control.h"
#include "node.h"
#include "cursor.h"
#include "edge.h"

Control::Control() : 
	mDragNode(-1),mDragEdge(-1),
	mDrawingLineNode(-1)
{
	//mNode.push_back(new Node(100, 100));
	mCursor = new Cursor();
}


Control::~Control()
{
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
}

void Control::ClickEvent() {
	//点
	{
		// 点の当り判定
		bool hit = false;
		int nodeNum, i = 0;
		for (auto node : mNode) {
			if (hit = node->ContainsPoint(mCursor->GetX(), mCursor->GetY())) {
				nodeNum = i;
				break;
			}
			i++;
		}

		// 点追加
		if (mCursor->GetCursorNum() == 0 && !hit) {
			// idを決める
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
			// 点を生成
			mNode.push_back(std::make_shared<Node>(id, mCursor->GetX(), mCursor->GetY()));
			return;
		}

		//点から線を引き始める
		if (mCursor->GetCursorNum() == 0 && hit) {
			mDrawingLineNode = nodeNum;
			return;
		}
		else {
			mDrawingLineNode = -1;
		}

		//点移動
		if (mCursor->GetCursorNum() == 1 && hit) {
			mDragNode = nodeNum;
			return;
		}
		else {
			mDragNode = -1;
		}

		//点削除
		if (mCursor->GetCursorNum() == 2 && hit) {
			// 点が消える辺を削除
			/*std::vector<std::shared_ptr<Edge>>::iterator*/ auto it = mEdge.begin();
			while (it != mEdge.end()) {
				if (it->get()->checkNode(mNode[nodeNum].get())) {
					it = mEdge.erase(it);
				}
				else it++;
			}
			//点を消す
			mNode.erase(mNode.begin() + nodeNum);
			return;
		}
	}

	//辺
	{
		// 点の当り判定
		bool hit = false;
		int edgeNum, i = 0;
		for (auto edge : mEdge) {
			if (hit = edge->ContainsPoint(mCursor->GetX(), mCursor->GetY())) {
				edgeNum = i;
				break;
			}
			i++;
		}

		//辺移動
		if (mCursor->GetCursorNum() == 1 && hit) {
			mDragEdge = edgeNum;
			return;
		}
		else {
			mDragEdge = -1;
		}

		//辺削除
		if (mCursor->GetCursorNum() == 2 && hit) {
			mEdge.erase(mEdge.begin() + edgeNum);
			return;
		}
	}
}

void Control::InputEvent() {
	// 点
	{
		int i = 0;
		for (auto node : mNode) {
			// 点を移動
			if (mCursor->GetCursorNum() == 1 && i == mDragNode) {
				node->SetX(mCursor->GetX());
				node->SetY(mCursor->GetY());
			}
			
			// 線を引く
			if (mCursor->GetCursorNum() == 0 && i == mDrawingLineNode) {
				DrawLine(node->GetX(), node->GetY(), mCursor->GetX(), mCursor->GetY(), GetColor(255, 255, 255));
			}
			i++;
		}
	}

	// 辺
	{
		int i = 0;
		for (auto edge: mEdge) {
			// 方向点を移動
			if (mCursor->GetCursorNum() == 1 && i == mDragEdge && mDragNode == -1) {
				edge->SetDPoint(mCursor->GetX(), mCursor->GetY());
			}
			i++;
		}
	}
}

void Control::UpEvent() {
	// 点
	{
		int i = 0;
		for (auto node : mNode) {
			if (node->ContainsPoint(mCursor->GetX(), mCursor->GetY())) {
				// 線を追加
				if (mCursor->GetCursorNum() == 0 && mDrawingLineNode != -1 && mDrawingLineNode != i) {
					// idを決める
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
					// 線を生成
					mEdge.push_back(std::make_shared<Edge>(id, mNode[mDrawingLineNode].get(), node.get()));
				}
				break;
			}
			i++;
		}

		mDragNode = -1;
	}
}