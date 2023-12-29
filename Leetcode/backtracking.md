## 77 组合
标准的回溯模板，也可以把res和temp声明为类的成员变量，这样就不用传递了
```CPP
vector<vector<int>> combine(int n, int k) {
    backTracking(n,k,0);
    return res;
}
void backTracking(int n,int k, int idx){
    if(temp.size() == k){
        res.push_back(temp);
        return;
    }
    for(int i = idx; i < n;i++){
        temp.push_back(i + 1);
        backTracking(n,k,i+ 1);
        temp.pop_back();
    }
}
```

## 78 子集

也是个标准的回溯模板，但是跟77采用了不同的写法，这次我采用DFS策略，决定每个元素是否被放入

```CPP
vector<vector<int>> subsets(vector<int>& nums) {
    backTracking(nums,0);
    return res;
}
void backTracking(vector<int>& nums,int idx){
    if(idx == nums.size()){
        res.push_back(cur);
        return;
    }
    backTracking(nums,idx+1);
    cur.push_back(nums[idx]);
    backTracking(nums,idx+1);
    cur.pop_back();
}
```

## 90 子集II

78代码加上sort以及去重操作同样AC，在这里使用for循环写法重新实现。
```CPP
// 没太理解下面这个写法，先放在这
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex)
    {
        result.push_back(path);
        unordered_set<int> uset;
        for (int i = startIndex; i < nums.size(); i++) 
        {
            if (uset.find(nums[i]) != uset.end()) 
            {
                continue;
            }
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end()); // 去重需要排序
        backtracking(nums, 0);
        return result;
    }
};
```

## 216 组合总数III

count += i + 1;

```CPP
vector<vector<int>> combinationSum3(int k, int n) {
    backTracking(k,n,0);
    return res;
}
void backTracking(int k, int n, int idx){
    if(count == n and temp.size() == k){
        res.push_back(temp);
        return;
    }
    if(count > n or temp.size() > k){
        return;
    }
    for(int i = idx;i < 9;i++){
        // idx在这只是可选择区间开始的下表，for循环中每次添加的数字是i + 1
        // 
        count+= (i + 1);
        temp.push_back(i + 1);
        backTracking(k,n,i+1);
        temp.pop_back();
        count-= (i + 1);
    }
}
```
## 131 分割回文串
补充知识点:
```CPP
// string取子串
s.sub( start, end - start + 1);
```
我一开始的做法，写一个isValid()，写一个backTracking()，时间复杂度不高
```CPP
class Solution {
private:
    vector<vector<string>> res;
public:
    vector<vector<string>> partition(string s) {
        vector<string> temp;
        backTracking(s,0,temp);
        return res;
    }
    void backTracking(string s,int idx,vector<string>& temp){
        if(idx == s.size()){
            res.push_back(temp);
            return;
        }
        for(int i = idx;i < s.size();i++){
            if(isValid(s,idx,i)){
                temp.push_back(s.substr(idx,i - idx + 1));
                backTracking(s,i+1,temp);
                temp.pop_back();
            }
        }
    }
    bool isValid(string s,int start ,int end){
        while(start <= end){
            if(s[start] != s[end])return false;
            start++; end--;
        }
        return true;
    }
};
```
改进方法是，在每次isValid时候会造成重复计算，可以首先DP出所有的回文串，然后再进行回溯，直接用上下索引查表 
```CPP
class Solution {
private:
    vector<vector<int>> f;
    vector<vector<string>> ret;
    vector<string> ans;
    int n;

public:
    void dfs(const string& s, int i) {
        if (i == n) {
            ret.push_back(ans);
            return;
        }
        for (int j = i; j < n; ++j) {
            if (f[i][j]) {
                ans.push_back(s.substr(i, j - i + 1));
                dfs(s, j + 1);
                ans.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        n = s.size();
        f.assign(n, vector<int>(n, true));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];
            }
        }
        dfs(s, 0);
        return ret;
    }
};
```

## 93 复原IP地址
使用的是跟切割回文串差不多的套路，只是改变了isValid的判断条件
```CPP
class Solution {
private:
    vector<string> res;
    vector<string> temp;
public:
    vector<string> restoreIpAddresses(string s) {
        backTracking(s,0,temp);
        return res;
    }
    void backTracking(string s, int idx,vector<string>& temp){
        if(temp.size() == 4 and idx == s.size()){
            string r;
            for(auto item : temp)r += (item + ".");
            r.pop_back();
            res.push_back(r);
            return;
        }
        for(int i = idx; i < s.size(); i++){
            if(isValid(s,idx,i)){
                temp.push_back(s.substr(idx,i - idx + 1));
                backTracking(s,i + 1,temp);
                temp.pop_back();
            }
        }
    }
    bool isValid(string s,int start,int end){
        if(start == end){
            return true;
        }
        if(start < end and s[start] == '0'){
            // 先导0
            return false;
        }
        if(end - start + 1 >3)return false;
        if(start < end ){
            int i = stoi(s.substr(start,end-start + 1));
            if(i >= 0 and i <= 255){
                return true;
            }
            return false;
        }
        return false;
    }
};
```

## 491 递增子序列
原始代码超时，由于不断find，时间复杂度太高。
同时了解到新知识点，map set的key必须是可哈希的，vector<int>不行，因为不可哈希

```CPP
class Solution {
private:
    int curMax = -100;
    vector<vector<int>> res;
    vector<int> temp;
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backTracking(nums,0);
        return res;
    }
    void backTracking(vector<int>& nums,int idx){
        if(idx >= nums.size() ){
            if(temp.size() >= 2 and find(res.begin(),res.end(),temp) == res.end()){
                res.push_back(temp);
            }
            return;
        }
        backTracking(nums,idx+1);
        if(nums[idx] >= curMax){
            int oMax = curMax;
            temp.push_back(nums[idx]);
            curMax = nums[idx];
            backTracking(nums,idx+1);
            temp.pop_back();
            curMax = oMax;
        }
    }
};
```
随想录的优化方法，说实话，目前还是没有掌握回溯的两种写法的区别和联系，遇到一些复杂的剪枝，去重问题就容易出错
还需要多多练习。

这个题类似于子集问题，总之要输出中间结果。取/不取写法的最终temp就包含了中间结果，而for写法中间结果要自己输出，所以开头部分没有return
```CPP
class Solution {
private:
    vector<vector<int>> res;
    vector<int> temp;
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backTracking(nums,0);
        return res;
    }
    void backTracking(vector<int>& nums,int idx){
        if(temp.size() >= 2 ){
            res.push_back(temp);
        }
        unordered_set<int> uset;
        for(int i =idx; i < nums.size();i++){
            if((!temp.empty() && nums[i] < temp.back()) ||
                uset.find(nums[i]) != uset.end()){
                    continue;
                }
                uset.insert(nums[i]);
                temp.push_back(nums[i]);
                backTracking(nums,i + 1);
                temp.pop_back();
        }
    }
};
```


## 46 全排列


这题做出来不难，但怎么处理某个元素已经被选取，这个比较困难，因为排列必然代表无序，我的第一个做法是，选了某个数，就把某个数从vector里直接erase，回溯完回来添加的时候就Insert,这两步操作对于vector来说都是非常费的

```CPP
vector<vector<int>> permute(vector<int>& nums) {
    backTracking(nums);
    return res;
}
void backTracking(vector<int>& nums){
    if(nums.size() == 0){
        res.push_back(temp);
        return;
    }
    for(int i = 0; i < nums.size();i++){
        temp.push_back(nums[i]);
        int copy = nums[i];
        nums.erase(nums.begin() + i);
        backTracking(nums);
        nums.insert(nums.begin() + i,copy);
        temp.pop_back();
    }
}
```
我设想使用list，使用deque，都不好满足在指定位置重新插入元素这个目的，其实只用创建一个记录数组used就行
```CPP
std::vector<std::vector<int>> res;
std::vector<int> temp;
std::vector<bool> used;  // 新增用于标记元素是否已使用的数组
std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    used.resize(nums.size(), false);
    backTracking(nums);
    return res;
}
void backTracking(std::vector<int>& nums) {
    if (temp.size() == nums.size()) {
        res.push_back(temp);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (!used[i]) {
            temp.push_back(nums[i]);
            used[i] = true;
            backTracking(nums);
            temp.pop_back();
            used[i] = false;
        }
    }
}
```

## 47 全排列II
**有重复数字**
直接按46做，最后去重，击败5%

用了一个unordered_map，控制for中不要选取相同数值的数，击败20%,也不是特别快
```CPP
vector<vector<int>> res;
vector<int> temp;
vector<bool> used;
vector<vector<int>> permuteUnique(vector<int>& nums) {
    used = vector<bool>(nums.size(),false);
    backTracking(nums);
    return res;
}
void backTracking(vector<int>& nums){
    if(temp.size() == nums.size()){
        res.push_back(temp);
        return;
    }
    unordered_map<int,int> map;
    for(int i =0;i < nums.size();i++){
        if(!used[i] and map[nums[i]]  == 0){
            map[nums[i]] = 1;
            used[i] = true;
            temp.push_back(nums[i]);
            backTracking(nums);
            temp.pop_back();
            used[i] = false;
        }
    }
}
```
还有一种思路，sort之后，相同的元素一定相邻，不能选择跟前一个元素相同的元素，
因为在排列，所有元素都会被取到的情况下， 111xxxx，先取哪个1其实是一个结果。所以直接剪枝。
```CPP
vector<vector<int>> res;
vector<int> temp;
vector<bool> used;
vector<vector<int>> permuteUnique(vector<int>& nums) {
    used = vector<bool>(nums.size(),false);
    sort(nums.begin(),nums.end());
    backTracking(nums);
    return res;
}
void backTracking(vector<int>& nums){
    if(temp.size() == nums.size()){
        res.push_back(temp);
        return;
    }
    int front = -11;
    for(int i =0;i < nums.size();i++){
        if((!used[i] && front == -11) || (!used[i] && front != nums[i])){
            used[i] = true;
            temp.push_back(nums[i]);
            backTracking(nums);
            temp.pop_back();
            used[i] = false;
            front = nums[i];
        }
    }
}
```

## 332 重新安排行程

题目没读懂、

## 51 N皇后

一遍过，没啥可说的，这题就是辅助函数需要写两个

```CPP
class Solution {
    vector<pair<int,int>> temp;
    vector<vector<string>> printRes;
public:
    vector<vector<string>> solveNQueens(int n) {
        backTracking(n,0);
        return printRes;
    }
    void backTracking(int n,int idx){
        if(idx == n){
            printRes.push_back(getTheStringBox(temp));
        }
        for(int i = 0; i < n;i++){
            if(canPlace(temp,idx,i)){
                temp.push_back(pair<int,int>({idx,i}));
                backTracking(n,idx+1);
                temp.pop_back();
            }
        }
    }
    bool canPlace(vector<pair<int,int>>& temp,int i,int j){
        for(auto item : temp){
            if(item.first == i or item.second == j or (abs(item.first - i) == abs(item.second - j))){
                return false;
            }
        }
        return true;
    }
    vector<string> getTheStringBox(vector<pair<int,int>>& temp){
        int n = temp.size();
        vector<string> table(n,string(n,'.'));
        for(auto item : temp){
            table[item.first][item.second] = 'Q';
        }
        return table;
    }
};
```
