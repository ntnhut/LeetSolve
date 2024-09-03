#include <iostream>
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* searchBST(TreeNode* root, int val) {
    while (root != nullptr && root->val != val) {
        if (val < root->val) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

void printNode(TreeNode* root) {
    if (root == nullptr) return;
    std::cout << root->val;
    if (root->left) {
        std::cout << ",";
        printNode(root->left);
    }
    if (root->right)  {
        std::cout << ",";
        printNode(root->right);
    }    
}

void printTree(TreeNode* root) {
    std::cout << "[";
    printNode(root);
    std::cout << "]" << std::endl;
}

int main() {
    TreeNode one(1);
    TreeNode three(3);
    TreeNode two(2, &one, &three);
    TreeNode seven(7);
    TreeNode four(4, &two, &seven);
    // Example 1
    printTree(searchBST(&four, 2));
    // Example 2
    printTree(searchBST(&four, 5));
}