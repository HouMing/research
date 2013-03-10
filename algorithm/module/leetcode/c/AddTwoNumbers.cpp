/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <a.out.h> 
#include <stdlib.h>
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int loc = 1;
    int carry = 0;
    ListNode* ret;
    while (l1->next != NULL && l2->next != NULL)
    {
      ListNode* t = new ListNode(0);
      if ( loc == 1) {
        ret = t;
        ret->val = l1->val + l2->val + carry;
        carry = 0;
      } else {
        t->val = l1->val + l2->val + carry;
        carry = 0;
      }
      if (t->val > 10) {
        t->val -= 10;
        carry = 1;
      }
    }
    return ret;
  }
};

ListNode* add (ListNode* l, int val)
{
  ListNode *n = new ListNode(val);
  l->next = n;
  return l;
}

int main () {
  ListNode l1(2);
  ListNode l2(5);
  add(add(&l1, 4), 3);
  add(add(&l2, 5), 4);
  Solution sln;
  sln.addTwoNumbers(&l1, &l2);
}
