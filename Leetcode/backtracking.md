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
