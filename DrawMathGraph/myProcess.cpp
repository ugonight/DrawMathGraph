// Process�N���X���Q��
#include"System\process.h"

// �K�v�ȃ��C�u�������C���N���[�h
#include"DxLib.h"
#include <time.h>

// run�{�^���������ꂽ�Ƃ��Ɏ��s����鏈��
void Process::run() {
	// Welsh-Powell�̃A���S���Y��

	// 0.������
	for (auto node : mNode) node->SetColor(255, 255, 255);

	// 1.�_�������̍~���ɕ��ёւ���
	std::vector<Node*> list;
	int max = 0;
	for (auto node : mNode) {						// mNode : �_�̃��X�g
		max = (node->GetNextNode().size() > max) ? 
			node->GetNextNode().size() : max;		// Node::GetNextNode() : �_�ɂȂ����Ă���_�̃��X�g
	}
	for (int i = max; i > 0; i--) {
		for (auto node : mNode) {
			if (node->GetNextNode().size() == i) {
				list.push_back(node);
			}
		}
	}

	// 2.�S�Ă̓_��h��܂ŌJ��Ԃ�
	bool loop = true, next;
	int n[3], id, x = 0;
	SRand((unsigned)time(NULL));
	while (loop) {
		x++;
		n[0] = GetRand(255); n[1] = GetRand(255); n[2] = GetRand(255);	// GetRand() : �����̎擾�iDxLib�̊֐��j
		// 2-1.�_�����ԂɌ��ēh���ĂȂ��_��Fn�œh��
		id = 0;
		for (auto node : list) {
			if (node->GetNodeColor() == GetColor(255,255,255)) {						// GetColor() : �F�R�[�h�̎擾�iDxLib�̊֐��j
				node->SetColor(n[0], n[1], n[2]);
				break;
			}
			else {
				id++;
			}
		}
		// 2-2.2-1�̓_�Ɨאڂ��Ă��Ȃ��h���Ă��Ȃ��_��Fn�œh��
		for (auto node : list) {
			if (node->GetNodeColor() == GetColor(255, 255, 255)) {
				next = false;
				for (auto n : list[id]->GetNextNode()) {
					if (n == node) next = true;
				}
				if (!next)node->SetColor(n[0], n[1], n[2]);
			}
		}
		// �S�Ă̓_��h������
		loop = false;
		for (auto node : list) {
			if (node->GetNodeColor() == GetColor(255,255,255)) {
				loop = true;
			}
		}
	}

	// ������\��
	setString("�� = " + std::to_string(x));
}