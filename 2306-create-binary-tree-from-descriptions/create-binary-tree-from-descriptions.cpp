class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> hasParent;

        for (auto& d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            // Create parent node if it doesn't exist
            if (!nodes.count(parent)) {
                nodes[parent] = new TreeNode(parent);
            }

            // Create child node if it doesn't exist
            if (!nodes.count(child)) {
                nodes[child] = new TreeNode(child);
            }

            // Connect child
            if (isLeft == 1) {
                nodes[parent]->left = nodes[child];
            } else {
                nodes[parent]->right = nodes[child];
            }

            // Child has a parent
            hasParent.insert(child);
        }

        // Find the node that has no parent
        for (auto& [value, node] : nodes) {
            if (!hasParent.count(value)) {
                return node;
            }
        }

        return nullptr;
    }
};