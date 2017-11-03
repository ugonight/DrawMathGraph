// Processクラスを参照
#include"System\process.h"

// 必要なライブラリをインクルード
#include"DxLib.h"
#include <time.h>

// runボタンが押されたときに実行される処理
void Process::run() {
	// Welsh-Powellのアルゴリズム

	// 0.初期化
	for (auto node : mNode) node->SetColor(255, 255, 255);

	// 1.点を次数の降順に並び替える
	std::vector<Node*> list;
	int max = 0;
	for (auto node : mNode) {						// mNode : 点のリスト
		max = (node->GetNextNode().size() > max) ? 
			node->GetNextNode().size() : max;		// Node::GetNextNode() : 点につながっている点のリスト
	}
	for (int i = max; i > 0; i--) {
		for (auto node : mNode) {
			if (node->GetNextNode().size() == i) {
				list.push_back(node);
			}
		}
	}

	// 2.全ての点を塗るまで繰り返す
	bool loop = true, next;
	int n[3], id, x = 0;
	SRand((unsigned)time(NULL));
	while (loop) {
		x++;
		n[0] = GetRand(255); n[1] = GetRand(255); n[2] = GetRand(255);	// GetRand() : 乱数の取得（DxLibの関数）
		// 2-1.点を順番に見て塗ってない点を色nで塗る
		id = 0;
		for (auto node : list) {
			if (node->GetNodeColor() == GetColor(255,255,255)) {						// GetColor() : 色コードの取得（DxLibの関数）
				node->SetColor(n[0], n[1], n[2]);
				break;
			}
			else {
				id++;
			}
		}
		// 2-2.2-1の点と隣接していない塗っていない点を色nで塗る
		for (auto node : list) {
			if (node->GetNodeColor() == GetColor(255, 255, 255)) {
				next = false;
				for (auto n : list[id]->GetNextNode()) {
					if (n == node) next = true;
				}
				if (!next)node->SetColor(n[0], n[1], n[2]);
			}
		}
		// 全ての点を塗ったか
		loop = false;
		for (auto node : list) {
			if (node->GetNodeColor() == GetColor(255,255,255)) {
				loop = true;
			}
		}
	}

	// 文字を表示
	setString("χ = " + std::to_string(x));
}