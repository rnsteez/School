//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#include "linkedlist.h"
#include "directory.h"

ListNode::ListNode(Directory *Dir, ListNode *nex): directory(Dir), next(nex)
{} // ListNode()


ListNode::ListNode(const ListNode &rhs)
{
  directory = new Directory(*rhs.directory);
  if (rhs.next)
    next = new ListNode(*rhs.next);
} // Copy constructor


ListNode::~ListNode()
{
  delete directory;
  if (!next)
    delete next;
} // ~ListNode()


LinkedList::LinkedList (): head(NULL)
{} // LinkedList()


LinkedList::~LinkedList ()
{
  if(head)
    delete head;
} // ~LinkedList()


void LinkedList::insert(Directory *Dir)
{
  ListNode *ptr = head;
  ListNode *prev = ptr;
  
  if (!ptr)
  {
    head = new ListNode(Dir);
  }
  else // Not an empty list
  {
    for (ptr = ptr->next; ptr && *ptr->directory < *Dir; ptr = ptr->next)
    {
      prev = ptr;
    }
    if (prev == head && !(*head->directory < *Dir))
      head = new ListNode(Dir, head);
    else // not an insert at the front
      prev->next = new ListNode(Dir, ptr);
  }
} // insert()


Directory* LinkedList::operator[] (int index)
{
  ListNode *ptr = head;
  for (int i = 0; i < index; i++)
    ptr = ptr->next;
  return ptr->directory;
} // operator[]


Directory* LinkedList::operator[] (int index) const
{
  ListNode *ptr = head;
  for (int i = 0; i < index; i++)
    ptr = ptr->next;
  return ptr->directory;
} // operator[] const


void LinkedList::operator+= (Directory *Dir)
{
  insert(Dir);
} // operator+=


void LinkedList::operator= (LinkedList &rhs)
{
  head = new ListNode(*rhs.head);     
} // operator=