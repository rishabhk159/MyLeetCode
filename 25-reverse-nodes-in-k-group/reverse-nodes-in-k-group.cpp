class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        if (!head || k <= 1) return head;

        // Stack-allocated sentinel to avoid heap dynamic allocation
        ListNode dummy(0);
        dummy.next = head;
        ListNode* groupPrev = &dummy;

        while (true) {
            // Check if there are at least k nodes left to reverse
            ListNode* kth = groupPrev;
            for (int i = 0; i < k && kth != nullptr; ++i) {
                kth = kth->next;
            }
            if (!kth) break; // Fewer than k nodes remain, keep them as is

            ListNode* groupNext = kth->next;
            ListNode* prev = groupNext;
            ListNode* curr = groupPrev->next;

            // Reverse k nodes in-place
            while (curr != groupNext) {
                ListNode* temp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = temp;
            }

            // Connect previous group to the newly reversed group head
            ListNode* temp = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = temp;
        }

        return dummy.next;
    }
};