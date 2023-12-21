## 232 用栈实现队列

第一版本代码时间复杂度不高，我在每一次pop或者push操作之后都进行数据的转移操作，保证sin和sout的数据一致性，但这题目，输出只会从sout出，pop也只取soout，输入只从sin进，不需要保证sin sout的一致性，即数据只会从Sin到sout，所以在sout为空的时候，直接把sin全部翻转到sout就可以了。

```CPP
class MyQueue {
private:
    void in2out() {
        while (!sin.empty()) {
            sout.push(sin.top());
            sin.pop();
        }
    }
    stack<int> sin;
    stack<int> sout;
public:
    MyQueue() {
    }
    void push(int x) {
        sin.push(x);
    }
    int pop() {
        if(sout.empty()){
            in2out();
        }
        int last = sout.top();
        sout.pop();
        return last;
    }
    int peek() {
        if (sout.empty()) {
            in2out();
        }
        return sout.top();
    }
    bool empty() {
        return sin.empty() and sout.empty();
    }
};
```

## 225 用队列实现栈

可以用两个队列实现也可以只用一个队列实现。

```CPP
class MyStack {
    queue<int> qin;
    queue<int> qout;
public:
    MyStack() {
    }
    void push(int x) {
        qin.push(x);
        while(!qout.empty()){
            qin.push(qout.front());
            qout.pop();
        }
        swap(qin,qout);
    }
    int pop() {
        int res = qout.front();
        qout.pop();
        return res;
    }
    int top() {
        return qout.front();
    }
    bool empty() {
        return qin.empty() && qout.empty();
    }   
};
```
一个队列的方法。

## 20 有效的括号

4ms？还有更快速度的方法。
```CPP
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(auto item : s){
            if(st.empty()){
                st.push(item);
                continue;
            }
            if(st.top() == '(' and item == ')'){
                st.pop();
                continue;
            }else if(st.top() == '{' and item == '}'){
                st.pop();
                continue;
            }else if(st.top() == '[' and item == ']'){
                 st.pop();
                 continue;
            }else {
                st.push(item);
            }
        }
        if(st.empty()){
            return true;
        }
        return false;
    }
};
```

## 150 逆波兰表达式求值
16 ms 24.40%， 时间复杂度很高，方法不快
注：C++11 string STL提供了stoi函数，可以直接将string转换为int

使用数组代替stack应该能提速

```CPP
int str2num(string str1){
    int res = 0;
    int level = 0;
    while(!str1.empty()){
        if(str1.back() != '-'){
            res += (str1.back() - '0') * pow(10,level);
            level++;
            str1.pop_back();
        }else{
            res = -res;
            str1.pop_back();
        }
    }
    return res;
}
int evalRPN(vector<string>& tokens) {
    stack<int> res;
    for(auto n : tokens){
        if(n != "+" && n != "-" && n != "*" && n != "/"){
            res.push(str2num(n));
            continue;
        }
        if( n == "+" ){
            int n2 = res.top();
            res.pop();
            int n1 = res.top();
            res.pop();
            res.push(n1 + n2);
        }
        if( n == "-" ){
            int n2 = res.top();
            res.pop();
            int n1 = res.top();
            res.pop();
            res.push(n1 - n2);
        }
        if( n == "*" ){
            int n2 = res.top();
            res.pop();
            int n1 = res.top();
            res.pop();
            res.push(n1 * n2);
        }
        if( n == "/" ){
            int n2 = res.top();
            res.pop();
            int n1 = res.top();
            res.pop();
            res.push(n1 / n2);
        }
    }
    return res.top();
}
```

