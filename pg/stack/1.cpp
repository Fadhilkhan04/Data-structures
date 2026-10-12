#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *next;
};

Node *top = nullptr;

void push(int value)
{
  Node *newNode = new Node();

  newNode->data = value;
  newNode->next = top;
  top = newNode;
}

void pop()
{
  if (top == nullptr)
  {
    cout << "stack underflow";
    return;
  }
  Node *temp = top;
  cout << "deleted element is :" << top->data;
  top = top->next;
  delete temp;
}
void peek()
{
  if (top == nullptr)
    cout << "Stack is empty\n";
  else
    cout << "Top element: " << top->data << endl;
}

void display()
{
  if (top == nullptr)
  {
    cout << "stack underfloe";
  }
  else
  {
    Node *temp = top;
    while (temp != nullptr)
    {
      cout << temp->data << " ";
      temp = temp->next;
    }
  }
}
int main()
{
  int ch, n;

  while (true)
  {
    cout << "\n1.Push  2.Pop  3.Peek  4.Display  5.Exit\n";
    cout << "Enter choice: ";
    cin >> ch;

    switch (ch)
    {
    case 1:
      cout << "Enter element: ";
      cin >> n;
      push(n);
      break;

    case 2:
      pop();
      break;

    case 3:
      peek();
      break;

    case 4:
      display();
      break;

    case 5:
      return 0;

    default:
      cout << "Invalid choice\n";
    }
  }
}