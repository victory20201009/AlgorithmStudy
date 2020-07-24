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

# 2. AVL树的操作

## 2.1 旋转操作

AVL树插入时，与BST操作是一样的。当数据插入完毕时，有可能破坏AVL的平衡特性，需要对数据做调整以保证其平衡特性。

[图暂缺]

当插入一个结点时造成整棵树不平衡时，我们需要从插入的结点开始，向上不断获取其父节点，计算父节点的平衡因子，找到第一个不平衡的子树的根r为止。不失一般性，我们先假设，r的右孩子为r_right，左孩子l_left，当r的左右孩子是NULL或者为叶子时，树是平衡的。不失一般性，我们假设r的左右孩子都不为NULL，那么造成r不平衡的原因主要是，有一个节点数为2的子树subAVLTree，挂在其左孩子或右孩子上，很显然，有四种情况：

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

   这些结点的中序遍历顺序是：subAVLTree，r_left，r_left_right，r，r_right我们的移动之后要保证这个顺序不变即可。那么我们可以怎么移动呢？移动方法是：把r变成r_left的右子树，r_left原来的右子树，变成r的左子树，r_left代替原来r的位置(图以后再画)。那么这样转换之后的中序遍历结果如下：

   subAVLTree，r_left，r_left_right，r，r_right，跟原来一样的，从结果来看，这种转换合理。
   
   **那么为什么这样的转换就是合理的呢？**其实在二叉树的中序遍历中，一个结点的前驱结点是其左子树的最后一个结点，即要么是其左子树的根，要么是其左子树的右子树上最右边的结点；一个结点的后继结点是其右子树上的第一个结点，即要么是其右子树的根，要么是右子树的左子树最左边的结点；那么在刚才的变换中，发生结点改变的，是r_left的右子树，r的左子树；我们不妨把r_left_right看成一个结点的树，那么r_left的后继就是r_left_right，同时，r_left_right也是r的前驱；转换以后，由于r变成r_left的右子树，r的后继就会其右子树的最左边的结点，就是r的左子树，即r_left_right；对于r来说，其前驱就是其左子树最右边的结点，还是r的左子树，即r_left_right；因此这种方式并不影响中序遍历的结果，即不影响二叉排序树的排序性质，因此是可行的。
   
   **这样的操作成为右旋**
   
2. subAVLTree是r_left的右子树，左子树记为 r_left_left。这样的情况下，只需要把r_left做一下左旋操作，即可转换为第一种的形式。左旋是右旋的逆操作。也就是把subAVLTree的根替代r_left的根，原来的r_left作为subAVLTree的左子树，subAVLTree原来的左子树，变成现在r_left的右子树。

3. 那么对应的，subAVLTree是r_right的右子树，左子树记为 r_right_left这种情况下，只需要对r做一下左旋操作，即：r_right替代r的位置，原板的r作为r_right的左子树，r_right原来的左子树，变为现在r的右子树。

4. subAVLTree是r_right的左子树，右子树记为 r_right_right，这样的情况下只需要对r_right做一次右旋操作，就可以变成第四种情况了，即：subAVLTree替代r_right的位置，r_right作为现在subAVLTree的右子树，原来subAVLTree的右子树，变成现在r_right的左子树。

这就是左旋和右选的操作。

# 3 AVL树的关键函数代码

## 3.1 计算平衡因子

```C++
int getBalance(AVLTree* node){
    if(!node)return 0;
    /**
    * 左子树的高度减去右子树的高度
    */
    return height(node->left)-height(node->right);
}
```

## 3.2 左旋

```C++
/**
* 堆某颗树进行左旋
*/
AVLTree* leftRotate(AVLTree* node){
    AVLTree* tnode = node;
    if(tnode){
        /*暂存其右子树*/
        AVLTree* tRight = node->right;
         /*暂存其右子树的左子树*/
        AVLTree* tRightLeft = tRight->left;
        /*原来的根节点变为其左子树*/
        tRight->left = node;
        /*原来的根的右子树的左子树 变为现在node的右子树*/
        node->right = tRightLeft;
        /*现在的tRight替代原来的根节点的位置*/
        tnode = tRight；
    }
    return tnode;
}
```

## 3.3 右旋

```C++
/**
* 堆某颗树进行右旋
*/
AVLTree* rightRotate(AVLTree* node){
    AVLTree* tnode = node;
    if(tnode){
        /*暂存其右子树*/
        AVLTree* tLeft = node->left;
         /*暂存其左子树的右子树*/
        AVLTree* tLeftRight = tLeft->right;
        /*原来的根节点变为其右子树*/
        tLeft->right = node;
        /*原来的根的左子树的右子树 变为现在node的左子树*/
        node->left = tLeftRight;
        /*现在的tLeft替代原来的根节点的位置*/
        tnode = tLeft；
    }
    return tnode;
}
```

## 3.4 插入

```C++
AVLTree* insert(AVLTree* node,int k){
    if(!node){
        /*说明找到了空位置*/
        return new AVLTree(k);
    }
    /*否则继续寻找插入的位置*/
    if(k<node->k){
        /*小于当前值，则放在左子树*/
        node->left = insert(node->left,k);
    }else if(k>node->k){
        node->right = insert(node->right,k)
    }else {
        throw "duplicate element";
    }
    /*计算平衡因子*/
    int balance = getBalance(node);
    /*左边高度太高,表示新的结点在其左子树*/
    if(balance>1){
        /*表示新的结点在其左子树的左子树上，因此右旋*/
        if(k>node->left->k){
            /*表示新的结点在其左子树的右子树上，因此先左旋，再右旋*/
            node->left = leftRotate(node->left);
        }
        node = rightRotate(node); 
    }
     /*右边高度太高,表示新的结点在其右子树*/
    if(balance<-1){
         if(k<node->right->k){
            /*表示新的结点在其右子树的左子树上，因此先右旋，再左旋*/
            node->right = rightRotate(node->right);
        }
        node = leftRotate(node);
    }
    return node;
}
```

