#include <vector>
#include <queue>
#include <climits>

namespace Trees
{
    const int null = INT_MIN;

    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
        ~TreeNode() { delete left; delete right; }
    };


    struct ListNode
    {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };
    struct DoublyListNode
    {
        int val;
        DoublyListNode* prev, * next;
        DoublyListNode() : val(0), prev(nullptr), next(nullptr) {}
        DoublyListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
        DoublyListNode(int x, DoublyListNode* prev, DoublyListNode* next) : val(x), prev(prev), next(next) {}
    };

    /* std::vector to doubly linked-list */
    template<class T>
    void to_list2(std::vector<int>& input, T*& node)
    {
        // either the list is empty or root is null
        if (input.empty() || input.front() == null)
            return;

        node = new T(input[0]);
        T* curr = node;
        T* prev = curr;

        for (int i = 1; i < input.size(); ++i)
        {
            curr->next = new T(input[i]);;
            prev = curr;
            curr = curr->next;
            curr->prev = prev;
        }


    }

    /* std::vector to singly linked-list */
    template<class T>
    void to_list(std::vector<int>& input, T*& node)
    {
        // either the list is empty or root is null
        if (input.empty() || input.front() == null)
            return;

        node = new T(input[0]);
        T* curr = node;

        for (int i = 1; i < input.size(); ++i)
        {
            curr->next = new T(input[i]);
            curr = curr->next;
        }


    }

    /* Create a tree from a std::vector of numbers */
    template<class T>
    void to_tree(std::vector<int>& input, T*& node)
    {
        // either the list is empty or root is null
        if (input.empty() || input.front() == null)
            return;

        std::queue<T*> q;
        node = new T(input[0]);
        int index = 1;


        T* curr = node;

        while (index < input.size())
        {
            if (index < input.size() && input[index] > null)
            {
                curr->left = new T(input[index]);
                q.push(curr->left);
            }

            if (index + 1 < input.size() && input[index + 1] > null)
            {
                curr->right = new T(input[index + 1]);
                q.push(curr->right);
            }

            if (q.size())
            {
                curr = q.front();
                q.pop();
            }

            index += 2;
        }

    }
}