/**************************************************************************
 * author:   zhaosl
 * created:  20150322
 * purpose:  二叉树的实现，遍历（前序遍历、中序遍历、后序遍历,层序遍历
 *************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

namespace zhaosl
{
    template <typename T>
    class BinaryTreeNode
    {
    friend class BinaryTree<T>;  // 声明为友元类，便于访问私有数据变量
    private:
        T         data;    // 节点中的数据
        BinaryTreeNode<T>   * left;
        BinaryTreeNode<T>   * right;
    public:
        BinaryTreeNode()
        :left(NULL)
        ,right(NULL)
        {
        };

        BinaryTreeNode(const T& value)
        :data(value)
        ,left(NULL)
        ,right(NULL)
        {
        }
        

    };

    template <typename T>
    class BinaryTree
    {
    };


    // 方法的实现
}

#endif
