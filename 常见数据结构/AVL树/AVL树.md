<center><font color="#FFA500" size="6">AVL树</font></center>
[TOC]

# 1.AVL树的概念

AVL树是一种高级的**二叉搜索树(BST)**，为啥说它高级呢？是因为它是自平衡的，能够保证其左右子树的高度差不会大于1，这样就保证了在搜索的时候，最坏情况下，时间复杂度也不会退化为$O(n)$。

下面就是定义：

AVL树是：一棵空树，或者是一棵BST，这时要满足： 

1. 左右子树的高度差不超过1；
2. 左右子树也是AVL树。

AVL树有一个描述左右子树的高度差的指标：平衡因子(Balanced Factor)，它的计算方法：BF = 左子树高度 - 右子树高度

树的高度的计算方法，不妨按照如下计算：

```C++
int height(AVLTree* node){
    if(!node)return 0;
    return max(height(node->left),height(node->right))+1;//严格来说，这样算出来的应该叫做层数，但是并不影响我们计算平衡因子
}
```

# 2. AVL树的插入操作

AVL树插入时，与BST操作是一样的。当数据插入完毕时，有可能破坏AVL的平衡特性，需要对数据做调整以保证其平衡特性。

[图暂缺]

当插入一个结点时造成整棵树不平衡时，我们需要从插入的结点开始，向上不断获取其父节点，计算父节点的平衡因子，找到第一个不平衡的子树的根r为止。不失一般性，我们先假设，r的右孩子为r_right，左孩子l_left，当r的左右孩子是NULL或者为叶子时，树是平衡的。不是一般性，我们假设r的左右孩子都不为NULL，那么造成r不平衡的原因主要是，有一个节点数至少为2的子树subAVLTree，挂在其左孩子或右孩子上，很显然，有四种情况：

- subAVLTree是r_left的左子树，右子树记为 r_left_right
- subAVLTree是r_left的右子树，左子树记为 r_left_left
- subAVLTree是r_right的左子树，右子树记为 r_right_right
- subAVLTree是r_right的右子树，左子树记为 r_right_left

下面逐一考虑：

1. subAVLTree是r_left的左子树，右子树记为 r_left_right

   这样的话就是左边的高度太高了，导致了平衡因子>1，需要把r左边的元素移动到最右边一些。那怎么移动呢？怎样的移动是正确的呢？移动之前我们考虑一下结点：

   - r
   - r_right
   - r_left
   - subAVLTree
   - r_left_right

   这些结点的中序遍历顺序是：subAVLTree，r_left_right，r_left，r，r_right我们的移动之后要保证这个顺序不变即可。

   