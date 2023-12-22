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

