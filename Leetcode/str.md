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



