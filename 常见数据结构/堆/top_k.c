#include <stdio.h>

void swap(int* arr,int i,int j){
        int a = arr[i],b = arr[j];
        if(i!=j&&a!=b) {
                arr[i]=b;
                arr[j] =a;
        }
}

void adjust_heap(int* arr,int i,int len){
        int tmp = arr[i];
        /**
         * 维护小顶堆
         */
        for(int k = 2*i+1; k<len; k = 2*k+1) {
                if(k+1<len&&arr[k]>arr[k+1]) {
                        k++;
                }
                if(arr[i]>arr[k]) {
                        arr[i] = arr[k];
                        i = k;
                }
        }
        arr[i] = tmp;
}

void build_heap(int* arr,int len){
        for(int i = (len>>1)-1; i>-1; --i) {
                adjust_heap(arr,i,len);
        }
}

void top_k(int* arr,int* top_k,int k,int len){
        for(int i=0; i<k; ++i) {
                top_k[i] = arr[i];
        }
        build_heap(top_k,k);
        for(int i = k; i<len; ++i) {
                if(arr[i]>top_k[0]) {
                        top_k[0] = arr[i];
                        adjust_heap(top_k,0,k);
                }
        }
}

int main(int argc, char const *argv[]) {
        int arr[10] = {1,3,5,7,9,2,4,6,8,10};
        int top_3[3];
        top_k(arr,top_3,3,10);
        for(int i=0; i<3; ++i) {
                printf("%d ",top_3[i]);
        }
        return 0;
}
