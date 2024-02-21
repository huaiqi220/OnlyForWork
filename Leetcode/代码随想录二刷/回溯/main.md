## 77 组合
```CPP
// 做了好一会，太慢了
// i++ 与 i + 1注意区别，别乱写
private:
    vector<vector<int>> res;
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> temp;
        backTracking(1,n,k,temp);
        return res;
    }
    void backTracking(int idx, int n, int k, vector<int>& temp){
        if(idx > n) return;
        for(int i = idx; i <=n; i++){
            temp.push_back(i);
            if(temp.size() == k){
                res.push_back(temp);
            }else{
                backTracking(i + 1, n, k, temp);
            }
            temp.pop_back();
        }
    }
```

## 216 组合总和 III
```CPP
// 没掌握好，在边界出循环地方始终犹豫怎么写
private:
    vector<vector<int>> res;
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> temp_dp;
        backTracking(1,0,temp_dp,n,k);
        return res;
    }
    void backTracking(int idx, int temp, vector<int>& temp_dp, int n, int k){
        if(temp_dp.size() == k){
            if(temp == n){
                res.push_back(temp_dp);
            }
            return;
        }
        for(int i = idx; i <= 9; i++){
            temp_dp.push_back(i);
            backTracking(i + 1, temp + i, temp_dp, n, k);
            temp_dp.pop_back();
        }
    }
```
## 17 电话号码的字母组合
- char m[][4] = ........ m作为参数传递的时候，直接写m就行了，不需要写m[][4]
- for auto item : m[][4]的时候，auto item dp的时候，会输出dp的结束空字符
  所以代码里应该使item >= 'a' && item <= 'z'的时候再继续逻辑
这题最合适的方法，vector<string> res = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
```CPP
//vector<string> res = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    vector<string> letterCombinations(string digits) {
        vector<string> sel = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string> res;
        if(digits.size() == 0) return res;
        vector<char> temp;
        backTracking(0,digits,temp,res,sel);
        return res;
    }
    void backTracking(int idx, string digits, vector<char> temp, vector<string>& res, vector<string> sel){
        if(idx == digits.size()){
            res.push_back(string(temp.begin(),temp.end()));
            return;
        }
        int num = digits[idx] - '0';
        for(auto item : sel[num]){
            temp.push_back(item);
            backTracking(idx+1,digits,temp,res,sel);
            temp.pop_back();
        }
    }
```

## 39 组合总和
```CPP
// 做了好一会，应该秒了这个题
private:
    vector<vector<int>> res;    
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        vector<int> temp;
        backTracking(0,candidates,temp,target,0);
        return res;
    }
    void backTracking(int idx, vector<int>& candidates, vector<int>& temp, int target, int curSum){
        if(idx >= candidates.size()){
            if(curSum == target){
                res.push_back(temp);
            }
            return;
        }
        if(curSum > target)return;

        temp.push_back(candidates[idx]);
        curSum += candidates[idx];
        backTracking(idx, candidates, temp, target, curSum);
        curSum -= candidates[idx];
        temp.pop_back();
        backTracking(idx + 1,candidates, temp,target,curSum);
    }
```

## 40 组合总和 II
剪枝没搞明白，要花一点时间重搞

## 131 分割回文串
```CPP
// 思路很经典，但我感觉涉及重复计算， 用DP或者记忆化可以更快
private:
    vector<vector<string>> res;
    vector<string> temp;
public:
    vector<vector<string>> partition(string s) {
        backTracking(s,0);
        return res;
    }
    bool isValid(string s, int start, int end){
        while(start <= end){
            if(s[start] == s[end]){
                start++; end--;
            }else{
                return false;
            }
        }
        return true;
    }
    void backTracking(string s, int idx){
        if(idx == s.size()){
            res.push_back(temp);
            return;
        }
        for(int i = idx; i < s.size(); i++){
            if(isValid(s,idx,i)){
                temp.push_back(s.substr(idx,i - idx + 1));
                backTracking(s,i + 1);
                temp.pop_back();
            }
        }
    }
```
