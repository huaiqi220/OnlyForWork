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