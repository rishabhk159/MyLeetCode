class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int prev = -1;
        int minDist = INT_MAX;

        int pos = 1;
        ListNode* curr = head;

        while (curr->next != nullptr && curr->next->next != nullptr) {
            
            int a = curr->val;
            int b = curr->next->val;
            int c = curr->next->next->val;

            // Check if curr->next is a critical point
            if ((b > a && b > c) || (b < a && b < c)) {
                
                int currentPos = pos + 1;

                if (first == -1) {
                    // First critical point
                    first = currentPos;
                } 
                else {
                    // Distance from previous critical point
                    minDist = min(minDist, currentPos - prev);
                }

                prev = currentPos;
            }

            pos++;
            curr = curr->next;
        }

        // Fewer than 2 critical points
        if (first == -1 || first == prev) {
            return {-1, -1};
        }

        int maxDist = prev - first;

        return {minDist, maxDist};
    }
};