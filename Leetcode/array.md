## 2962统计最大元素出现至少k次的子数组

滑动窗口

这个题一开始思路想错了，搞好多个for回溯找到所有子数组，又是记忆化搜索，又是dp的，实际只是一道滑动窗口题目

同时在使用right指针时候出现错误，这题用for(auto)就够了，我们不关心right具体值

```CPP
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        int curCount = 0;
        int maxe = *max_element(nums.begin(),nums.end());
        int left = 0;
        for(auto item : nums){
            curCount += item == maxe;
            while(curCount == k){
                curCount -= nums[left] == maxe;
                left++;
            }
            ans += left;
        }
        return ans;
    }
};

```

## 704二分查找

没什么好说的，就是个简单的二分查找

**递归**
```CPP
class Solution {
public:
    int search(vector<int>& nums, int target) {
        return findHelper(nums,target,0,nums.size() -1 );
    }

    int findHelper(vector<int>& nums, int target,int left,int right){
        if(right - 1 <= left){
            if(nums[left] == target) return left;
            if(nums[right] == target) return right;
            return -1;
        }
        int middle = left + (right - left ) /2;
        if(nums[middle] == target) return middle;
        if(nums[middle] < target)return findHelper(nums,target,middle,right);
        if(nums[middle] > target) return findHelper(nums,target,left,middle);
        return -1;
    }
};
// 没什么呃好说的，就是个简单的递归，但递归并不总是好方法
```
**循环**
```CPP
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1; // 定义target在左闭右闭的区间里，[left, right]
        while (left <= right) { // 当left==right，区间[left, right]依然有效，所以用 <=
            int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
            if (nums[middle] > target) {
                right = middle - 1; // target 在左区间，所以[left, middle - 1]
            } else if (nums[middle] < target) {
                left = middle + 1; // target 在右区间，所以[middle + 1, right]
            } else { // nums[middle] == target
                return middle; // 数组中找到目标值，直接返回下标
            }
        }
        // 未找到目标值
        return -1;
    }
};

// 怎么循环比递归还慢？？？
```


## 35搜索插入位置

跟二分查找差不多，但是在输出结果时候有一点点区别，注意此处的结果输出时候的if
middle = left 还比middle小直接输出left,middle= right还比right大就输出right+1;

```CPP
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() -1;
        while(left <= right){
            int middle = left  + (right - left) / 2;
            if(nums[middle] > target){
                if(left == middle)return left;
                right = middle - 1;
            }else if(nums[middle] < target){
                if(middle == right)return right + 1;
                left = middle + 1;  
            }
            if(nums[middle] == target){
                return middle;
            }
        }
        return -1;
    }
};
```

## 34在排序数组中查找元素的第一个和最后一个位置

以二分查找的思路做，但陷入了超时的误区，问题在于
```CPP
    if(nums[middle] == target){
        ans = middle;
    }
    //再找到目标点后ans = middle后，需要设置right = left - 1退出循环，不然就卡在这重复给ans赋值
```
最终代码如下
```CPP
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() -1;
        int ans = -1;
        while(left <= right){
            int middle  = left + (right - left) / 2;
            if(nums[middle] < target)left = middle + 1;
            if(nums[middle] > target)right = middle - 1;
            if(nums[middle] == target){
                ans = middle;
                right = left -1;
            }
        }
        if (ans == -1)return vector<int>(2,-1);
        left = ans;
        for(int i = ans;i >= 0; i--){
            if(nums[i] == nums[ans]) {left = i;}
            else {break;}
        }
        right = ans; 
        for(int i = ans;i < nums.size(); i++){
            if(nums[i] == nums[ans]) {right = i;}
            else {break;}
        }
        return {left,right};
    }
};
// 最后用for循环往左右两边查找，时间复杂度可以认为是O(logn) + O(l) l为target出现次数
// 总而言之这题做法很多，就先这样
```

## 27 移除元素


我的做法——复杂的双指针逻辑，debug半天才通过，这还是个简单题

```CPP
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(nums.size() == 0)return 0;
        if(nums.size() == 1 and  nums[0] == val) return 0;
        if(nums.size() == 1 and nums[0] != val) return 1;
        int left  = 0;
        int right = 1;
        while(left < nums.size() and right < nums.size()){
            if(nums[left] == val and nums[right] == val){right++;continue;}
            if(nums[left] == val and nums[right] != val){
                swap(nums[left],nums[right]);
                right++;
                left++;
                continue;
            }
            if(nums[left] != val and nums[right] == val){left++;continue;}
            if(nums[left] != val and nums[right] != val){
                left++;
                right++;
                continue;
            }
        }
        for(int i = nums.size() -1 ;i >= 0;i--){
            if(nums[i] == val){
                nums.pop_back();
            }else{
                break;
            }
        }
        return nums.size();
    }
};
```

答案的双指针

```CPP
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int left = 0;
        for (int right = 0; right < n; right++) {
            if (nums[right] != val) {
                nums[left] = nums[right];
                left++;
            }
        }
        return left;
    }
};
// 由于len(合法数字) <= index，所以直接这样使用left指针赋值没有任何的问题。最后直接返回left
// 根本不需要像上文我的做法一样写复杂的判断逻辑
```

关键点：宁愿覆盖，也不删除，由于连续地址空间，删除的时间开销特别的大，所以优先覆盖。


## 26 删除有序数组中的重复项

经典的双指针，区别就是加了一个pivor在记录当前不重复的最后一个元素

还有个编码小技巧就是尽量使得循环规律可以包括第0 个元素，这样就能避免单独处理第0个元素的情况

```CPP
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int left = 1;
        int pivor = *nums.begin();
        for(int right = 1;right < nums.size(); right++){
             if(nums[right] != pivor){
                nums[left] = nums[right];
                left++;
                pivor = nums[right];
             }
        }
        return left;
    }
};
```

## 283 移动零

标准的双指针然后置0

```CPP
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0;
        for(int right = 0;right <nums.size();right++){
            if(nums[right] != 0 ){
                nums[left] = nums[right];
                left++;
            }
        }
        for(int i = left;i < nums.size();i++){
            nums[i] = 0;
        }
        
    }
};
```

## 844 比较含退格的字符串

方法1栈，

```CPP
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char> ss;
        stack<char> st;
        for(auto item : s){
            if(item != '#'){
                ss.push(item);

            }else{
                if(!ss.empty())ss.pop();
            }
        }
        for(auto item : t){
            if(item != '#'){
                st.push(item);

            }else{
                if(!st.empty())st.pop();
            }
        }
        if(ss == st) return true;
        return false;
    }
};

```


方法2双指针，倒序抵消就做出来了，正序也可以，下标变化复杂一点点

俩方法时间复杂度一样，空间复杂度双指针小
```CPP
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.length() - 1, j = T.length() - 1;
        int skipS = 0, skipT = 0;

        while (i >= 0 || j >= 0) {
            while (i >= 0) {
                if (S[i] == '#') {
                    skipS++, i--;
                } else if (skipS > 0) {
                    skipS--, i--;
                } else {
                    break;
                }
            }
            while (j >= 0) {
                if (T[j] == '#') {
                    skipT++, j--;
                } else if (skipT > 0) {
                    skipT--, j--;
                } else {
                    break;
                }
            }
            if (i >= 0 && j >= 0) {
                if (S[i] != T[j]) {
                    return false;
                }
            } else {
                if (i >= 0 || j >= 0) {
                    return false;
                }
            }
            i--, j--;
        }
        return true;
    }
};
// 从官网上抄的，实现起来很复杂，没必要
```

## 977 有序数组的平方

第一反应是排序，然后平方，但是这样时间复杂度就是O(nlogn)

双指针

```CPP
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int i  = 0;
        int j = nums.size() - 1;
        vector<int> res;
        while(i<= j){
            int ni = abs(nums[i]);
            int nj = abs(nums[j]);
            if(ni >= nj){
                res.push_back(ni * ni);
                i++;
                continue;
            }
            if(ni < nj){
                res.push_back(nj * nj);
                j--;
                continue;
            }
        }
        std::reverse(res.begin(),res.end());
        return res;
    }
};
// O(n) 
```

桶排序好像也可以实现O(n)，一会再做

## 209长度最小的子数组

滑动窗口

```CPP
// 很简单的一个滑动窗口，但是在实现的时候，外循环指针没有弄清晰，导致卡了一会
// 要多复习这个滑动窗口的双指针变化，争取不卡住
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int curTotal = 0;
        int left = 0;
        int right = 0;
        int minNum = nums.size() + 1;
        for(int i = 0;i < nums.size();i++){
            curTotal += nums[i];
            while(curTotal>= target){
                minNum = min(minNum,i - left + 1);
                curTotal -= nums[left];
                left++;
            }
            
        }
        if(minNum == nums.size() + 1 )return 0;
        return minNum;
    }
};
```

## 904水果成篮
翻译题目：
只有两种不同数字的子数组的长度最大值

滑动窗口是可以做的，但我又写了个异常复杂的逻辑，各种控制变量乱飞，最后显而易见就是模型奇妙的解答错误。

官方题解思路跟我写的是一致的，就是用一个Map记录水果种类及出现个数，出现了新种类直接动左指针不断丢水果，直到把出map的水果全部丢完。

```CPP
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        unordered_map<int,int> cnt;
        int left = 0;
        int ans = 0;
        for(int right = 0; right < n; right++){
            ++cnt[fruits[right]];
            while(cnt.size()>2){
                auto it = cnt.find(fruits[left]);
                --it->second;
                if(it->second == 0){
                    cnt.erase(it);
                }
                ++left;
            }
            ans = max(ans,right - left + 1);
        }
        return ans;
    }
};
// 终于理解了，他不是先得知要删除的水果，
// 而是直接从左往右删除，直到某一种水果为0，相当于对left的每一次移动，都重新查map，
//删去对应的水果种类，在left与right相遇之前，总会有一种水果先删完，那剩下的水果肯定在left右边。
// 有以结果为导向的这种感觉，学习了！
```

## 239 滑动窗口最大值

滑动窗口最大值的典型做法，使用deque维持一个递减队列，同时实际存储的是下标
比我设想的，封装单调队列pop push的方法更简洁

```CPP
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> q;
        for(int i = 0; i < k; ++i){
            while(!q.empty() && nums[i] >= nums[q.back()]){
                q.pop_back();
            }
            q.push_back(i);
        }
        vector<int> ans = {nums[q.front()]};
        for(int i = k; i < n; ++i){
            while(!q.empty() && nums[i] >= nums[q.back()]){
                q.pop_back();
            }
            q.push_back(i);
            while(q.front() <= i - k){
                q.pop_front();
            }
            ans.push_back(nums[q.front()]);
        }
        return ans;


    }
};
```

## 347 前K个高频元素
第一眼  map排序？ O(n) + O(slogs)
简单题目在这搞了半天，归根结底是对于C++的map vector等容器掌握不熟练
首先一是自定义排序，二是map只能遍历，不能排序，排序需要先转换为vector

```CPP
class Solution {
private:
    static bool com(pair<int,int> p1,pair<int,int> p2){
        return p1.second > p2.second;
    }
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> cmap;
        for(auto item : nums){
            cmap[item]++;
        }
        vector<pair<int, int>> vec(cmap.begin(), cmap.end());
        sort(vec.begin(),vec.end(),com);
        vector<int> res;
        int count = 0;
        for(auto item : vec ){
            if(count < k){
                res.push_back(item.first);
                count++;
            }else{
                break;
            }
        }
        return res;
    }
};
```