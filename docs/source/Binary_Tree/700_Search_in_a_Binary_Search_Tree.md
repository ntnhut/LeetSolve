# Search in a Binary Search Tree

## [Problem statement](https://leetcode.com/problems/search-in-a-binary-search-tree)

You are given the `root` of a binary search tree (BST) and an integer `val`.

Find the node in the BST that the node's value equals `val` and return the subtree rooted with that node. If such a node does not exist, return `null`.

### Example 1

![The BST in Example 1](700_tree1.jpg)

```plain
Input: root = [4,2,7,1,3], val = 2
Output: [2,1,3]
```

### Example 2

![The BST in Example 2](700_tree2.jpg)

```plain
Input: root = [4,2,7,1,3], val = 5
Output: []
``` 

### Constraints

* The number of nodes in the tree is in the range `[1, 5000]`.
* `1 <= Node.val <= 10^7`.
* `root` is a binary search tree.
* `1 <= val <= 10^7`.

## Solution 1: Recursive approach

To solve this problem, you can leverage the properties of a binary search tree. In a BST, for any given node:

* The left subtree contains only nodes with values less than the node's value.

* The right subtree contains only nodes with values greater than the node's value.

Given this property, we can use a recursive approach to search for the node:

1. Start at the root node.
2. If the `root` is `null`, return `null` (base case).
3. If the `root`'s value equals `val`, return the `root`.
4. If `val` is less than the `root`'s value, recursively search the left subtree.
5. If `val` is greater than the `root`'s value, recursively search the right subtree.

This approach ensures that you efficiently find the node or determine that it does not exist in the tree.

### Code
```cpp
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
    if (root == nullptr || root->val == val) return root;
    if (val < root->val) return searchBST(root->left, val);
    return searchBST(root->right, val);
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
```

```plain
Output:
[2,1,3]
[]
```

### Complexity

* Runtime: `O(log n)`, where `n` is the number of nodes in the tree. This is because, in the best case, we halve the search space at each step.
* Extra memory: `O(1)`as we are not using any additional data structures that grow with the input size.

### Summary 

1. **Understanding BST Properties**: This solution leverages the properties of BSTs to efficiently search for a node. Understanding these properties is crucial for solving similar problems.

2. **Recursive Approach**: The recursive approach simplifies the problem by breaking it down into smaller subproblems. Each recursive call handles a smaller part of the tree.

3. **Base Cases**: Handling base cases (e.g., when the root is `null` or the node is found) is essential to avoid infinite recursion and ensure correct results.

## Solution 2: Non-recursive (iterative) approach

You can use a loop to traverse the tree instead of recursion.

### Code

```cpp
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
```

## Key takeaway

1. **Iterative Approach**: The iterative approach avoids the overhead of recursive function calls, which can be beneficial in environments with limited stack space.

2. **Efficiency**: Like the recursive approach, the iterative solution is efficient with a time complexity of `O(log n)` for balanced trees.

3. **Practical Application**: Understanding both recursive and iterative approaches provides flexibility in solving tree-related problems, which is valuable in coding interviews and real-world applications.
