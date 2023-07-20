# Swap Nodes in Pairs

## [Problem statement](https://leetcode.com/problems/swap-nodes-in-pairs/)
Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)
 
### Example 1
![The link list and its result in Example 1.](02_LL_24_swap_ex1.jpg)
```text
Input: head = [1,2,3,4]
Output: [2,1,4,3]
```

### Example 2
```text
Input: head = []
Output: []
```
### Example 3
```text
Input: head = [1]
Output: [1]
``` 

### Constraints

* The number of nodes in the list is in the range `[0, 100]`.
* `0 <= Node.val <= 100`.

## Solution

Draw a picture of the swapping to identify the correct order of the update.

![The swapping steps.](02_LL_24_drawing_1.png)

Denote `(cur, next)` the pair of nodes you want to swap and `prev` be the previous node that links to `cur`. Here are the steps you need to perform for the swapping.
1. Update the links between nodes.
2. Go to the next pair. 

### Code
```cpp
#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* preNode = nullptr;
    ListNode* curNode = head; 
    ListNode* nextNode = head->next;  
    head = nextNode;
    while (curNode != nullptr && nextNode != nullptr) {
        curNode->next = nextNode->next;
        nextNode->next = curNode;
        if (preNode) {
            preNode->next = nextNode;
        }
        preNode = curNode;
        curNode = curNode->next;       
        if (curNode) {
            nextNode = curNode->next;
        }
    }
    return head;
}
void print(ListNode* head) {
    ListNode* node = head;
    std::cout << "[";
    while (node != nullptr) {
        std::cout << node->val << ",";
        node = node->next;
    }
    std::cout << "]" << std::endl;
}
int main() {
    ListNode four(4);
    ListNode three(3, &four);
    ListNode two(2, &three);
    ListNode one(1, &two);    
    print(swapPairs(&one));
    ListNode five(5);
    print(swapPairs(nullptr));
    print(swapPairs(&five));
}
```
```text
Output:
[2,1,4,3,]
[]
[5,]
```
### Complexity
* Runtime: $O(N)$, where $N$ is the number of nodes.
* Extra space: $O(1)$.


