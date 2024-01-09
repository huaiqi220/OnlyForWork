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

## 377 组合总数

跟零钱兑换的区别就是交换了循环的顺序
这一题还涉及到剪枝，不然有一个用例会溢出
```CPP
int combinationSum4(vector<int>& nums, int target) {
    vector<long> dp(target + 1,0);
    dp[0] = 1;
    for(int i = 0; i <= target; i++){
        for(int j = 0; j < nums.size(); j ++){
            if(i - nums[j] >= 0 and dp[i - nums[j]] < INT_MAX - dp[i]) dp[i] += dp[i - nums[j]];
        }
    }
    return int(dp[target]);
}
```

## 322 零钱兑换
DP
当排列for写外面，当组合for写里面对这题没影响
```CPP
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for(int i = 0; i < coins.size(); i++){
        for(int j = coins[i]; j <= amount; j++){
            dp[j] = min(dp[j],dp[j - coins[i]] + 1);
        }
    }
    int res = dp[amount] > amount ? -1  : dp[amount];
    return res;
}
```

## 279 完全平方数

题目都没怎么读，跟上题一样的，只不过这次的coins是从1到sqrt(n)
```CPP
int numSquares(int n) {
    vector<int> dp(n + 1,n + 1);
    dp[0] = 0;
    int max = sqrt(n) + 1;
    for(int i = 1; i <= max; i++)
    {
        for(int j = i; j <= n; j++){
            if(j - i * i >= 0) dp[j] = min(dp[j],dp[j - i * i] + 1);
        }
    }
    int res = dp[n] > n ? 0 : dp[n];
    return res;
}
```
## 139 单词拆分

想到了用DP，但思路感觉也是比较正确，但是因为写的比较复杂出现了空指针

不调了，直接看标答

```CPP
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> wordset(wordDict.begin(),wordDict.end());
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;
    for(int i = 1; i <= s.size(); i++){
        for(int j = 0; j < i; j++){
            string word = s.substr(j, i - j);
            if(wordset.find(word) != wordset.end() && dp[j]){
                dp[i] = true;
            }
        }
    }
    return dp[s.size()];
}
// 写法比较高明，不像我自己写字符串匹配算法，其实substr结合unordered_set一样能实现匹配效果，速度还快
```

## 198 打家劫舍

这题我总喜欢拿一个状态变量status来记录会不会出现dp[i - 1] + nums[i]的情况
但实际上递推公式已经帮助避免了这个情况
```CPP
int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    vector<int> dp(nums.size());
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < nums.size(); i++) {
        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
    }
    return dp[nums.size() - 1];
}
```

## 213 打家劫舍II

这题大方针就是针对头节点选不选进行，讨论
我使用了status表示头节点选了没有，但是遇到0，1元素相等的时候，到底设为true或者false没想明白，
我的想法是，如果最后一个节点可以选，但我又不知道dp[i - 2]这个结果里面包不包含第一个节点，总而言之就是分类讨论并不清晰
代码随想录搞了个巧妙地分类

- 考虑头尾都不选
- 考虑只选头不选尾
- 考虑只选尾不选头

然后从robRange()直接限制选择的范围

```CPP
int rob(vector<int>& nums) {
    if(nums.size() == 1) return nums[0];
    if(nums.size() == 2) return max(nums[0],nums[1]);
    vector<int> dp(nums.size(),0);
    /** 情况23包含情况1 */
    int res1 = robRange(nums,0,nums.size() - 2);
    int res2 = robRange(nums,1,nums.size() - 1);
    return max(res1,res2);
}
int robRange(vector<int>& nums,int start,int end){
    if (end == start) return nums[start];
    vector<int> dp(nums.size());
    dp[start] = nums[start];
    dp[start + 1] = max(nums[start], nums[start + 1]);
    for (int i = start + 2; i <= end; i++) {
        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
    }
    return dp[end];
}
```

## 337 打家劫舍III


## 121 买卖股票最佳时机 && 122 买卖股票最佳时机 II
做了很多遍，依然不会
```CPP
/** 贪心 */
int maxProfit(vector<int>& prices) {
    int low = INT_MAX;
    int result = 0;
    for(int i = 0; i < prices.size(); i++){
        low = min(low, prices[i]);
        result = max(result,prices[i] - low);
    }
    return result;
}
```

这题做了这么多遍，以前都没认真看过它的递推公式，刷题要专心啊
```CPP
/** vector size (n,2)，分别记录当天持有股票，不持有股票时候的现金数 */
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(),vector<int>(2,0));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for(int i = 1; i < prices.size(); i++){
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = max(-prices[i],dp[i - 1][1]);
    }
    return dp[prices.size() -1 ][0];
}
```

122 跟121的唯一区别，就是dp的时候,dp[i][1]从dp[i-1][0] - prices[i]，多了一个从0到1的双向状态转换。
当然，既然能多次买卖，这题有更简单的解法。

## 123 买卖股票最佳时机 III && 188 买卖股票的最佳时机IV

感觉思路跟我的差不多，我觉得这题需要用回溯加DP，但实际根据这个答案来说，k数字比较小的时候可以直接枚举
一天一共就有五个状态，
- 没有操作 （其实我们也可以不设置这个状态）
- 第一次持有股票
- 第一次不持有股票
- 第二次持有股票
- 第二次不持有股票
dp[i][j]中 i表示第i天，j为 [0 - 4] 五个状态，dp[i][j]表示第i天状态j所剩最大现金。
k == 2的时候，就是申请了一个dp[prices.size()][2k + 1]
```CPP
/** 再改改可以改成一个适用于所有K的算法 */
int maxProfit(vector<int>& prices) {
    if(prices.size() == 0)return 0;
    int k = 2;
    vector <vector<int>> dp(prices.size(), vector<int>(2 * k + 1, 0));
    dp[0][1] = -prices[0];
    dp[0][3] = -prices[0];
    for (int i = 1; i < prices.size(); i++) {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
        dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
        dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
    }
    vector<int> last = dp[prices.size() - 1];
    int res = *max_element(last.begin(),last.end());
    return res;
}
```

```CPP
/** 适用于k */
int maxProfit(int k, vector<int>& prices) {
    if(prices.size() == 0)return 0;
    vector <vector<int>> dp(prices.size(), vector<int>(2 * k + 1, 0));
    // init 
    int i = 1;
    while(i < 2 * k + 1){
        dp[0][i] = -prices[0];
        i += 2;
    }
    int mark = -1;
    for (int i = 1; i < prices.size(); i++) {
        dp[i][0] = dp[i - 1][0];
        for(int j = 1; j < 2* k + 1; j++){
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + (prices[i] * mark));
            mark *= -1;
        }
    }
    vector<int> last = dp[prices.size() - 1];
    int res = *max_element(last.begin(),last.end());
    return res;
}
```

## 309 最佳买卖股票时机含冷冻期
不会做，看了题解
似乎——股票问题，不管是只能交易几手，或者是冷静期，似乎都是状态上的转换
可以通过图来建模股票问题的状态转换，根据状态转换路径来DP
买入状态------->今天卖出------->冷冻------->卖出状态（未持有）
                                |-------->买入状态

```CPP
/** 看答案做的，多多复习啊 */
int maxProfit(vector<int>& prices) {
    vector<vector<int>> dp(prices.size(),vector<int>(4,0));
    dp[0][0] = -prices[0];
    for(int i = 1; i < prices.size(); i++)
    {
        // 0 买入 1 卖出 2 冷冻 3 未持有
        dp[i][0] = max(dp[i -1][0],max(dp[i - 1][2] - prices[i],dp[i - 1][3] - prices[i]));
        dp[i][1] = dp[i - 1][0] + prices[i];
        dp[i][2] = dp[i - 1][1];
        dp[i][3] = max(dp[i - 1][3], dp[i - 1][2]);
    }
    vector<int> last = dp[prices.size() - 1];
    int res = *max_element(last.begin(),last.end());
    return res;      
}
```

## 714 买卖股票的最佳时机含手续费
跟买卖股票2很像，但似乎有个bug，为什么fee放到dp[i][1]里面就不行了？？
输出的比实际高一个fee，我不知道买的时候扣税和买的时候扣税有什么区别，我觉得应该一致吧？

```CPP
int maxProfit(vector<int>& prices, int fee) {
    if(prices.size() == 1) return 0;
    vector<vector<int>> dp(prices.size(), vector<int>(2,0));
    dp[0][1] = -prices[0];
    for(int i = 1 ; i < prices.size(); i++){
        dp[i][1] = max(dp[i - 1][1],dp[i - 1][0] - prices[i]);
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
    }
    return *max_element(dp[prices.size() -1].begin(),dp[prices.size() -1].end());
}
```