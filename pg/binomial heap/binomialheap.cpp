#include <iostream>
using namespace std;

struct Node
{
  int data, degree;
  Node *child;
  Node *parent;
  Node *sibling;
};

Node *head = nullptr;

Node *createNode(int x)
{
  Node *newNode = new Node();

  newNode->data = x;
  newNode->degree = 0;
  newNode->child = nullptr;
  newNode->parent = nullptr;
  newNode->sibling = nullptr;

  return newNode;
}

void linkTrees(Node *a, Node *b)
{
  if (a->data > b->data)
  {
    swap(a, b);
  }
  b->parent = a;
  b->sibling = a->child;
  a->child = b;

  a->degree++;
}

Node *mergedList(Node *a, Node *b)
{
  if (a == nullptr)
  {
    return b;
  }
  if (b == nullptr)
  {
    return a;
  }
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
  {
    tail->sibling = a;
  }
  else
  {
    tail->sibling = b;
  }
  return newHead;
}

Node *unionHeap(Node *a, Node *b)
{
}

void insert(int x)
{
  Node *temp = createNode(x);
  head = unionHeap(head, temp);
}