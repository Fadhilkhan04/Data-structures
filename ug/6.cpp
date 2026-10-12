#include <iostream>
using namespace std;

int rear = -1;
int front = 0;
void enqueue(int queue[], int n, int size)
{
  if (rear == size - 1)
  {
    cout << "queue overflow." << endl;
  }
  else
  {
    rear++;
    queue[rear] = n;
  }
}

void dequeue(int queue[], int size)
{
  if (rear == -1)
  {
    cout << "queue underflow";
  }
  else
  {
    cout << "the element deleted from the queue is :" << queue[front] << endl;
    front++;

    if (front > rear)
    {
      rear = -1;
      front = 0;
    }
  }
}
void peek(int queue[])
{
  if (rear == -1)
  {
    cout << "queue is empty" << endl;
  }
  else
  {
    cout << "the element which is at front container :" << queue[front] << endl;
  }
}
void display(int queue[])
{
  if (rear == -1)
  {
    cout << "queue is empty please enter elements." << endl;
  }
  else
  {
    cout << "the elements in queue are:" << endl;
    for (int i = front; i <= rear; i++)
    {
      cout << queue[i] << " ";
    }
  }
}

int main()
{
  int size, ch, n;
  cout << "Enter the size of the Queue:" << endl;
  cin >> size;
  int queue[size];
  while (true)
  {
    cout << endl;
    cout << "----------- Queue Operation -----------" << endl;
    cout << "1. Enqueue." << endl;
    cout << "2. Dequeue." << endl;
    cout << "3. peek." << endl;
    cout << "4. display" << endl;
    cout << "5. exit" << endl;
    cout << "Enter choice: ";

    cin >> ch;

    if (ch == 1)
    {
      cout << "Enter the element you want to push in the queue:" << endl;
      cin >> n;
      enqueue(queue, n, size);
      continue;
    }
    else if (ch == 2)
    {
      dequeue(queue, size);
      continue;
    }
    else if (ch == 3)
    {
      peek(queue);
      continue;
    }
    else if (ch == 4)
    {
      display(queue);
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