## 3无重复字符的最长子串

思路很简单就想到了，但实现起来各种问题，又是怎么从map中删除元素，又是怎么挪动指针，实现的很复杂，结果还错了。

好好学习一下别人怎么实现的代码

```CPP
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        int n = s.size();
        int start = 0;
        int end = 0;
        while(end < n){
            for(int i = start; i < end;i++){
                if(s[i] == s[end]){
                    start = i + 1;
                    break;
                }
            }
            result = max(result,end - start + 1);
            end++;
        }
        return result;
    }
};
```

## 483找到字符串中的所有字母异位词语

**滑动窗口**

C++ str.substr(start,len)函数是截的开始下标和长度，不是结束下标，
如果根据下标截取就是str.substr(start,end-start+1)

如果以窗口p.size()向右平移排序比较，就是超时。要换种思路

```CPP
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int i = 0;
        int j = p.size() -1;
        vector<int> res;
        while(j < s.size()){
            if(isSame(s,p,i,j))res.push_back(i);
            i++;
            j++;
        }
        return res;
    }
    bool isSame(string s, string p,int i,int j){
        string cop = s.substr(i,j - i + 1);
        sort(cop.begin(),cop.end());
        sort(p.begin(),p.end());
        if(cop == p) return true;
        return false;
    }
};
// 超时

```

## 76 最小覆盖子串

？？
困难滑动窗口，改天做


## 59 螺旋矩阵II && LCR 146 螺旋遍历二维数组

没什么思考上的难度，就是一个纯模拟的题目，搞了半个小时

利用引用、level、n这几个变量来逐层控制填充，每一层只填一个圈。

```CPP
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int start = 1;
        int level = 0;
        vector<vector<int>> res(n,vector<int>(n,0));
        while(start <= n * n){
            fillthematrix(start,res,level++,n);
        }
        return res;  
    }
    void fillthematrix(int& start,vector<vector<int>>& res,int level, int n){
        if(n -1 -level == level){
            res[level][level] = start;
            start++;
            return;
        }
        if(n - 1 -level < level)return;
        for(int i = level; i <= n-2-level;i++){
            res[level][i] = start;
            start++;
        }
        for(int j = level; j <= n-2-level;j++){
            res[j][n-1-level] = start;
            start++;
        }
        for(int k = n - 1- level;k > level;k--){
            res[n-1-level][k] = start;
            start++;
        }
        for(int i = n - 1- level;i > level;i--){
            res[i][level] = start;
            start++;
        }
        return;
    }
};
```

## 334 反转字符串

```CPP
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0;
        int j = s.size() -1;
        while(i <= j){
            swap(s[i],s[j]);
            i++;
            j--;
        }
    }
};
```

## 151 翻转字符串里的单词

简答想了下可以用stack存，但是答案说有原地算法，明天再做，出差去了




## 1047 删除字符串中的所有相邻重复项

```CPP
// 这是一段并不合适的方法，1.方法执行特别的慢，2. 代码中存在多处容易执行出错的地方
// 如while循环中的复杂判断，最后st.push前的索引检查等，这个方法并不合适
class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        for(int i = 0; i < s.size(); i++){
            if(st.empty()){
                st.push(s[i]);
                continue;
            }
            while(!st.empty() && i < s.size() && st.top() == s[i]){
                st.pop();
                i++;
            }
            // 不加这一行判断，在处理aaaaaa这种用例时会将s外的未知内存中的值加入到st中
            if(i < s.size()){
                st.push(s[i]);
            }
        }
        string res = "";
        while(!st.empty()){
            res = st.top() + res;
            st.pop();
        }
        return res;
    }
};
```

改进方法——
string STL也提供了push_back，pop_back，back等函数

```CPP
class Solution {
public:
    string removeDuplicates(string s) {
        string stk;
        for(char c : s){
            if(!stk.empty() and stk.back() == c){
                stk.pop_back();
            }else{
                stk.push_back(c);
            }
        }
        return stk;
    }
};
```


## 459 重复的子字符串
我的方法——类似于转轮，每次转一格是不是跟原字符串匹配，如果这个字符串由“abac”重复多次生成。那我最多旋转四轮就能判断出结果

问题是string的尾插入头删除，或者尾删除头插入比较耗时。方法本身复杂度也较高，方法直接超时。

正确方法：KMP

```CPP

```