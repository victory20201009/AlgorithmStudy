#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

class Solution{
public:
    vector<int> towSum(vector<int>&nums, int target){
        int len = nums.size(),tmp;
        unordered_map<int,int> map;
        vector<int> res(2);
        for(int i=0;i<len;++i){
            tmp=target-nums[i];
            if(map.find(tmp)!=map.end()){
                res[0]=i;
                res[1]=map[tmp];
                return res;
            }
            map[nums[i]]=i;
        }  
    }
};


int main(){
    Solution solution;
    int iarr[]={2,7,11,15};
    vector<int> nums,res;
    for(int i=0;i<4;++i){
        nums.push_back(iarr[i]);
    }
    res=solution.towSum(nums,9);
    cout<<res[0]<<" "<<res[1]<<endl;
    return 0;
}
