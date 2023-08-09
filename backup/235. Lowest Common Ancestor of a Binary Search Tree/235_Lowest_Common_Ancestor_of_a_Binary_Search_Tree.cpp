#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val < root->val && q->val < root->val) {
        return lowestCommonAncestor(root->left, p, q);
    } else if (root->val < p->val && root->val < q->val) {
        return lowestCommonAncestor(root->right, p, q);
    }
    return root;
}

int main() {
    TreeNode zero(0);
    TreeNode three(3);
    TreeNode five(5);
    TreeNode four(4);
    four.left = &three;
    four.right = &five;
    TreeNode two(2);
    two.left = &zero;
    two.right = &four;
    TreeNode seven(7);
    TreeNode nine(9);
    TreeNode eight(8);
    eight.left = &seven;
    eight.right = &nine;
    TreeNode six(6);
    six.left = &two;
    six.right = &eight;

    cout << lowestCommonAncestor(&six, &two, &eight)->val << endl;
    cout << lowestCommonAncestor(&six, &two, &four)->val << endl;
    cout << lowestCommonAncestor(&two, &two, &zero)->val << endl;
}