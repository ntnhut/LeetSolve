# Linked List Cycle

## [Problem statement](https://leetcode.com/problems/linked-list-cycle/)

Given `head`, the head of a linked list, determine if the linked list has a cycle in it.

Return `true` if there is a cycle in the linked list. Otherwise, return `false`.

 

### Example 1
![The linked list of Example 1](08_TP_141_circularlinkedlist.png)
```text
Input: head = [3,2,0,-4], where -4 links next to 2.
Output: true
```

### Example 2
![The linked list of Example 2](08_TP_141_circularlinkedlist_test2.png)
```text
Input: head = [1,2], where 2 links next to 1.
Output: true
```

### Example 3
![The linked list of Example 3](08_TP_141_circularlinkedlist_test3.png)
```text
Input: head = [1], and 1 links to NULL.
Output: false
Explanation: There is no cycle in this linked list.
``` 

### Constraints

* The number of the nodes in the list is in the range `[0, 10^4]`.
* `-10^5 <= Node.val <= 10^5`.
 

**Follow up:** Can you solve it using $O(1)$ (i.e. constant) memory?

## Solution 1: Storing the visited nodes

### Code
```cpp
#include <unordered_map>
#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
bool hasCycle(ListNode *head) {
    std::unordered_map<ListNode*, int> m;
    while (head) {
        if (m[head] > 0) {
            return true;
        }
        m[head]++;
        head = head->next;
    }
    return false;
}
int main() {
    {
        ListNode three(3);
        ListNode two(2);
        three.next = &two;
        ListNode zero(0);
        two.next = &zero;
        ListNode four(4);
        zero.next = &four;
        four.next = &two;
        std::cout << hasCycle(&three) << std::endl;
    }
    {
        ListNode one(1);
        ListNode two(2);
        one.next = &two;
        two.next = &one;
        std::cout << hasCycle(&one) << std::endl;
    }
    {
        ListNode one(1);
        std::cout << hasCycle(&one) << std::endl;
    }
}
```
```text
Output:
1
1
0
```

### Complexity
* Runtime: $O(N)$, where $N$ is the length of the linked list.
* Extra space: $O(N)$.

## Solution 2: Fast and slow runners
Imagine there are two runners both start to run along the linked list from the `head`. One runs twice faster than the other. 

If the linked list has a cycle in it, they will meet at some point. Otherwise, they never meet each other.

### Example 1
The slower runs `[3,2,0,-4,2,0,...]` while the faster runs `[3,0,2,-4,0,2,...]`. They meet each other at node `-4` after three steps.

### Example 2
The slower runs `[1,2,1,2,...]` while the faster runs `[1,1,1,...]`. They meet each other at node `1` after two steps.

### Code
```cpp
#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
bool hasCycle(ListNode *head) {
    if (head == nullptr) {
        return false;
    }
    ListNode* fast = head;
    ListNode* slow = head;    
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            return true;
        }
    }
    return false;
}
int main() {
    {
        ListNode three(3);
        ListNode two(2);
        three.next = &two;
        ListNode zero(0);
        two.next = &zero;
        ListNode four(4);
        zero.next = &four;
        four.next = &two;
        std::cout << hasCycle(&three) << std::endl;
    }
    {
        ListNode one(1);
        ListNode two(2);
        one.next = &two;
        two.next = &one;
        std::cout << hasCycle(&one) << std::endl;
    }
    {
        ListNode one(1);
        std::cout << hasCycle(&one) << std::endl;
    }
}
```
```text
Output:
1
1
0
```

### Complexity
* Runtime: $O(N)$, where $N$ is the length of the linked list.
* Extra space: $O(1)$.



