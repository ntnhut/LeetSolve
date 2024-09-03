#include <iostream>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) 
    : val(x), left(left), right(right) {}
};
//! @param p, q are binary trees
//! @return true if p and q are identical in both structures and values
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) return true;
    if (p == nullptr || q == nullptr) return false;        
    if (p->val != q->val) return false;
    return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
}
int main() {
    {   // Example 1
        TreeNode two1(2);
        TreeNode three1(3);
        TreeNode p(1, &two1, &three1);
        TreeNode two2(2);
        TreeNode three2(3);
        TreeNode q(1, &two2, &three2);
        std::cout << (isSameTree(&p, &q) ? "true" : "false") << std::endl;
    }
    {   // Example 2
        TreeNode two1(2);
        TreeNode p(1, &two1, nullptr);
        TreeNode two2(2);
        TreeNode q(1, nullptr, &two2);
        std::cout << (isSameTree(&p, &q) ? "true" : "false") << std::endl;
    }
    {   // Example 3
        TreeNode two1(2);
        TreeNode one1(1);
        TreeNode p(1, &two1, &one1);
        TreeNode two2(2);
        TreeNode one2(1);
        TreeNode q(1, &one2, &two2);
        std::cout << (isSameTree(&p, &q) ? "true" : "false") << std::endl;
    }
}