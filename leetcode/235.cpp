/* 235. Lowest Common Ancestor of a Binary Search Tree
 *  
 *  Given a binary search tree (BST), find the lowest common ancestor (LCA) of
 *  two given nodes in the BST.
 *
 *  According to the definition of LCA on Wikipedia: “The lowest common ancestor
 *  is defined between two nodes v and w as the lowest node in T that has both v 
 *  and w as descendants (where we allow a node to be a descendant of itself).”
 *
 *
 *
 *  For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. 
 *  Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant
 *  of itself according to the LCA definition.

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5
 */

#include <iostream>
#include <vector>

using std::vector;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Solution
class Solution {
public:
    // Find the path from root to p, and the path from root to q via DFS
    // compare the two paths, until one different node found, the previous node is what we want
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) return NULL;
        if (root ==p || root ==q) return root;

        vector<TreeNode*> pAnces, qAnces;
        if (!findNode(root, p, pAnces)) return NULL;
        if (!findNode(root, q, qAnces)) return NULL;

        pAnces.push_back(root);
        qAnces.push_back(root);
        std::reverse(pAnces.begin(), pAnces.end());
        std::reverse(qAnces.begin(), qAnces.end());

        int i;
        for(i = 0; i < pAnces.size() && i < qAnces.size(); i++) {
            if (pAnces[i] != qAnces[i]) break;
        }

        return pAnces[i-1];
    }

    bool findNode(TreeNode* root, TreeNode* p, vector<TreeNode*>& ancestors) {
        if (root == p) {
            return true;
        }
        if (root==NULL) return false;

        if (findNode(root->left, p, ancestors)) {
            ancestors.push_back(root->left);
            return true;
        }
        if (findNode(root->right, p, ancestors)) {
            ancestors.push_back(root->right);
            return true;
        }

        return false;
    }
};

int main() {
    TreeNode* root = new TreeNode(6);

    root->left = new TreeNode(2);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);

    root->right = new TreeNode(8);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    Solution sol;
    std::cout << "1. " << (sol.lowestCommonAncestor(root, root, root) == root) << std::endl;
    std::cout << "2. " << (sol.lowestCommonAncestor(root, root->left, root->right) == root) << std::endl;
    std::cout << "3. " << (sol.lowestCommonAncestor(root, root->left, root->right->right) == root) << std::endl;
    std::cout << "4. " << (sol.lowestCommonAncestor(root, root->left, root->left->right) == root->left) << std::endl;

}