## 704 二分查找
秒
```CPP
int search(vector<int>& nums, int target) {
    int oleft = 0;
    int oright = nums.size() - 1;
    while(oleft <= oright){
        int middle = (oleft + oright) / 2;
        if(nums[middle] == target) return middle;
        if(nums[middle] > target){
            oright = middle - 1;
        }else{
            oleft = middle + 1;
        }
    }
    return -1;
}
```

## 27 移除元素
秒
```CPP
// 方法不是特别好，改变了元素顺序
int removeElement(vector<int>& nums, int val) {
    int moveptr = nums.size() - 1;
    int endptr = nums.size() -1;
    while(moveptr >= 0){
        if(nums[moveptr] == val and moveptr == endptr){
            endptr--;
            moveptr--;
            continue;
        }
        if(nums[moveptr] == val and moveptr != endptr){
            swap(nums[moveptr],nums[endptr]);
            endptr--;
            moveptr--;
            continue;
        }
        if(nums[moveptr] != val){
            moveptr--;
            continue;
        }
    }
    return endptr + 1;
}
```
这是一种巧妙地不用打乱顺序的方法，双指针，由于题目特殊，可以直接覆盖
不用swap
```CPP
int removeElement(vector<int>& nums, int val) {
    int moveptr = 0;
    int endptr = 0;
    while(moveptr < nums.size()){
        if(nums[moveptr] != val){
            nums[endptr] = nums[moveptr];
            moveptr++;
            endptr++;
        }else{
            moveptr++;
        }
    }
    return endptr;
}
```

## 977 有序数组的平方
秒了，sort
不用sort双指针方法
```CPP
vector<int> sortedSquares(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    deque<int> que;
    while(left <= right){
        if(abs(nums[left]) <= abs(nums[right])){
            que.push_front(nums[right] * nums[right]);
            right--;
        }else{
            que.push_front(nums[left] * nums[left]);
            left++;                
        }
    }
    vector<int> res(que.begin(),que.end());
    return res;
}
```

## 209 长度最小的子数组
秒了，很简单一个题，不知道怎么用while循环就不通
```CPP
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0;
    int right = 0;
    int count = 0;
    int minres = INT_MAX;
    for(;right < nums.size(); right++){
        count += nums[right];
        while(count >= target){
            minres = min(minres, right - left + 1);
            count -= nums[left];
            left++;
        }
    }
    return minres == INT_MAX ? 0 : minres;
}
```

## 59 螺旋矩阵II
卡了一会，主要卡在边界条件部分
```CPP
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> result(n,vector<int>(n,0));
    int start = 1;
    int level = 0;
    while(start <= n * n){
        fillByLevel(result,level,n,start);
        level++;
    }
    return result;
}

void fillByLevel(vector<vector<int>>& result,int level, int n, int& start){
    int end = n - level - 1;
    if(end == level){
        result[level][level] = start;
        start++;
        return;
    }
    if(end < level)return;
    for(int i = level; i < end;i++){
        result[level][i] = start;
        start++;
    }
    for(int i = level; i < end; i++ ){
        result[i][end] = start;
        start++;
    }
    for(int i = end; i > level; i--){
        result[end][i] = start;
        start++;
    }
    for(int i = end; i > level; i--){
        result[i][level] = start;
        start++;
    }
}
```

## 54 螺旋矩阵
写了一个遍历方法，但在处理结束部分时候比较复杂，我看看    
```CPP
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    vector<int> res;
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = n - 1, top = 0, bottom = m - 1;
    while (left <= right && top <= bottom) {
        for (int i = left; i <= right; i++) res.push_back(matrix[top][i]); // Traverse right
        top++;
        for (int i = top; i <= bottom; i++) res.push_back(matrix[i][right]); // Traverse down
        right--;
        if (top <= bottom) { // Check to avoid double counting in a single row
            for (int i = right; i >= left; i--) res.push_back(matrix[bottom][i]); // Traverse left
            bottom--;
        }
        if (left <= right) { // Check to avoid double counting in a single column
            for (int i = bottom; i >= top; i--) res.push_back(matrix[i][left]); // Traverse up
            left++;
        }
    }
    return res;
}
// 写法跟我的缺1遍历有一点点不一样，可以学习一下
```