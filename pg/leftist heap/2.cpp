#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
  int data, npl;
  Node *left;
  Node *right;
};

Node *root = nullptr;

int getNpl(Node *node)
{
  if (node == nullptr)
  {
    return -1;
  }
  return node->npl;
}

Node *merge(Node *a, Node *b)
{
  if (a == nullptr)
  {
    return b;
  }
  if (b == nullptr)
  {
    return a;
  }
  if (a->data > b->data)
  {
    swap(a, b);
  }
  a->right = merge(a->right, b);
  if (getNpl(a->left) < getNpl(a->right))
  {
    swap(a->left, a->right);
  }
  a->npl = getNpl(a->right) + 1;

  return a;
}

void insert(int x)
{
  Node *newNode = new Node();
  newNode->data = x;
  newNode->npl = 0;
  newNode->left = nullptr;
  newNode->right = nullptr;

  root = merge(newNode, root);
}

void deleteNode()
{
  if (root == nullptr)
  {
    cout << "heap is empty";
    return;
  }

  cout << "the node deleted is :" << root->data;
  Node *temp = root;
  root = merge(root->left, root->right);
  delete temp;
}

void display(Node *root, int level = 0)
{
  if (root == nullptr)
  {
    return;
  }
  display(root->right, level + 1);

  for (int i = 0; i < level; i++)
  {
    cout << "   ";
  }
  cout << root->data << endl;

  display(root->left, level + 1);
}