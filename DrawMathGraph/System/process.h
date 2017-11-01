#pragma once

#include<vector>
#include<memory>

#include"control.h"
#include"node.h"
#include"edge.h"

class Process
{
private:
	std::vector<Node*> mNode;
	std::vector<Edge*> mEdge;
	Control* mControl;

	// �o�͕������Z�b�g
	void setString(std::string str);
public:
	Process(Control* control);
	~Process();

	// mNode��mEdge�����Z�b�g
	void reset(std::vector<std::shared_ptr<Node>> node,std::vector<std::shared_ptr<Edge>> edge);
	// run�{�^�����������Ƃ��Ɏ��s����鏈��
	void run();
};

