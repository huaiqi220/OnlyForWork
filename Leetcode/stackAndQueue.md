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
public:
    queue<int> q1;
    queue<int> q2;
    MyStack() {
    }
    void push(int x) {
        q2.push(x);
        while(!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1,q2);
    }
    int pop() {
        int item = q1.front();
        q1.pop();
        return item;   
    }
    int top() {
        return q1.front();
    }
    bool empty() {
        return q1.empty();
    }
};
```

一个队列的方法。