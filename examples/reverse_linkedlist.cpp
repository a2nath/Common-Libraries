#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include "../inc/trees.h"

using namespace std;
using namespace Trees;


TreeNode* make_tree(vector<int> input)
{
    TreeNode* node = nullptr;

    to_tree(input, node);

    return node;
}

DoublyListNode* make_list2(vector<int> input)
{
    DoublyListNode* node = nullptr;
    to_list2(input, node);
    return node;
}

ListNode* make_list(vector<int> input)
{
    ListNode* node = nullptr;
    to_list(input, node);
    return node;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* next1 = head, * prev = NULL, * curr = head;
        while (curr != NULL) {
            next1 = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next1;
        }
        return prev;
    }
};


int main()
{
    ListNode* head = make_list(vector<int>{1, 2, 3, 4, 5});
    ListNode* curr = head;
    
    cout << "Original linked-list: ";
    while (curr)
    {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;

    Solution s;
    ListNode* newhead = s.reverseList(head);
    curr = newhead;

    cout << "Modified linked-list: ";
    while (curr)
    {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
    delete newhead;

    return 0;

}