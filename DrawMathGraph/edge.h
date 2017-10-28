#pragma once

class Node;

class Edge
{
private:
	int mId;
	Node* mNode[2];
	int mFontHandle;
	int mDPointX, mDPointY;	//�����_

public:
	Edge(int id,Node* start, Node* end);
	~Edge();

	void update();
	void draw();

	int GetId();

	void SetDPoint(int x,int y);


	bool checkNode( Node* node);		// �w�肵���_���[�_�ɂ��邩�m�F����					
	bool ContainsPoint(int x, int y);	// �|�C���g���ӂƐڂ��Ă��邩�Ԃ�
};

