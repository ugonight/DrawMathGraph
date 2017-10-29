#include <DxLib.h>
#include <math.h>
#include "node.h"

Node::Node(int id,int x,int y) :
	mId(id), mX(x), mY(y)
{
	mFontHandle = CreateFontToHandle(NULL, FONT_SIZE_N, 3);

}


Node::~Node()
{
	DeleteFontToHandle(mFontHandle);
}

void Node::update() {

}

void Node::draw() {
	DrawCircleAA(mX, mY, NODE_R, 16, GetColor(255, 255, 255), TRUE);
	DrawCircleAA(mX, mY, NODE_R + 1, 32, GetColor(100, 100, 100), FALSE);
	DrawFormatStringToHandle(mX + NODE_R, mY + NODE_R, GetColor(200, 200, 200), mFontHandle, "%d", mId);
}

bool Node::ContainsPoint(int x, int y) {
	return  sqrt(pow(x - mX,2) + pow(y-mY,2)) <= NODE_R*2;
}

int Node::GetId() { return mId; }
int Node::GetX() { return mX; }
int Node::GetY() { return mY; }
std::vector<Node*> Node::GetNextNode() { return mNextNode; }
std::vector<Edge*> Node::GetConnectedEdge() { return mConnectedEdge; }

void Node::SetX(int x) { mX = x; }
void Node::SetY(int y) { mY = y; }
void Node::AddNextNode(Node* node) { mNextNode.push_back(node); }
void Node::AddConnectedEdge(Edge* edge) { mConnectedEdge.push_back(edge); }
void Node::DeleteNextNode(Node* node) {
	for (auto it = mNextNode.begin(); it != mNextNode.end();it++) {
		if (*it == node) {
			mNextNode.erase(it);
			break;
		}
	}
	
}
void Node::DeleteConnectedEdge(Edge* edge) {
	for (auto it = mConnectedEdge.begin(); it != mConnectedEdge.end();it++) {
		if (*it == edge) {
			mConnectedEdge.erase(it); 
			break; 
		}
	}
}