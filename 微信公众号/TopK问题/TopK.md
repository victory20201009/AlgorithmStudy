<center><font color="#FFA500" size="6">TopK问题</font></center>

[TOC]

# 1 问题描述

就是在arr[1,n]这n个数中，找出最大的K个数($K\in[1,n]$)

# 2 解法思路

## 2.1 排序法

新从小到大排序，取最后的K个数。显然这种算法的复杂度平均来说是$O(n\log_2n)$，不再赘述

## 2.2 冒泡排序法

只需要找出最大的N个数，上述算法却对整个N个数进行了排序，做了好多无用的计算，这就是上述算法效率低的原因。对于那些不需要的数，是否可以不用理会呢？我们可以使用冒泡排序的思想，最坏只需要进行K轮冒泡即可；

```C
void bubbleTopK(int *arr,int len,int k){
    if(k>len||len<=0||k<1)return;
    int flag,t;
    for(int i = 0;i<k;++i){//进行K次冒泡
        flag = 0;
        for(int j = 0;j<len-1-i;++j){//每次找出最大的
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

最后取[len-k,len-1]即可，(k>=1)

## 2.3 堆排序法

题目要求找出topK，但是并没有要求排序，上述2.2算法额外对K个数进行了排序，这是影响效率的原因。能否找出这K个数但是不排序呢？可以使用堆排序。

找出数组的前K个元素，维护一个小顶堆，遍历剩下的元素，当当前元素比堆顶大时，替换堆顶，调整堆。这样，当遍历完毕的时候，堆顶元素就是整个堆最小的元素，由于堆元素个数为K，那堆顶就是原数组第K大的元素，自然堆中的所有元素即为topK。

时间复杂度：设当前数组元素个数N，调整堆的时间$O(\log_2K)$，调整的次数$N-K$，所以时间复杂度$(N-K)\log_2K$。

##  2.4 减治法

快速排序的partition函数，可以在$O(N)$的复杂度内，把数组分为两份，左边的小于基准，右边的大于基准。如果能找到第K大的数，那么通过一次partition操作，即可在线性复杂度内解决topK问题。对于如何找第大的数，可以做以下考虑：

对数组partition后，左边的小于基准，右边的大于基准：

- 如果右边的个数=K-1，那么显然基准就是第K 大的元素；
- 如果右边的个数>=K，第K大的元素在右边部分，递归右边区域即可；
- 否则，第K大的元素在左边部分，设右边部分的元素个数为R，在左边部分中，只需要递归第K-(R+1)大的元素即可。

代码如下：

```C++
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        sort(nums.begin(), nums.begin()+nums.size());

        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        if (nums.size() == 2)
            return nums[1];
        if (nums.size() == 1)
            return nums[0];
        std::cout << nums.size() << std::endl;
        return quickSelect(nums, 3, 0, nums.size()-1);

    }

    int partition(vector<int>& arr, int left, int right){
        int i = left, j = right + 1, pivot = arr[left];
        while(true){
            while (i < right && arr[++i] > pivot)
                if (i == right) break;
            while (j > left && arr[--j] < pivot)
                if (j == left) break;
            if (i >= j) break;
            swap(arr, i, j);
        }
        swap(arr, left, j);
        return j;
    }

    void swap(vector<int>& arr, int i, int j){
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    int quickSelect(vector<int>& arr, int k, int left, int right){
        if (left == right)
            return arr[right];
        int index = partition(arr, left, right);
        std::cout << "index" << index << std::endl;
        if (index - left + 1 > k)
            return quickSelect(arr, k, left, index - 1);
        else if (index - left + 1 == k){
            std::cout << arr[index] << std::endl;
            return arr[index];
        }
        else 
            return quickSelect(arr, k - index + left - 1, index + 1, right);
        
    }
};
```

平均来说，每次partition都把原数组分等长的两份，递归到什么时候两边的数组长度是常数级别呢？其阶应该是$O(\log_2N)$，也就是partition的次数，第一次partition是按复杂度$O(N)$，第二次partition时间复杂度$O(\frac{N}{2})$，......，第K次partition时间复杂度$O(\frac{N}{2^{K-1}})$，前K项和$S(K) = N\frac{1-(\frac{1}{2})^K}{1-\frac{1}{2}} = 2N(1-(\frac{1}{2})^K)$，代入执行次数$O(\log_2N)$，得到$S(\log_2N) = 2N(1-\frac{1}{N}) = 2N-2=O(N)$，这个方法的平均时间复杂度$O(N)$。

