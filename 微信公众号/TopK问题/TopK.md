<center><font color="#FFA500" size="6">TopK问题</font></center>

[TOC]

# 1 问题描述

就是在arr[1,n]这n个数中，找出最大的K个数

# 2 解法思路

## 2.1 排序法

新从小到大排序，取最后的K个数。显然这种算法的复杂度平均来说是$$