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