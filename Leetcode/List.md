## 02.04分割链表

第一次做在那玩指针，玩的链表断裂在那猛调执行出错

事实上直接记录小大两个链表就行了，也是一次遍历

```cpp
class Solution {
public:
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
};

```
