#include <iostream>
#include <unordered_map>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    int lengthA = 0;
    ListNode *nodeA = headA;
    while (nodeA->next != nullptr) {
        lengthA++;
        nodeA = nodeA->next;
    }
    int lengthB = 0;
    ListNode *nodeB = headB;
    while (nodeB->next != nullptr) {
        lengthB++;
        nodeB = nodeB->next;
    }
    if (nodeA != nodeB) {
        return nullptr;
    }
    nodeA = headA;
    nodeB = headB;
    while (lengthA > lengthB) {
        nodeA = nodeA->next;
        lengthA--;
    }
    while (lengthB > lengthA) {
        nodeB = nodeB->next;
        lengthB--;
    }
    while (nodeA != nodeB) {
        nodeA = nodeA->next;
        nodeB = nodeB->next;
    }
    return nodeA;
}

int main() {
    {   // Example 1
        ListNode five(5);
        ListNode four(4);
        four.next = &five;
        ListNode eight(8);
        eight.next = &four;

        ListNode one1(1);
        one1.next = &eight;
        ListNode four1(4);
        four1.next = &one1;

        ListNode one2(1);
        one2.next = &eight;
        ListNode six2(6);
        six2.next = &one2;
        ListNode five2(5);
        five2.next = &six2;
        cout << (getIntersectionNode(&four1, &five2) == &eight) << endl;
    }
    {   // Example 2
        ListNode four(4);
        ListNode two(2);
        two.next = &four;

        ListNode one12(1);
        one12.next = &two;
        ListNode nine1(9);
        nine1.next = &one12;
        ListNode one11(1);
        one11.next = &nine1;

        ListNode three2(3);
        three2.next = &two;
        cout << (getIntersectionNode(&one11, &three2) == &two) << endl;
    }
    {   // Example 3
        ListNode four(4);
        ListNode six(6);
        six.next = &four;
        ListNode two(2);
        two.next = &six;

        ListNode five(5);
        ListNode one(1);
        one.next = &five;
        cout << (getIntersectionNode(&two, &one) == nullptr) << endl;
    }
}