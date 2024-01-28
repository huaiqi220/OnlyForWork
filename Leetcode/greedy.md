## 455 分发饼干
两个sort，然后给每个小孩分配够他需要的最小的饼干

```CPP
// 贪心 双指针实现
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(),g.end());
    sort(s.begin(),s.end());
    int i = 0; int j = 0;
    int count = 0;
    while(i < g.size() and j < s.size()){
        if(g[i]<= s[j]){
            i++;
            j++;
            count++;
        }else {
            j++;
        }
    }
    return count;
}
```

## 376 摆动序列


## 55 跳跃游戏
贪心算法，每次都遍历当前轮次的开始位置和当前最大结束位置，不断更新最大结束位置，如果最大结束位置大于等于数组长度，说明可以到达最后一个位置
while循环的结束条件显然为startindex == tempEnd;
```CPP
bool canJump(vector<int>& nums) {
    int startindex = 0;
    int tempEnd = nums[0];
    while(startindex != tempEnd and tempEnd <= nums.size() - 1){
        int epochMax = tempEnd;
        for(int i = startindex; i <= tempEnd; i++){
            epochMax = i + nums[i] > epochMax ? i + nums[i] : epochMax;
        }
        startindex = tempEnd;
        tempEnd = epochMax;
    }
    if(tempEnd >= nums.size() - 1){
        return true;
    }
    return false;
}
```

## 45 跳跃游戏II
跟55的区别是本题要返回跳跃次数，我在每次更新tempEnd的时候，count++，最后返回count

这种方法结果是真确的吗？先试试
```CPP
    // 我的方法实现起来太复杂了，还容易错，直接学这个随想录方法
    int jump(vector<int>& nums) {
        int curDistance = 0;
        int ans = 0;
        int nextDistance = 0;
        for(int i = 0; i < nums.size() - 1; i++){
            nextDistance = max(nums[i] + i, nextDistance);
            if(i == curDistance){
                curDistance = nextDistance;
                ans++;
            }
        }
        return ans;
    }
```

## 1005 K次取反后最大化的数组和
这题我做的时候很纠结，又是正负分类讨论，又是取反次数跟负值个数的讨论，又是讨论有没有0
看看随想录的方法
```CPP
// 很巧妙，比我自己那抽象的很的什么分类讨论，正负数组，是否有0布尔量，简单多了
class Solution {
    static bool cmp(int x, int y){
        return abs(x) > abs(y);
    }
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end(),cmp);
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] < 0 and k != 0){
                nums[i] *= -1;
                k--;
            }
        }
        if (k % 2 == 1) nums[nums.size() - 1] *= -1;
        int res = 0;
        for(auto item : nums)res += item;
        return res;
    }
};
```

## 134 加油站
首先gas与cost做差找到可以起始的加油站，然后遍历开始搜索，方法比较暴力
最坏复杂度为n^2
```CPP
// not a good solution
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    vector<int> temp(gas.size(),0);
    for(int i = 0; i < temp.size(); i++){
        temp[i] = gas[i] - cost[i];
    }
    int tempGas = 0;
    for(int i = 0; i < temp.size(); i++){
        if(temp[i] >= 0)// 可以到达下一个目标
        {
            if(canReach(gas,cost,i)){
                return i;
            }
        }
    }
    return -1;
}
bool canReach(vector<int>& gas, vector<int>& cost,int sindex){
    int tempGas = gas[sindex] - cost[sindex];
    int curIndex = sindex + 1;
    while(curIndex != sindex){
        if(curIndex > gas.size() - 1)curIndex = curIndex % gas.size();
        if(tempGas + gas[curIndex] >= cost[curIndex]){
            tempGas = tempGas + gas[curIndex] - cost[curIndex];
            curIndex++;
        }else{
            return false;
        }
    }
    return true;
}
```
实际方法，贪心，省了很多重复计算
```CPP
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int totalSum = 0;
        int start = 0;
        for(int i = 0; i < gas.size(); i++){
            curSum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            if(curSum < 0){
                start = i + 1;
                curSum = 0;
            }
        }
        if(totalSum < 0)return -1;
        return start;
    }  
```

## 135 分发糖果
我一直有个思路，从最低的开始分配，从小到大，依次排序。可能一次遍历，判断左右大小，就能得到结果
但这个做法要写一个比较函数，建一个结构体的vector，有点麻烦，不如两次遍历，左遍历调大小，右遍历调大小
```CPP
// 非常巧妙的方法，第一遍调好左关系，第二遍通过max维持住了第一遍关系的同时调好了右关系
// 这个解答要背住
int candy(vector<int>& ratings) {
    vector<int> candy(ratings.size(),1);
    for(int i = 1; i < ratings.size(); i++){
        if(ratings[i] > ratings[i - 1])candy[i] = candy[i - 1] + 1;
    }
    for(int i = ratings.size() - 2; i >= 0 ; i--){
        if(ratings[i] > ratings[i + 1])candy[i]  = max(candy[i], candy[i + 1] + 1);
    }
    int res = 0;
    for(auto item : candy) res += item;
    return res;
}
```

## 406 根据身高重建队列
这题，最重要的思路，就是高的人眼里只看得见比他更高的，所以从大往小处理就ok
其次，当两人身高一样高的时候，眼里也是看得见的，说人话就是，先拍k小的，再拍k大的
所以要针对这种排序，自己写一个排序函数(这块还不熟，要记住)
```CPP
static bool specialSort(vector<int>& i1,vector<int>& i2){
    // 特殊的排序函数
    if(i1[0] != i2[0]){
        return i1[0] > i2[0];
    }else{
        return i1[1] < i2[1];
    }
}
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(),people.end(),specialSort);
    list<vector<int>> que;
    for(int i = 0; i < people.size(); i++){
        int position = people[i][1];
        // list的插入时间开销更小
        list<vector<int>>::iterator it = que.begin();
        while(position--){
            it++;
        }
        que.insert(it,people[i]);
    }
    // vector提供了构造函数直接从list转为vector
    return vector<vector<int>>(que.begin(),que.end());
}
```
## 452 用最少数量的箭引爆气球
首先思路上，从重叠最多的位置开射，是正确的，不存在什么，只射部分，再射两边箭更少的反例
其次，我一开始希望用的方法是，什么标记数组，然后遍历气球填重叠数组，然后找最大，再剔除气球，再修改标记数组
这个方法可能是对的？我没写，太繁琐，时间复杂度不低
正确方法：
```CPP
// 先排序，再遍历，当经过了重叠气球的最小右边界，就需要一支箭
static bool cmp(const vector<int>& a, const vector<int>& b){
    return a[0] < b[0];
}
int findMinArrowShots(vector<vector<int>>& points) {
    if(points.size() == 0) return 0;
    sort(points.begin(),points.end(),cmp);
    int result = 1;
    for(int i = 1; i < points.size(); i++){
        if(points[i][0] > points[i - 1][1]){
            result++;
        }else{
            points[i][1] = min(points[i - 1][1],points[i][1]);
        }
    }
    return result;
}
```
