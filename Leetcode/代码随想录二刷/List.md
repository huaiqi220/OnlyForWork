## 203 移除链表元素
秒了
```CPP
ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummy = new ListNode();
    dummy->next = head;
    ListNode* copy = dummy;
    while(copy->next != nullptr){
        if(copy->next->val == val){
            ListNode* del = copy->next;
            copy->next = copy->next->next;
            delete(del);
        }else{
            copy = copy->next;
        }
    }
    return dummy->next;
}
```

## 707 设计链表
设计链表，卡了一会，容我用VS2022搞一哈
好吧，也没搞出来，用struct搞就是很繁琐，没注意到下表是从0开始，get是根据下标，而不是个数
```CPP
// 卡了好一会，要背住
class MyLinkedList {
private:
    // 私有类型建议以_开始命名
    int _size;
    ListNode* _dummyHead;
public:
    MyLinkedList() {
        _dummyHead = new ListNode(0);
        _size = 0;
    }
    int get(int index) {
        if (index > (_size - 1) || index < 0) {
            return -1;
        }
        ListNode* cur = _dummyHead->next;
        while (index--) {
            cur = cur->next;
        }
        return cur->val;
    }
    void addAtHead(int val) {
        _size++;
        ListNode* newNode = new ListNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;

    }
    void addAtTail(int val) {
        _size++;
        ListNode* newNode = new ListNode(val);
        ListNode* cur = _dummyHead;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
    void addAtIndex(int index, int val) {
        if (index > _size) return;// 因为之前插入，所以这里其实可以等于_size
        if (index < 0) index = 0;
        ListNode* newNode = new ListNode(val);
        ListNode* cur = _dummyHead;
        while (index--) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
    }
    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) {
            return;
        }
        ListNode* cur = _dummyHead;
        while (index--) {
            cur = cur->next;
        }
        ListNode* del = cur->next;
        cur->next = cur->next->next;
        delete(del);
        del = nullptr;
        _size--;
    }
};
```

## 206 反转链表
头插法
```CPP
ListNode* reverseList(ListNode* head) {
    ListNode* dummy = new ListNode(0);
    while(head){
        ListNode* n = head->next;
        head->next = nullptr;
        head->next = dummy->next;
        dummy->next = head;
        head = n;
    }
    return dummy->next;
}
```
## 24 两两交换链表中的节点
用个count记录节点数的迭代方法，出bug，递归特别简单，在此把两种方法都写一下
```CPP
// 递归
ListNode* swapPairs(ListNode* head) {
    if(head == nullptr || head->next == nullptr){
        return head;
    }
    ListNode* second = head->next;
    head->next = swapPairs(second->next);
    second->next = head;
    return second;
}
```
```CPP
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode();
        int count = 1;
        ListNode* moveptr = dummy;
        while(head){
            ListNode* cur = head->next;
            // 很绷不住，代码几次跑不过，加了一行这个就跑过了
            head->next = nullptr;
            if(count % 2 == 1){
                moveptr->next = head;
            }
            if(count % 2 == 0){
                head->next = moveptr->next;
                moveptr->next = head;
                moveptr = moveptr->next->next;
            }
            count++;
            head = cur;
        }
        return dummy->next;
    }
```
