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


