// Kristopher Acuna (5005035589)
// CS302 - 1004

#include <iostream>
#include <string>

template <typename T> class LL {
  // contents of each node
  struct node {
    T data;
    node *prev;
    node *next;
  };
  // iterator class to allow access of each node in main
public:
  class Iterator {
  public:
    friend class LL;
    Iterator();
    Iterator(node *);
    T operator*() const;
    Iterator operator++(int);
    Iterator operator++();
    Iterator operator--(int);
    Iterator operator--();
    bool operator==(const Iterator &) const;
    bool operator!=(const Iterator &) const;

  private:
    node *current;
  };

  LL();
  LL(const LL<T> &);
  const LL<T> &operator=(const LL<T> &);
  ~LL();
  void headInsert(const T &);
  void tailInsert(const T &);
  void headRemove();
  bool isEmpty() const;
  std::size_t size() const;
  Iterator begin() const;
  Iterator end() const;

private:
  node *portal;
};

// iterator class implementation
template <typename T> LL<T>::Iterator::Iterator() {
  current = nullptr;
  // sets current with nullptr
}

template <typename T> LL<T>::Iterator::Iterator(node *ptr) {
  current = ptr;
  // sets current equal to ptr
}

template <typename T> T LL<T>::Iterator::operator*() const {
  return current->data;
  // overloads dereference operator, returns data
}

// ----------------------------------------------------------------
// DONT DO THIS it2=it++; or it2 = ++it

// POSTFIX
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++(int) {
  current = current->next;
  return *this;
}

// PREFIX
template <typename T> typename LL<T>::Iterator LL<T>::Iterator::operator++() {
  current = current->next;
  return *this;
}

// POSTFIX
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--(int) {
  current = current->prev;
  return *this;
}

// PREFIX
template <typename T> typename LL<T>::Iterator LL<T>::Iterator::operator--() {

  current = current->prev;
  return *this;
}

// --------------------- COMPARISON OPERATORS -------------------
template <typename T>
bool LL<T>::Iterator::operator==(const Iterator &rhs) const {
  if (this->current == rhs.current) {
    return true;
  } else {
    return false;
  }
  // The Comparison Operator
  // Compares if *this Iterator and RHS Iterator point to same node, if they
  // dont, return true
}

template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator &rhs) const {
  if (this->current != rhs.current) {
    return true;
  } else {
    return false;
  }
  // The Comparison Operator
  // Compares if *this Iterator and RHS Iterator point to same node, if they
  // dont, return false
}

// ======================================================================================

// Linked list class implementation
template <typename T> LL<T>::LL() {

  node *tempPortal = new node();

  portal = tempPortal;
  portal->prev = portal;
  portal->next = portal;
}

// copy constructor
template <typename T> LL<T>::LL(const LL<T> &copy) {
  // perform the deep copy here
  portal = new node;
  portal->prev = portal;
  portal->next = portal;

  auto it = copy.begin();
  while (it != copy.end()) {
    tailInsert(*it);
    ++it;
  }
}

//-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename T> const LL<T> &LL<T>::operator=(const LL<T> &rhs) {
  if (this != &rhs) {
    while (!isEmpty()) {
      headRemove();
    }
    auto findCheck = rhs.begin();
    while (findCheck != rhs.end()) {
      tailInsert(*findCheck);
      ++findCheck;
    }
  }
  return *this;
}
//-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// destructor
template <typename T> LL<T>::~LL() {
  while (!isEmpty()) {
    headRemove();
  }
  delete portal;
}

// head insert
template <typename T> void LL<T>::headInsert(const T &item) {
  // case - headInsert(7);
  // create a dummy node
  // portal = new node; ???
  if (portal->next == portal) {
    node *tmp = new node; // creates temp node [  |   |  ]
    tmp->data = item;     // inserts 7 into dummy node
    portal->next = tmp;   //
    portal->prev = tmp;   // points back to tail node of linked list
    tmp->next = portal;   // set to point to dummy node
    tmp->prev = portal;
  } else {
    node *tmp = new node; // creates new node that *tmp pointer points at
    tmp->data = item;     // assigns (item) into data field
    tmp->next = portal->next;
    portal->next->prev = tmp; // portal->next is address of node // gets first
                              // node we derefernece by getting the nodes
                              // previous field and set it to tmp
    tmp->prev = portal;       // points tmp node to portal
    portal->next = tmp;       // points portal to tmp
  }
}

// tail insert
template <typename T> void LL<T>::tailInsert(const T &item) {
  if (portal->next == portal) {
    headInsert(item);
  } else {
    node *tmp = new node;
    tmp->data = item;
    tmp->next = portal;
    portal->prev->next = tmp;
    tmp->prev = portal->prev;
    portal->prev = tmp;
  }
}

//-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename T> void LL<T>::headRemove() {
  node *tmp;

  if (isEmpty()) {
    return;
  } else if (isEmpty() == false) {
    tmp = portal->next;          // create temp ptr to store head
    portal->next = tmp->next;    // point head ptr to point to next node on list
    tmp->next->prev = tmp->next; // reallocate next ptr of
                                 // tail to point to new head
    delete tmp;
  }
}
//-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <typename T> bool LL<T>::isEmpty() const {
  // return portal == nullptr;
  if (portal->next == portal) {
    return true;
  } else if (portal->next != portal) {
    return false;
  }
  // checks if empty
}

template <typename T> std::size_t LL<T>::size() const {
  node *checkCurrent; // instantiate node
  checkCurrent = portal->next;

  size_t checkCounter = 0;
  while (checkCurrent != portal) {
    checkCurrent = checkCurrent->next;
    checkCounter++;
  }
  return checkCounter;
}

template <typename T> typename LL<T>::Iterator LL<T>::begin() const {
  Iterator i;               // creates i
  i.current = portal->next; // assigns current into i
  return i;                 // return iterator
}

template <typename T> typename LL<T>::Iterator LL<T>::end() const {
  Iterator i; // create iterator i
  i = portal; // assign portal into i
  return i;   // return iterator
}

// Iterator Class
// LL<int> list;
// list.headInsert(4);
// list.headInsert(7);
// list.headInsert(3);
// list.headInsert(10);
//             <-----
// [10]<->[3]<->[7]<->[4]<->[portal]
//             ----->

// ==============================

// for(it=list.begin(); it != list.end(); it++) // once you hit the dummy node
// youre done