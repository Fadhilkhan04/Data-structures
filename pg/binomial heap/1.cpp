#include <iostream>
using namespace std;

struct Node
{
  int data, degree;
  Node *parent, *child, *sibling;
};

Node *head = nullptr;

Node *createNode(int x)
{
  Node *temp = new Node;

  temp->data = x;
  temp->degree = 0;
  temp->parent = nullptr;
  temp->child = nullptr;
  temp->sibling = nullptr;

  return temp;
}

// Join two binomial trees of the same degree
void linkTrees(Node *a, Node *b)
{
  if (a->data > b->data)
  {
    Node *temp = a;
    a = b;
    b = temp;
  }

  b->parent = a;
  b->sibling = a->child;
  a->child = b;

  a->degree++;
}

// Merge root lists in increasing order of degree
Node *mergeLists(Node *a, Node *b)
{
  if (a == nullptr)
    return b;

  if (b == nullptr)
    return a;

  Node *newHead = nullptr;
  Node *tail = nullptr;

  while (a != nullptr && b != nullptr)
  {
    Node *temp;

    if (a->degree <= b->degree)
    {
      temp = a;
      a = a->sibling;
    }
    else
    {
      temp = b;
      b = b->sibling;
    }

    if (newHead == nullptr)
    {
      newHead = temp;
      tail = temp;
    }
    else
    {
      tail->sibling = temp;
      tail = temp;
    }
  }

  if (a != nullptr)
    tail->sibling = a;
  else
    tail->sibling = b;

  return newHead;
}

// Combine trees having the same degree
Node *unionHeap(Node *a, Node *b)
{
  Node *newHead = mergeLists(a, b);

  if (newHead == nullptr)
    return nullptr;

  Node *prev = nullptr;
  Node *curr = newHead;
  Node *next = curr->sibling;

  while (next != nullptr)
  {
    if (curr->degree != next->degree ||
        (next->sibling != nullptr &&
         next->sibling->degree == curr->degree))
    {

      prev = curr;
      curr = next;
    }
    else
    {
      if (curr->data <= next->data)
      {
        curr->sibling = next->sibling;
        linkTrees(curr, next);
      }
      else
      {
        if (prev == nullptr)
          newHead = next;
        else
          prev->sibling = next;

        linkTrees(next, curr);
        curr = next;
      }
    }

    next = curr->sibling;
  }

  return newHead;
}

void insert(int x)
{
  Node *temp = createNode(x);
  head = unionHeap(head, temp);
}

// Delete the minimum element
void deleteMin()
{
  if (head == nullptr)
  {
    cout << "Heap is empty\n";
    return;
  }

  Node *minNode = head;
  Node *minPrev = nullptr;

  Node *curr = head;
  Node *prev = nullptr;

  while (curr != nullptr)
  {
    if (curr->data < minNode->data)
    {
      minNode = curr;
      minPrev = prev;
    }

    prev = curr;
    curr = curr->sibling;
  }

  cout << "Deleted element: " << minNode->data << endl;

  if (minPrev == nullptr)
    head = minNode->sibling;
  else
    minPrev->sibling = minNode->sibling;

  Node *child = minNode->child;
  Node *revHead = nullptr;

  while (child != nullptr)
  {
    Node *next = child->sibling;

    child->parent = nullptr;
    child->sibling = revHead;
    revHead = child;

    child = next;
  }

  head = unionHeap(head, revHead);

  delete minNode;
}

bool search(Node *node, int x)
{
  if (node == nullptr)
    return false;

  if (node->data == x)
    return true;

  return search(node->child, x) ||
         search(node->sibling, x);
}

// Display the binomial trees
void display(Node *node, int level = 0)
{
  while (node != nullptr)
  {
    for (int i = 0; i < level; i++)
      cout << "    ";

    cout << node->data
         << " (B" << node->degree << ")" << endl;

    display(node->child, level + 1);

    node = node->sibling;
  }
}

int main()
{
  int choice, x;

  while (true)
  {
    cout << "\n1. Insert"
         << "\n2. Delete Minimum"
         << "\n3. Display"
         << "\n4. Search"
         << "\n5. Exit\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter element: ";
      cin >> x;
      insert(x);
      break;

    case 2:
      deleteMin();
      break;

    case 3:
      if (head == nullptr)
        cout << "Heap is empty\n";
      else
        display(head);
      break;

    case 4:
      cout << "Enter element to search: ";
      cin >> x;

      if (search(head, x))
        cout << "Element found\n";
      else
        cout << "Element not found\n";
      break;

    case 5:
      return 0;

    default:
      cout << "Invalid choice\n";
    }
  }
}
