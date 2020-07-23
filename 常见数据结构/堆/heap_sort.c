#include <stdio.h>

void swap(int* arr,int i,int j) {
        int a = arr[i],b = arr[j];
        if(i!=j&&a!=b) {
                arr[i]=b;
                arr[j]=a;
        }
}

void adjust_heap(int* arr,int adjust_index,int len){
        int temp = arr[adjust_index];
        for(int i = 2*adjust_index+1; i<len; i = i*2+1) {
                if(i+1<len&&arr[i]<arr[i+1]) {
                        i++;
                }
                if(arr[i]>temp) {
                        arr[adjust_index] = arr[i];
                        adjust_index = i;
                }
                arr[adjust_index] = temp;
        }
}

void build_heap(int* arr,int len){
        if(len<=1) return;
        for(int i = len/2-1; i>-1; --i)
                adjust_heap(arr,i,len);
}

void heap_sort(int* arr,int len){
        build_heap(arr,len);
        for(int i=len-1; i>0; --i) {
                swap(arr,i,0);
                adjust_heap(arr,0,i);
        }
}

int main(int argc, char const *argv[]) {
        int arr[] = {1,3,5,7,9,2,4,6,8,10};
        heap_sort(arr,10);
        for(int i=0; i<10; ++i) {
                printf("%d ",arr[i]);
        }
        return 0;
}
