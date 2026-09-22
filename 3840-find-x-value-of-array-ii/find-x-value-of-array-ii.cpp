class Solution {
public:
    struct Node {
        int prod;              // Product of entire segment % k
        int pref[5];           // Number of non-empty prefixes with each residue

        Node(int k = 1) {
            prod = 1 % k;
            for (int i = 0; i < 5; i++) pref[i] = 0;
        }
    };

    int k;
    vector<Node> seg;

    Node mergeNode(const Node& A, const Node& B) {
        Node C(k);

        // Product of complete segment
        C.prod = (A.prod * B.prod) % k;

        // Prefixes entirely inside A
        for (int r = 0; r < k; r++) {
            C.pref[r] += A.pref[r];
        }

        // Prefixes = all of A + a prefix of B
        for (int r = 0; r < k; r++) {
            int nr = (A.prod * r) % k;
            C.pref[nr] += B.pref[r];
        }

        return C;
    }

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            seg[p] = Node(k);
            seg[p].prod = nums[l] % k;
            seg[p].pref[seg[p].prod] = 1;
            return;
        }

        int mid = (l + r) >> 1;

        build(p << 1, l, mid, nums);
        build(p << 1 | 1, mid + 1, r, nums);

        seg[p] = mergeNode(seg[p << 1], seg[p << 1 | 1]);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            seg[p] = Node(k);
            seg[p].prod = val % k;
            seg[p].pref[seg[p].prod] = 1;
            return;
        }

        int mid = (l + r) >> 1;

        if (idx <= mid)
            update(p << 1, l, mid, idx, val);
        else
            update(p << 1 | 1, mid + 1, r, idx, val);

        seg[p] = mergeNode(seg[p << 1], seg[p << 1 | 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[p];

        int mid = (l + r) >> 1;

        if (qr <= mid)
            return query(p << 1, l, mid, ql, qr);

        if (ql > mid)
            return query(p << 1 | 1, mid + 1, r, ql, qr);

        Node left = query(p << 1, l, mid, ql, qr);
        Node right = query(p << 1 | 1, mid + 1, r, ql, qr);

        return mergeNode(left, right);
    }

    vector<int> resultArray(vector<int>& nums, int K,
                            vector<vector<int>>& queries) {
        k = K;
        int n = nums.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent point update
            nums[index] = value;
            update(1, 0, n - 1, index, value);

            // All possible remaining arrays are non-empty prefixes
            // of nums[start ... n-1].
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.pref[x]);
        }

        return ans;
    }
};