package leetcode.two_sum;

import java.util.HashMap;

public class Solution{
    
    public static void main(String[] args){
        int[] arr={2,7,11,15};
        int[] res = towSum(arr,9);
        System.out.println(res[0]+"---"+res[1]);
    }
    
    public static int[] towSum(int[] nums,int target){
        int[] res = new int[2];
        int tmp;
        HashMap<Integer,Integer> map = new HashMap<>();
        for(int i=0;i<nums.length;++i){
            tmp = target-nums[i];
            if(map.containsKey(tmp)){
                res[0]=i;
                res[1]=map.get(tmp);
                break;
            }
            map.put(nums[i],i);
        }
        return res;
    }
}