## 02.04分割链表

第一次做在那玩指针，玩的链表断裂在那猛调执行出错

事实上直接记录小大两个链表就行了，也是一次遍历

```cpp
ListNode* partition(ListNode* head, int x) {
    ListNode* small = new ListNode();
    ListNode* big = new ListNode();
    while(head != nullptr){
        if(head->val < x){
            ListNode* m = head->next;
            head->next = small->next;
            small->next = head;
            head = m;
        }else if(head->val >= x){
            ListNode* m = head->next;
            head->next = big->next;
            big->next = head;
            head = m;
        }
    }
    ListNode* sl = small;
    while(sl->next !=nullptr){
        sl = sl->next;
    }
    sl->next = big->next;
    return small->next;
}

ListNode* partition(ListNode* head, int x) {
    if(head == nullptr) return head;
    ListNode* dummy = new ListNode();
    dummy->next = head;
    ListNode* lptr =head->next;
    // 第一次做的时候，始终出现莫名其妙的head used free，今天给我发现了，就是这head->next没有置nullptr
    head->next = nullptr;
    while(lptr != nullptr){
        ListNode* m = lptr->next;
        if(lptr->val < x){
            lptr->next = dummy->next;
            dummy->next = lptr;
        }else{
            lptr->next = head->next;
            head->next = lptr;
        }
        lptr = m;
    }
    return dummy->next;
}




```


## 203 移除链表元素

用一个dummy虚拟头节点，然后遍历，就不用单独处理head== nullptr的特殊情况

但这个简单题目，竟然写了十多分钟，是真不合适

```CPP
ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummy = new ListNode();
    dummy->next = head;
    ListNode* prior = dummy;
    ListNode* deal = head;
    while(deal != nullptr){
        if(deal->val == val){
            prior->next = deal->next;
            deal = prior->next;
        }else{
            prior = prior->next;
            deal = deal->next;
        }
    }
    ListNode*  ans = dummy->next;
    delete(dummy);
    return ans;
}
```
这是个经典的，处理后一个节点的模板，不记录prior的话，就不知道上一个节点，这个代码争取拿着就写，还犹豫就是不够熟练


## 707 设计链表

简单题目又没有秒，还体现出了C++理解的一些问题——List容器底层双向链表实现，不提供[]运算符。

list的迭代器使用++或者std::advance(it,index)步进。

list的insert(it,val)插入到it之前，erase(it)删除it指向的元素。

```CPP
class MyLinkedList {
    list<int> myList;
public:
    MyLinkedList() {  
    }
    int get(int index) {
        if(index >= 0 and index < myList.size()){
            auto it = myList.begin();
            std::advance(it, index);
            return *it;
        }else{
            return -1;
        }
    }
    void addAtHead(int val) {
        myList.push_front(val);
    }
    void addAtTail(int val) {
        myList.push_back(val);
    }
    void addAtIndex(int index, int val) {
        if(index == myList.size()){
            myList.push_back(val);
        }else if(index < myList.size()){
            auto it = myList.begin();
            std::advance(it, index);
            myList.insert(it,val);
        }
    }
    void deleteAtIndex(int index) {
        if(index >=0 and index < myList.size()){
            auto it = myList.begin();
            std::advance(it, index);
            myList.erase(it);
        }
    }
};s
```
一种使用list的实现方法，使用ListNode也能实现，实现方法很多。

## 206 反转链表

头插法秒了

```CPP
ListNode* reverseList(ListNode* head) {
    ListNode* dummy = new ListNode();
    while(head != nullptr){
        ListNode* n = head->next;
        head->next = dummy->next;
        dummy->next = head;
        head = n;
    }
    return dummy->next;
}
```

## 24 两两交换链表中的节点

这题我才用了一个非常复杂的方法，根据mark的正负来判断是插入末尾还是插入到last后面，然后last指针指向新的节点，最后返回dummy->next

```CPP
// 我的复杂方法
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode();
        ListNode* last = dummy;
        bool mark = false;
        while(head != nullptr){
            ListNode* n = head->next;
            if(mark == false){
                // 就下面这行代码，模型奇妙，没它就heap use after free，加上就通过，有空调试一下加深印象
                head->next = nullptr;
                last->next = head;
                mark = !mark;
            }else{
                head->next = last->next;
                last->next = head;
                last = last->next->next;
                mark = !mark;
            }
            head = n;
        }
        ListNode* result = dummy->next;
        delete dummy;

        return result;
    }

    // 递归写法，递归写法比我的指针交换法不容易出错
ListNode* swapPairs(ListNode* head) {
    if(head == nullptr || head->next == nullptr){
        return head;
    }
    ListNode* second = head->next;
    head->next = swapPairs(second->next);
    second->next = head;
    return second;
}
};
```
编码中有两个总结

1. 不能直接!mark；mark =!mark 跟!mark不是一个东西！！！

2. head->next = nullptr;

## LCR 078 合并K个升序链表

k个取小，指针进一，超过5.21%

前置题目，合并两个升序链表

## 19 删除链表的倒数第N个节点
不要用vector，双指针
```CPP

```



