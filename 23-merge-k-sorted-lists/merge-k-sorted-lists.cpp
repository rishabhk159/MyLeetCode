class Solution {
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = (l1 != nullptr) ? l1 : l2;
        return dummy.next;
    }

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int n = lists.size();
        if (n == 0) return nullptr;

        // Iterative Divide and Conquer (in-place)
        int step = 1;
        while (step < n) {
            for (int i = 0; i + step < n; i += step * 2) {
                lists[i] = mergeTwoLists(lists[i], lists[i + step]);
            }
            step *= 2;
        }

        return lists[0];
    }
};