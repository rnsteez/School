// Author: Sean Davis
#include <iostream> // for NULL
#include "linkedlist.h"
#include "directory.h"

ListNode::ListNode(Directory *d, ListNode *n): directory(d), next(n)
{
} // ListNode()


ListNode::~ListNode()
{
  delete directory;
} // ~ListNode()


LinkedList::LinkedList() : head(NULL)
{
} // LinkedList()

LinkedList::~LinkedList()
{
  ListNode *ptr;

  for(ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } // for each ListNode
} // ~LinkedList()


const Directory* LinkedList::operator[] (int index)const
{
  int i;
  ListNode *ptr;

  for(i = 0, ptr = head; ptr && i < index; i++, ptr = ptr->next);

  return ptr->directory;
} // operator[] const



Directory* LinkedList::operator[] (int index)
{
  int i;
  ListNode *ptr;

  for(i = 0, ptr = head; ptr && i < index; i++, ptr = ptr->next);

  return ptr->directory;
} // operator[]


LinkedList& LinkedList::operator+= (Directory *directory)
{
  ListNode *ptr, *prev = NULL;

  for(ptr = head; ptr && *(ptr->directory) < *directory; ptr = ptr->next)
    prev = ptr;

  if(!prev)
    head = new ListNode(directory, head);
  else // prev exists
    prev->next = new ListNode(directory, ptr);

  return *this;
} // operator+=


/*
LinkedList& LinkedList::operator= (const LinkedList &linkedList)
{
  if(this == &linkedList)
    return *this;

  ListNode *ptr, *ptr2;

  for(ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } // for each ListNode

  if(linkedList.head)
  {
    head = new ListNode(new Directory(*(linkedList.head->directory)), NULL);
    ptr = head;
    for(ptr2 = linkedList.head->next; ptr2; ptr2 = ptr2->next)
    {
      ptr->next = new ListNode(new Directory(*(ptr2->directory)), NULL);
      ptr = ptr->next;
    } // for each node in linkedList
  } // if entries in linkedList
  else
    head = NULL;

  return *this;

} // operator=
 */
