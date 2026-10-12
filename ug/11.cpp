#include <iostream>
using namespace std;

void bubble_Sort(int mynum[], int size)
{

  int i, j, swap, temp;

  for (i = 0; i < size; i++)
  {
    swap = 0;

    for (j = 0; j < size - i - 1; j++)
    {
      if (mynum[j] > mynum[j + 1])
      {
        temp = mynum[j];
        mynum[j] = mynum[j + 1];
        mynum[j + 1] = temp;

        swap = 1;
      }
    }
    if (swap == 0)
    {
      return;
    }
  }
}

void selection_Sort(int mynum[], int size)
{

  int i, j, minidx, minval, temp;

  for (i = 0; i < size; i++)
  {

    minval = mynum[i];
    minidx = i;

    for (j = i + 1; j < size; j++)
    {
      if (mynum[j] < minval)
      {
        minval = mynum[j];
        minidx = j;
      }
    }
    // swapping
    temp = mynum[i];
    mynum[i] = mynum[minidx];
    mynum[minidx] = temp;
  }
}

void insertion_Sort(int mynum[], int size)
{

  int i, value, index;

  for (i = 1; i < size; i++)
  {

    value = mynum[i];
    index = i;

    while (index > 0 && mynum[index - 1] > value)
    {
      mynum[index] = mynum[index - 1];
      index--;
    }

    mynum[index] = value;
  }
}

int main()
{

  int size, ch;

  cout << "Enter size of array: ";
  cin >> size;

  int mynum[size];

  for (int i = 0; i < size; i++)
  {
    cout << "Enter item " << i + 1 << " : ";
    cin >> mynum[i];
  }

  cout << "Before Sorting: " << endl;
  for (int i = 0; i < size; i++)
    cout << mynum[i] << " ";
  cout << endl;

  cout << "--------- Sorting Methods ---------" << endl;
  cout << "1. Bubble Sort" << endl;
  cout << "2. Selection Sort" << endl;
  cout << "3. Insertion Sort" << endl;
  cout << "Enter choice: ";
  cin >> ch;

  if (ch == 1)
  {
    bubble_Sort(mynum, size);
  }
  else if (ch == 2)
  {
    selection_Sort(mynum, size);
  }
  else if (ch == 3)
  {
    insertion_Sort(mynum, size);
  }

  cout << "After Sorting: " << endl;
  for (int i = 0; i < size; i++)
    cout << mynum[i] << " ";
  cout << endl;
  cout << "Fadhilkhan" << endl;
  cout << "RRN : 220071601060" << endl;
  cout << "B.Tech CSE - A" << endl;

  return 0;
}