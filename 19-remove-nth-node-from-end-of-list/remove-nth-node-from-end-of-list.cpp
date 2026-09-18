class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        // Stack-allocated dummy node avoids heap allocation
        ListNode dummy(0, head);
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        // Advance fast pointer n + 1 steps ahead
        for (int i = 0; i <= n; ++i) {
            fast = fast->next;
        }

        // Move both pointers until fast reaches the end
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // Bypass the target node
        slow->next = slow->next->next;

        return dummy.next;
    }
};