#include <iostream>
using namespace std;

void push(int *stack, int n, int size, int top)
{
  if (top >= size)
  {
    cout << "stack overflow" << endl;
  }
  else
  {
    *(stack + top) = n;
    cout << "element successfully entered" << endl;
  }
}
void pop(int stack[], int size, int top)
{
  if (top >= 0)
  {
    int item;
    item = stack[top];
    cout << "the element removed from the stack is:" << item << endl;
  }
  else
  {
    cout << "stack underflow" << endl;
  }
}
void peek(int stack[], int top)
{
  cout << "the top most element is:" << stack[top] << endl;
}
void display(int stack[], int top)
{
  if (top >= 0)
  {
    int i;
    cout << "the elements are:" << endl;
    for (i = 0; i <= top; i++)
    {
      cout << stack[i] << " ";
    }
  }
  else
  {
    cout << "stack is empty please enter the elements." << endl;
  }
}
int main()
{
  int size, ch, n;
  int top = -1;
  cout << "Enter the size of the stack:" << endl;
  cin >> size;
  int stack[size];
  while (true)
  {
    cout << endl;
    cout << "----------- Stack Operation -----------" << endl;
    cout << "1. push." << endl;
    cout << "2. pop." << endl;
    cout << "3. peek." << endl;
    cout << "4. display" << endl;
    cout << "5. exit" << endl;
    cout << "Enter choice: ";

    cin >> ch;

    if (ch == 1)
    {
      cout << "Enter the element you want to push in the stack:" << endl;
      cin >> n;
      top++;
      push(stack, n, size, top);
      continue;
    }
    else if (ch == 2)
    {
      pop(stack, size, top);
      top--;
      continue;
    }
    else if (ch == 3)
    {
      peek(stack, top);
      continue;
    }
    else if (ch == 4)
    {
      display(stack, top);
      continue;
    }
    else if (ch == 5)
    {
      cout << "Fadhilkhan" << endl;
      cout << "RRN : 220071601060" << endl;
      cout << "B.Tech CSE - A" << endl;
      break;
    }
    else
    {
      cout << endl
           << "Invalid choice try again." << endl
           << endl;
      continue;
    }
    return 0;
  }
}