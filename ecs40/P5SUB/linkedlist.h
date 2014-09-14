//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef LINKEDLIST_H
  #define	LINKEDLIST_H

#include <cstdlib>

class Directory;

class ListNode
{
  Directory *directory;
  ListNode *next;
  
  friend class LinkedList;
  ListNode(Directory *Dir, ListNode *next = NULL);
  ListNode(const ListNode &rhs);
  ~ListNode ();
}; // class ListNode

class LinkedList
{
  ListNode *head;
public:
  LinkedList ();
  ~LinkedList ();
  void insert (Directory *Dir);
  Directory* operator[] (int index);
  Directory* operator[] (int index) const;
  void operator+= (Directory *Dir);
  void operator= (LinkedList &rhs);
}; // class LinkedList

#endif	// LINKEDLIST_H 

