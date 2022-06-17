#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//! @param root The root node.
//! @return The number of nodes along the longest path from root.
//! @author Nhut Nguyen
int maxDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

int main() {
    TreeNode fifteen(15);
    TreeNode seven(7);
    TreeNode twenty(20, &fifteen, &seven);
    TreeNode nine(9);
    TreeNode three(3, &nine, &twenty);
    std::cout << maxDepth(&three) << std::endl; // 3
    TreeNode two(2);
    TreeNode one(1, nullptr, &two);
    std::cout << maxDepth(&one) << std::endl; // 2
}