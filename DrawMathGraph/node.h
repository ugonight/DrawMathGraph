#pragma once
#include<vector>

#define NODE_R 10
#define FONT_SIZE_N 15

class Edge;

class Node
{
private:
	int mId;
	int mX, mY;
	std::vector<Node*> mNextNode;
	std::vector<Edge*> mConnectedEdge;

	int mFontHandle;

public:
	Node(int id, int x, int y);
	~Node();

	void update();
	void draw();

	int GetId();
	int GetX();
	int GetY();
	std::vector<Node*> GetNextNode();
	std::vector<Edge*> GetConnectedEdge();

	void SetX(int x);
	void SetY(int y);
	void AddNextNode(Node* node);
	void AddConnectedEdge(Edge* edge);
	void DeleteNextNode(Node* node);
	void DeleteConnectedEdge(Edge* edge);

	bool ContainsPoint(int x, int y);	// ポイントがノードと接しているか返す

};