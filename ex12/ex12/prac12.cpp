#include <iostream>
using namespace std;

//#define DEBUG

class BinTree{
private:
  class BinNode{
  public:
    int data;
    BinNode* left;
    BinNode* right;
    BinNode(int a = 0, BinNode* b = NULL, BinNode* c = NULL){
      data = a; left = b; right = c;
    }
    void printNode(){cout << data << " ";}
  };

  BinNode* root;
  void traverse(BinNode* rp);
  BinNode* addNode(BinNode* rp, BinNode* node);
  BinNode* delNode(BinNode* rp, int x);
public:
  BinTree(){root = NULL;}
  void printTree(){traverse(root);}
  void insert(int x){
    BinNode* np = new BinNode(x);
    root = addNode(root, np);
  }
  void remove(int x){
    root = delNode(root, x);
  }
};

void BinTree::traverse(BinNode* rp){
  if(rp == NULL) return;
  traverse(rp->left);
  rp->printNode();
  traverse(rp->right);
}

BinTree::BinNode* BinTree::addNode(BinNode* rp, BinNode* node){
  if(node == NULL) return rp;
  if(rp == NULL) return node;
  else{
    if(node->data <= rp->data){
      rp->left = addNode(rp->left, node);
    } else {
      rp->right = addNode(rp->right, node);
    }
    return rp;
  }
}

BinTree::BinNode* BinTree::delNode(BinNode* rp, int x){

  if(rp == NULL) return NULL;

  #ifdef DEBUG
  cout << "del : " << x << endl;
  cout << "now : " << rp->data << endl;
  if(rp->left)cout << "left : " << rp->left->data << endl;
  if(rp->right)cout << "right : " << rp->right->data << endl;
  
  #endif
  if(x == rp->data){
    BinNode* left = rp->left;
    BinNode* right = rp->right;
    delete rp;
    return addNode(right, left);
  } else{
    if(x < rp->data){
      rp->left = delNode(rp->left, x);
    } else {
      rp->right = delNode(rp->right, x);
    }
    return rp;
  }
}

int main(){
  BinTree bt;	// 空の二進木を作成
  int x;

  cout << "正整数をいくつか入力せよ --> ";
  while(cin >> x && x >0){	// 負数が入力されるまで正整数を入力
    bt.insert(x);	// x をデータとして持つノードを木に追加
  }

  bt.printTree();	// bt の木全体を表示する
  cout << endl;

  while(cout << "削除したい正整数 --> " && cin >> x && x > 0){
    bt.remove(x);
    bt.printTree();
    cout << endl;
  }

  return 0;
}
