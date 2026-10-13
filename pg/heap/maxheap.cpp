#include <iostream>
using namespace std;

int heap[100];
int n = 0;

void insert(int value)
{
  int i = n;
  heap[n] = value;
  n++;

  while (i > 0)
  {
    int parent = (i - 1) / 2;

    if (heap[i] > heap[parent])
    {
      swap(heap[i], heap[parent]);
      i = parent;
    }
    else
    {
      break;
    }
  }
}

void deleteNode()
{
  if (n == 0)
  {
    cout << "heap is empty";
    return;
  }
  cout << "deleted elemented is :" << heap[0];
  heap[0] = heap[n - 1];
  n--;

  int i = 0;

  while (2 * i + 1)
  {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = left;

    if (right < n && heap[right] > heap[left])
    {
      largest = right;
    }
    if (heap[i] < heap[largest])
    {
      swap(heap[i], heap[largest]);
      i = largest;
    }
    else
    {
      break;
    }
  }
}