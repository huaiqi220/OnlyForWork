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