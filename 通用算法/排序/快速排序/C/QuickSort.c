#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int arr[], int i, int j) {
	if (i != j && arr[i] != arr[j]) {
		int t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
	}
}

//generate random number between start and end
int baseIndex(int start, int end) {
	srand((unsigned)time(NULL));
	return rand() % (end - start + 1) + start;
}

//区间法
int partition1(int array[],int start,int end){
	int base = baseIndex(start,end);
	//printf("base=%d\n",base);
	swap(array,base,end);
	int flag_num = array[end];
	int left_bound=start-1;//left_bound始终是小于基准的那一半数组的最后一个元素的位置
	for(int i=start;i<end;++i){
		if(array[i]<flag_num){
			++left_bound;
			if(i!=left_bound)swap(array,i,left_bound);
		}
	}
	++left_bound;
	swap(array,end,left_bound);
	return left_bound;
}

//数据结构书上讲的方法 甩锅法
int partition2(int array[], int start, int end) {
	int base = baseIndex(start, end);
	swap(array, base, start);
	int flag_num = array[start];
	int i = start, j = end;
	while (i < j) {
		while (array[j] > flag_num&& j > i)--j;
		if (j == i)break;
		else array[i++] = array[j];//一边遇到不符合条件的，甩给另一边
		while (array[i] <= flag_num && i < j)++i;
		if (i == j)break;
		else array[j--] = array[i];
	}
	array[j] = flag_num;
	return j;
}

//优化partition2函数
int partition3(int array[], int start, int end) {
	int base = baseIndex(start, end);
	swap(array, base, start);
	int flag_num = array[start];
	int i = start, j = end;
	while (i < j) {
		while (j > i&& array[j] > flag_num)--j;
		array[i] = array[j];//不让i+1，让判断是否等于的代码合入while
		while (i < j && array[i] <= flag_num)++i;
		array[j] = array[i];
	}
	array[j] = flag_num;
	return j;
}

//哨兵法
int partition4(int array[], int start, int end) {
	int base = baseIndex(start, end);
	swap(array, base, start);
	int flag_num = array[start];
	int left = start, right = end;//左右两个哨兵
	while (left < right) {
		while (left < right && array[right] >= flag_num)--right;//不符合条件停下来
		while (left < right && array[left] <= flag_num)++left;
		if (left < right)swap(array, left, right);//两个哨兵都停下来的时候，如果left<right，交换二者
	}
	swap(array, start, right);//交换基准
	return right;
}

/*
以上的partition方法
*/

void m_qsort(int array[], int start, int end) {
	if (start == end)return;
	int spliter = partition4(array, start, end);
	if (spliter > start)m_qsort(array, start, spliter - 1);
	if (spliter < end)m_qsort(array, spliter + 1, end);
}

void print_array(int array[], int start, int end) {
	if (array != NULL) {
		if (start <= end) {
			int i = start;
			printf("[");
			while (i < end)
				printf("%d,", array[i++]);
			printf("%d]\n", array[i]);
		}
		else {
			printf("[]\n");
		}
	}
	else {
		printf("[]\n");
	}
}

void runQsort(int array[], int start, int end) {
	printf("before sort\n");
	print_array(array, start, end);
	m_qsort(array, start, end);
	printf("after sort\n");
	print_array(array, start, end);
}
int main() {
	int arr[10] = { 1,3,5,7,9,2,4,6,8,10 };
	runQsort(arr, 0, 9);

	int arr1[] = { 1 };
	runQsort(arr1, 0, 0);

	int arr2[] = { 1,3 };
	runQsort(arr2, 0, 1);

	int arr3[10] = { 1,3,5,7,9,2,4,6,8,10 };
	runQsort(arr3, 0, 7);

	return 0;
}