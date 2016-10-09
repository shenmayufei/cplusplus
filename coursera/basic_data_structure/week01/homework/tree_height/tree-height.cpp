#include <iostream>
#include <vector>
#include <algorithm>

class TreeNode {
public:
  TreeNode* child;
  TreeNode* next;
  TreeNode() : child(NULL), next(NULL){};
  TreeNode(TreeNode* child, TreeNode* next): child(child), next(next) {};
};

class Tree {
  int root;
  std::vector<TreeNode*> trees;
public:
  Tree(int size) {
    trees.resize(size);
    for(int i = 0; i < size; i++) trees[i] = new TreeNode();
  }
  ~Tree() {
    // release memory
    for(std::vector<TreeNode*>::iterator it = trees.begin(); it != trees.end(); it++) {
      delete *it;
    }
  }
  void connect(int child, int parent) {
    if (parent == -1) {
      root = child;
      return;
    }
    TreeNode* ptrParent = trees[parent];
    TreeNode* ptrChild = trees[child];
    ptrChild->next = ptrParent->child;
    ptrParent->child= ptrChild;
  }

  int height() {
    return heightHelper(trees[root]);
  }
private:
  int heightHelper(TreeNode* ptrRoot) {
    if (ptrRoot == nullptr) return 0;
    if (ptrRoot->child == nullptr) return 1;

    TreeNode* cur = ptrRoot->child;
    int max = 0;
    while(cur != nullptr) {
      max = std::max(max, heightHelper(cur)); 
      cur = cur->next;
    }
    return max+1;
  }
};

class TreeHeight {
  int n;             
  Tree* t;

public:
  void read() {
    std::cin >> n;
    t = new Tree(n);
    int parent;
    for (int i = 0; i < n; i++) {
      std::cin >> parent;
      t->connect(i, parent);
    }
  }

  int compute_height() {
    return t->height();
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height() << std::endl;
}
