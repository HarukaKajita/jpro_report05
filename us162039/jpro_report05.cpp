#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;


class BinTree {
private:
	class BinNode {
	public:
		string data;
		int appearanceNum;
		BinNode* left;
		BinNode* right;
		BinNode(string a = 0, BinNode * b = NULL, BinNode * c = NULL) {
			data = a; left = b; right = c; appearanceNum = 1;
		}
		void printNode() {
			cout << data << "[" << appearanceNum << "] ";
#ifdef _DEBUG
		cout << "this = " << this << endl;
		cout << "left = " << left << endl;
		cout << "right = " << right << endl;
#endif // DEBUG

		}
	};

	BinNode* root;
	void traverse(BinNode* rp);
	BinNode* addNode(BinNode* rp, BinNode* node);
	BinNode* delNode(BinNode* rp, int  appearanceNum);
public:
	BinTree() { root = NULL; }
	void printTree() { traverse(root); }
	void insert(string str) {
		BinNode* np = new BinNode(str);
		root = addNode(root, np);
	}
	void remove(int apppearanceNum) {
		root = delNode(root, apppearanceNum);
	}
};

void BinTree::traverse(BinNode* rp) {
	if (rp == NULL) return;
	traverse(rp->left);
	rp->printNode();
	traverse(rp->right);
}

BinTree::BinNode* BinTree::addNode(BinNode* rp, BinNode* node) {
	if (node == NULL) return rp;
	if (rp == NULL) return node;
	else {
		if (node->data == rp->data) {
			rp->appearanceNum++;
		} 
		else if (node->data < rp->data) {
			rp->left = addNode(rp->left, node);
		}
		else {
			rp->right = addNode(rp->right, node);
		}
		return rp;
	}
}

BinTree::BinNode* BinTree::delNode(BinNode* rp, int appearanceNum) {

	if (rp == NULL) return NULL;
	rp->left = delNode(rp->left, appearanceNum);
#ifdef _DEBUG
	cout << rp->data << " : " << rp->appearanceNum << endl;
#endif // _DEBUG

	if (appearanceNum == rp->appearanceNum) {
#ifdef _DEBUG
		cout << "削除します" << endl;
		cout << "right = " << right << endl;
		cout << "left = " << left << endl;
#endif // _DEBUG

		BinNode* left = rp->left;
		BinNode* right = rp->right;
		
		delete rp;
		rp = addNode(right, left);//rp下のツリーの再構成
		//再構成後のツリーに対して削除処理
		rp = delNode(rp, appearanceNum);
		return rp;
	}
	else rp->right = delNode(rp->right, appearanceNum);
	
	return rp;
}

int main() {
	BinTree bt;	// 空の二進木を作成
	string str;
	ifstream fin("words.txt");
	if (!fin) {
		cerr << "ファイルを開けませんでした。" << endl;
		exit(EXIT_FAILURE);
	}

	while (fin >> str) {
		bt.insert(str);	//単語をツリーに入力
	}

	bt.printTree();	// bt の木全体を表示する
	cout << endl;

	int appearanceNum = 0;
	while (cout << "何回出現した単語を削除しますか --> " && cin >> appearanceNum) {
		bt.remove(appearanceNum);
		bt.printTree();
		cout << endl;
	}

	return 0;
}
