# 动态规划

## 509 Fibonacci

太经典了没啥好说的，注意n == 0,1,2时候别让数组越界出现运行错误就ok

## 746 最小花费爬楼梯 && 70 爬楼梯

算法大差不差，递推公式一个是
```CPP
dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);

dp[i] = dp[i-1] + dp[i-2]

```

## 62 不同路径 && 63 不同路径2

```CPP
dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
```
不写了，做过很多遍。

63在62基础上查一下表，如果是与障碍物相邻就只加没障碍的那边

## 343 整数拆分

这题大半年前做过，当时做的特别复杂，代码我都不认识

现在以一个标准dp的方式来做，把递推公式想明白了，代码其实很简洁

```CPP
int integerBreak(int n) {
    int nn = n >= 3 ? n : 3;
    vector<int> dp(nn+1,0);  
    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 2;
    for(int i = 3; i <= nn; i++ ){
        int ans = 0;
        // 核心就是下面这个for，其实可以控制j < i / 2
        for(int j = 1; j <= i -1;j++){
            int cc = max(i - j,dp[i - j]) * j;
            ans = cc > ans ? cc : ans;
        }
        dp[i] = ans; 
    }
    return dp[n];
}
```
## 96 不同的二叉搜索树

弄清楚DP公式就是神中神，这题第一次看还觉得，卧槽，这怎么整

实际跟树，节点，没任何关系，就是一个排列组合问题

```CPP
 DP[i] = SUM(j = 0,1,2,...,n-1){DP[j] * DP[i - j - 1]} // DP[0] = 1;
```

有以下代码, 0ms 100%
```CPP
int numTrees(int n) {
    int cn = n >= 3 ? n : 3;
    vector<int> dp(cn + 1,0);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for(int i = 3;i <= cn; i++){
        int count = 0;
        for(int j = 0; j <= i - 1;j++){
            count += dp[j] * dp[i - j - 1];
        }
        dp[i] = count;
    }
    return dp[n];
}
```
## 416 分割等和子集
看不出DP原理，直接回溯，超时 O(2^n)
```CPP
bool canPartition(vector<int>& nums) {
    return backTracking(nums,0);
}
bool backTracking(vector<int>& nums, int idx){
    if(idx == nums.size()){
        if(left == right){
            return true;
        }
        return false;
    }
    left += nums[idx];
    if(backTracking(nums,idx+1)){
        return true;
    }
    left -= nums[idx];
    right += nums[idx];
    if(backTracking(nums,idx+1)){
        return true;
    }
    right -= nums[idx];
    return false;
}
```
将题目视为容量大小为count / 2的背包，认为每个数字的重量为nums[i]，价值为nums[i]，那么就是一个0-1背包问题
在这里使用了滚动数组，把原始DP的二维dp数组压缩成了一维。经典好题要背住。
```CPP
bool canPartition(vector<int>& nums) {
    int count = 0;
    for(auto item : nums)count += item;
    if(count % 2 == 1) return false;
    int maxRange = count / 2;
    vector<int> dp(maxRange+ 1,0);
    for(int i = 0;i < nums.size(); i++){
        for(int j = maxRange; j >= nums[i]; j--){
            dp[j] =  max(dp[j], dp[j - nums[i]] + nums[i]);
        }
    }
    if(dp[maxRange] == maxRange) return true;
    return false;
}
```

## 1049 最后一块石头的重量II

这题我做时候，除了回溯，没想到别的办法，其实也是一个背包问题，但我确实没看出来

跟416一样，找一堆数字，使其尽可能逼近count / 2，最后输出count - 2 * dp[maxRange]即可

```CPP
int lastStoneWeightII(vector<int>& stones) {
    int count = 0;
    for(auto item : stones)count += item;
    int maxRange;
    maxRange = count / 2;
    vector<int> dp(maxRange + 1,0);
    for(int i = 0; i < stones.size(); i++){
        for(int j = maxRange; j >= stones[i]; j--){
            dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
        }
    }
    return count - 2 * dp[maxRange];
}
```

## 494 目标和

方法1：回溯，2040ms，5.01%

方法2：DP，没做出来，抄的，背包DP解决组合问题的模板，要记住这个递推公式

```CPP
int findTargetSumWays(vector<int>& nums, int target) {
    int ans = 0;
    for(auto item : nums) ans += item;
    if((ans - target) % 2 == 1) return 0;
    int neg = (ans - target) / 2;
    if(abs(target) > ans) return 0;
    vector<int> dp(neg + 1,0);
    dp[0] = 1;
    for(int i = 0; i < nums.size();i++){
        for(int j = neg; j >= nums[i]; j--){
            dp[j] += dp[j - nums[i]];
        }
    }
    return dp[neg];
}
```

## 474 一和零

方法1：回溯，没有意义

方法2：DP，背包问题，两个维度的背包

```CPP
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1,vector<int>(n+1,0));
    for(string str : strs){
        int oneNum = 0;
        int zeroNum = 0;
        for(char c : str){
            if(c == '0') zeroNum++;
            else oneNum++;
        }
        for(int i  = m; i >= zeroNum; i--){
            for(int j = n; j >= oneNum; j--){
                dp[i][j] = max(dp[i][j],dp[i - zeroNum][j - oneNum] + 1);
            }
        }
    }
    return dp[m][n];
}
```
## 完全背包理论基础

完全背包与0-1背包问题不同，每种物品可以选择无限件。

## 518 零钱兑换II

方法1：回溯，超时
```CPP
int change(int amount, vector<int>& coins) {
    backTracking(0,0,amount,coins);
    return res;
}
void backTracking(int idx,int count,int amount,vector<int>& coins){
    if(count == amount){
        res++;
        return;
    }
    if(count > amount){
        return;
    }
    for(int i = idx;i < coins.size();i++){
        backTracking(i,count + coins[i],amount,coins);
    }
}
```
方法2：DP，完全背包问题，跟474一样，只不过这里是求方案数，474是求最大价值
要理解这个 += 的作用，理解这个一维DP数组背包是怎么计算出结果的

```CPP
int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1,0);
    dp[0] = 1;
    for(int i = 0; i < coins.size(); i++){
        for(int j = coins[i]; j <= amount; j++ ){
            dp[j] += dp[j - coins[i]];
        }
    }
    return dp[amount];
}
```