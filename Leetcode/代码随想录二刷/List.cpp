
struct ListNode
{
    /* data */
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr){}
    ListNode(int value): val(value),next(nullptr){}
    ListNode(int value,ListNode* next): val(value), next(next) {}
};


class SolutionList{
public:
    // 206反转链表，头插法
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

    // 两个一组翻转的迭代法，相对还有递归法
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
};