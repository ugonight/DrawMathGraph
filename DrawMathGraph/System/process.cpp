#include "process.h"

Process::Process(Control* control) : mControl(control)
{
}


Process::~Process()
{
}

void Process::reset(std::vector<std::shared_ptr<Node>> node, std::vector<std::shared_ptr<Edge>> edge) {
	mNode.clear(); mEdge.clear();
	for (auto n : node) mNode.push_back(n.get());
	for (auto e : edge) mEdge.push_back(e.get());
}

void Process::setString(std::string str) {
	mControl->SetProcessInfo(str);
}