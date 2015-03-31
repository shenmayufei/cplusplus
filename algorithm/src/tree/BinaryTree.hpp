/**************************************************************************
 * author:   zhaosl
 * created:  20150322
 * purpose:  二叉树的实现，遍历（前序遍历、中序遍历、后序遍历,层序遍历
 *************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <queue>

namespace zhaosl
{
    template <typename T>
    class BinaryTree;

    template <typename T>
    class BinaryTreeNode
    {
    friend class BinaryTree<T>;  // 声明为友元类，便于访问私有数据变量
    private:
        T         m_data;    // 节点中的数据
        BinaryTreeNode<T>   * m_pLeft;
        BinaryTreeNode<T>   * m_pRight;
    public:
        BinaryTreeNode()
        :m_pLeft(NULL)
        ,m_pRight(NULL)
        {
        };

        BinaryTreeNode(const T& value)
        :m_data(value)
        ,m_pLeft(NULL)
        ,m_pRight(NULL)
        {
        };

        T value() const;                    // 返回当前节点的数据
        BinaryTreeNode<T> * getLeft() const;      // 左子树
        BinaryTreeNode<T> * getRight() const;     // m_pRight child Node
        void setLeft(BinaryTreeNode<T> * newNode); 
        void setRight(BinaryTreeNode<T> * newNode);
        void setValue(const T& value);         // 设置当前节点的数据域
        bool isLeaf() const;                      // 判断当前节点是否是叶子节点
        BinaryTreeNode <T> & operator= (const BinaryTreeNode <T> & newNode);   // 重载赋值操作符

        BinaryTreeNode<T> * findParent(BinaryTreeNode<T> * curr);
    };

    template <typename T>
    class BinaryTree
    {
    private:
        BinaryTreeNode<T> * m_pRoot;                   // 根节点
        BinaryTreeNode<T> * findParent(BinaryTreeNode<T> * curr);
    public:
        BinaryTree() {m_pRoot = NULL;};
        ~BinaryTree() { deleteTree(m_pRoot);};
        bool isEmpty() const { return NULL==m_pRoot; };
        BinaryTreeNode<T> * root() {return m_pRoot;};
        BinaryTreeNode<T> * parent(BinaryTreeNode<T> * curr);  
        BinaryTreeNode<T> * leftSibling(BinaryTreeNode<T> * curr);
        BinaryTreeNode<T> * rightSibling(BinaryTreeNode<T> * curr);     // 返回当前节点的右兄弟，根节点的 为 NULL
        void createTree(const T& root, BinaryTree<T>& leftChild, BinaryTree<T>& rightChild);
        
        void preOrder(BinaryTreeNode<T> * root, std::vector<T> & result);        // 前序遍历
        void inOrder(BinaryTreeNode<T> * root, std::vector<T> & result);         // 中序遍历
        void postOrder(BinaryTreeNode<T> * root, std::vector<T> & result);       // 后序遍历
        void levelOrder(BinaryTreeNode<T> * root, std::vector<T> & result);      // 层序遍历

        void deleteTree(BinaryTreeNode<T> * root);                      // 删除给定的二叉树
    private:
        bool copyNodes(BinaryTreeNode<T> *root, const BinaryTreeNode<T> *left, const BinaryTreeNode<T> *right);
    };

    template <typename T>
    T BinaryTreeNode<T>::value() const
    {
        return m_data;
    }

    template <typename T>
    BinaryTreeNode<T> * BinaryTreeNode<T>::getLeft() const
    {
        return m_pLeft;
    }

    template <typename T>
    BinaryTreeNode<T> * BinaryTreeNode<T>::getRight() const
    {
        return m_pRight;
    }

    template <typename T>
    void BinaryTreeNode<T>::setLeft(BinaryTreeNode<T> * newNode)
    {
        m_pLeft = newNode;
    }
    
    template <typename T>
    void BinaryTreeNode<T>::setRight(BinaryTreeNode<T> * newNode)
    {
        m_pRight = newNode;
    }

    template <typename T>
    void BinaryTreeNode<T>::setValue(const T& value)
    {
        m_data = value;
    }

    template <typename T>
    bool BinaryTreeNode<T>::isLeaf() const
    {
        return NULL == m_pLeft && NULL==m_pRight;
    }

    template <typename T>
    BinaryTreeNode<T> & BinaryTreeNode<T>::operator= (const BinaryTreeNode<T> & newNode)
    {
        *this = newNode;
    }

    template <typename T>
    BinaryTreeNode<T> * BinaryTreeNode<T>::findParent(BinaryTreeNode<T> * curr)
    {
        if(m_pLeft == curr || m_pRight == curr) return this;  // 能够找到的情况（递归结束，查找成功）

        BinaryTreeNode<T> * tmpNode = NULL;
        if(NULL != m_pLeft)
        {
            tmpNode = m_pLeft->findParent(curr);
        }

        if(NULL != tmpNode) return tmpNode;   // 左子树下找到
        if(NULL == m_pRight) return NULL;     // 左子树查找失败，右子树为空
        return m_pRight->findParent(curr);  // 左子树查找失败，在右子树找（递归进行）
    }

    // 方法的实现
    template <typename T>
    BinaryTreeNode<T> * BinaryTree<T>::parent(BinaryTreeNode<T> * curr)
    {
        return m_pRoot->findParent(curr);
    }

    template <typename T>
    BinaryTreeNode<T> * BinaryTree<T>::leftSibling(BinaryTreeNode<T> * curr)
    {
        BinaryTreeNode<T> * parent = m_pRoot->findParent(curr);
        return parent;
    }

    template <typename T>
    BinaryTreeNode<T> * BinaryTree<T>::rightSibling(BinaryTreeNode<T> * curr)     // 返回当前节点的右兄弟，根节点的 为 NULL
    {
        BinaryTreeNode<T> * parent = m_pRoot->findParent(curr);
        return parent;
    }

    
    template <typename T>
    bool BinaryTree<T>::copyNodes(BinaryTreeNode<T> *root, const BinaryTreeNode<T> *left, const BinaryTreeNode<T> *right)
    {
        if(NULL != left)
        {
        
            BinaryTreeNode<T> * tmpNode = new BinaryTreeNode<T>(*left);
            if(NULL == tmpNode) return false;
            root->setLeft(tmpNode);
            copyNodes(root->getLeft(), left->getLeft(), left->getRight());
        }
        else
        {
            root->setLeft(NULL);
        }

        if(NULL != right)
        {
            BinaryTreeNode<T> * tmpNode = new BinaryTreeNode<T>(*right);
            if(NULL == tmpNode) return false; 
            root->setRight(tmpNode);
            copyNodes(root->getRight(), right->getLeft(), right->getRight());
        }
        else
        {
            root->setRight(NULL);
        }

        return true;
    }

    template <typename T>
    void BinaryTree<T>::createTree(const T& root, BinaryTree<T>& leftChild, BinaryTree<T>& rightChild)
    {
        m_pRoot = new BinaryTreeNode<T>(root);
        if(NULL == m_pRoot) return ;
        copyNodes(m_pRoot, leftChild.root(), rightChild.root());
    }
             
    template <typename T>
    void BinaryTree<T>::preOrder(BinaryTreeNode<T> * root, std::vector<T> & result)                        // 前序遍历
    {
        // 递归实现
        if(NULL == root) return ;

        result.push_back(root->value());
        preOrder(root->getLeft(), result);
        preOrder(root->getRight(), result);
    }

    template <typename T>
    void BinaryTree<T>::inOrder(BinaryTreeNode<T> * root, std::vector<T> & result)                         // 中序遍历
    {
        // 递归实现
        if(NULL == root) return;
        inOrder(root->getLeft(), result);
        result.push_back(root->value());
        inOrder(root->getRight(), result);
    }

    template <typename T>
    void BinaryTree<T>::postOrder(BinaryTreeNode<T> * root, std::vector<T> & result)                       // 后序遍历
    {
        if(NULL == root) return ;
        postOrder(root->getLeft(), result);
        postOrder(root->getRight(), result);
        result.push_back(root->value());
    }

    template <typename T>
    void BinaryTree<T>::levelOrder(BinaryTreeNode<T> * root, std::vector<T> & result)                      // 层序遍历
    {
        if(NULL == root) return ;
        std::queue<T> q;
        q.push_back(root);
        while(!q.empty())
        {
            BinaryTreeNode<T> * tmpNode = q.pop_front();
            result.push_back(tmpNode->value());
            if(NULL != tmpNode->getLeft()) q.push_back(tmpNode->getLeft());
            if(NULL != tmpNode->getRight()) q.push_back(tmpNode->getRight());
        }
    }

    template <typename T>
    void BinaryTree<T>::deleteTree(BinaryTreeNode<T> * root)                      // 删除给定的二叉树
    {
        if(NULL == root) return ;
        deleteTree(root->getLeft());
        deleteTree(root->getRight());
        delete root;
    }
}

#endif
