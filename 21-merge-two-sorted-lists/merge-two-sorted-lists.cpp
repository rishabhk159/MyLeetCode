class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        // Stack-allocated dummy head to avoid heap allocation
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // Splice the remaining non-empty list in O(1)
        tail->next = (list1 != nullptr) ? list1 : list2;

        return dummy.next;
    }
};