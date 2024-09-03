# Same Tree

## [Problem statement](https://leetcode.com/problems/same-tree/)

Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

### Example 1

![The trees in Example 1](100_ex1.jpg)

```plain
Input: p = [1,2,3], q = [1,2,3]
Output: true
```

### Example 2

![The trees in Example 2](100_ex2.jpg)

```plain
Input: p = [1,2], q = [1,null,2]
Output: false
```

### Example 3

![The trees in Example 3](100_ex3.jpg)

```plain
Input: p = [1,2,1], q = [1,1,2]
Output: false
```

### Constraints

* The number of nodes in both trees is in the range `[0, 100]`.
* `-10^4 <= Node.val <= 10^4`.

## Solution

To determine whether two binary trees are the same, you can use a recursive approach that traverses both trees simultaneously. The idea is to compare corresponding nodes in both trees as you traverse them:

* **Base Case**: If both nodes are `nullptr`, they are considered identical at this position.
* If one of the nodes is `nullptr` and the other is not, they are not the same.
* If both nodes have values but the values differ, the trees are not identical at this point.
* **Recursive Case**: If the current nodes are the same, you recursively check the left and right subtrees. The trees are only considered identical if both the left and right subtrees are also identical.

By following this strategy, you ensure that every node in both trees is compared in the same relative position, which determines whether the entire tree structures are the same.

### Code
```cpp
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
```
```plain
Output:
true
false
false
```

### Complexity

* Runtime: `O(n)`, where `n` is the size of one tree.
* Extra space: `O(1)`.

## Key takeaway

This problem highlights the importance of understanding recursion in tree traversal. By breaking down the problem into smaller subproblems: comparing individual nodes and their subtrees, you can effectively determine whether two binary trees are identical. 

The recursive approach mirrors the tree structure itself, making it an intuitive and powerful technique for tree-related problems.

This problem also emphasizes the significance of base cases in recursion. Especially when dealing with data structures like trees where `nullptr` values play a crucial role in defining the structure. Understanding how to handle these edge cases is key to mastering recursion and tree algorithms.