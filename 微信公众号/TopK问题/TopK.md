<center><font color="#FFA500" size="6">TopK问题</font></center>

[TOC]

# 1 问题描述

就是在arr[1,n]这n个数中，找出最大的K个数

# 2 解法思路

## 2.1 排序法

新从小到大排序，取最后的K个数。显然这种算法的复杂度平均来说是$O(n\log_2n)$，不再赘述

## 2.2 冒泡排序法

只需要找出最大的N个数，上述算法却对剩余的N-K个数也进行了排序，这就是上述算法效率低的原因。对于那些不需要的数，是否可以不排序呢？我们可以使用冒泡排序的思想，最坏只需要进行K轮冒泡即可；

```C
void bubbleTopK(int *arr,int len,int k){
    int flag,t;
    for(int i = 0;i<k;++i){
        flag = 0;
        for(int j = 0;j<len-1-i;++j){
            if(arr[j]>arr[j+1]){
                t = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
                flag=1;
            }
        }
        if(!flag)break;
    }
}
```

## 2.3 堆排序法

题目要求找出topK，但是这K个数不一定是有序的，上述2.2算法额外对K个数进行了排序，这是影响效率的原因。能否找出这K个数但是不排序呢？[这里先了解堆的数据结构以后在更新]

