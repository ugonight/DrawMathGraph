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

	// 出力文字をセット
	void setString(std::string str);
public:
	Process(Control* control);
	~Process();

	// mNodeとmEdgeをリセット
	void reset(std::vector<std::shared_ptr<Node>> node,std::vector<std::shared_ptr<Edge>> edge);
	// runボタンを押したときに実行される処理
	void run();
};

