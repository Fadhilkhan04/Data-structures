#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *next;
};

Node *front = nullptr;
Node *rear = nullptr;

void push(int value)
{
  Node *newNode = new Node();
  newNode->data = value;
  newNode->next = nullptr;
  if (front == nullptr)
  {
    front = rear = newNode;
  }
  else
  {
    rear->next = newNode;
    rear = newNode;
  }
}

void pop()
{
  if (front == nullptr)
  {
    cout << "queue empty";
    return;
  }
  Node *temp = front;
  cout << "deleted element is :" << front->data;
  front = front->next;
  if (front == nullptr)
  {
    rear = nullptr;
  }
  delete temp;
}
void peek()
{
  if (front == nullptr)
    cout << "Stack is empty\n";
  else
    cout << "Top element: " << front->data << endl;
}

void display()
{
  if (front == nullptr)
  {
    cout << "stack underfloe";
  }
  else
  {
    Node *temp = front;
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