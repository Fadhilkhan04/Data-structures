#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *next;
};

Node *createNode(int value)
{
  Node *newNode = new Node();

  newNode->data = value;
  newNode->next = NULL;
  return newNode;
}
