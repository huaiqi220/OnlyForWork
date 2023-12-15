## 69 x的平方根

 这题有换底的数学方法，从1-x里面遍历是很愚蠢的做法
但是就当是练习二分查找，做的试试

```CPP
class Solution {
public:
    int mySqrt(int x) {
        if(x == 0 )return 0;
        if(x == 1) return 1;
        if(x == 2)return 1;
        int left = 1;
        int right = x / 2;
        while(left <= right){
            int middle = left + (right - left) / 2;
            if((long long)middle * middle > x){
                if(middle == left) return middle - 1;
                right = middle - 1;
            } 
            if((long long)middle * middle < x){
                if(middle == right)return right;
                left = middle + 1;
            }  
            if((long long)middle * middle == x){
                return middle;
            }           
        }
        return -1;
    }
};
// 没卡在二分查找上，卡在了很奇怪的longlong 相乘上
// (long long)middle * middle与 (long long)(middle * middle)是不一样的，
//前者是先把middle转成longlong再相乘，后者是先相乘再转成longlong，后者会溢出 
```

## 367有效的完全平方数

```CPP
class Solution {
public:
    bool isPerfectSquare(int x) {
        if(x == 0 )return true;
        if(x == 1) return true;
        if(x == 2)return false;
        int left = 1;
        int right = x / 2;
        while(left <= right){
            int middle = left + (right - left) / 2;
            if((long long)middle * middle > x){
                right = middle - 1;
            } 
            if((long long)middle * middle < x){
                left = middle + 1;
            }  
            if((long long)middle * middle == x){
                return true;
            }           
        }
        return false;
    }
};
// 就是一个十分标准的二分查找，没任何说法
```