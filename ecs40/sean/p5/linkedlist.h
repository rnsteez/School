// Author: Sean Davis
#ifndef linkedlistH
#define linkedlistH

class Directory;
class LinkedList;

class ListNode
{
  Directory *directory;
  ListNode *next;
  ListNode(Directory *d, ListNode *n);
  ~ListNode();
  friend class LinkedList;

}; // ListNode class


class LinkedList
{
  ListNode *head;
public:
  LinkedList();
  ~LinkedList();
  const Directory* operator[] (int index)const;
  Directory* operator[] (int index);
  LinkedList& operator+= (Directory *directory);
  //LinkedList& operator= (const LinkedList &linkedList);
}; // LinkedList class

#endif
