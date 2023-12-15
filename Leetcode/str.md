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



