

def towSum(nums,target):
    lens=len(nums);
    j=-1;
    for i in range(1,lens):
        tmp=nums[:i];
        if(target-nums[i]) in tmp:
            j=tmp.index(target- nums[i]);
            break;
    if(j>=0):
        return [i,j];
         
         
def twoSum2(nums,target):
    map={};
    for index,num in enumerate(nums):
        index2=map.get(target-num);
        if index2 is not None:
            return [index,index2];
        map[num]=index;


def twoSum3(nums,target):
    map={};
    for i,n in enumerate(nums):
        if target - n in map:
            return [i,map[target-n]]
        map[n]=i
        
        
        
if __name__ == "__main__":
    nums=[2,7,12,4];
    res = twoSum3(nums,9);
    print(str(res[0])+"---"+str(res[1]));