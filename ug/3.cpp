#include <iostream>
using namespace std;

void display(int mynum[], int i, int n)
{
  for (i = 0; i < n; i++)
  {
    cout << mynum[i] << " ";
  }
}
void insert(int mynum[], int n, int num, int pos)
{
  int i;
  n++;
  for (i = n; i >= pos; i--)
  {
    mynum[i] = mynum[i - 1];
  }
  mynum[pos - 1] = num;
}

void Delete(int mynum[], int n, int x)
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (i + 1 == x)
    {
      break;
    }
  }
  if (i < n)
  {
    for (int j = i; j < n; j++)
    {
      mynum[j] = mynum[j + 1];
    }
  }
}

int main()
{
  int n, i, size, ch, num, pos, x;
  cout << "Enter the size of the array : ";
  cin >> size;
  cout << "Enter the number of elements in the array : ";
  cin >> n;
  int mynum[size];
  cout << "Enter the elements of the array : " << endl;
  for (i = 0; i < n; i++)
  {
    cin >> mynum[i];
  }

  while (true)
  {
    cout << endl;
    cout << "----------- Array Operation -----------" << endl;
    cout << "1. Display Array." << endl;
    cout << "2. Insert Array." << endl;
    cout << "3. Delete Array." << endl;
    cout << "4. Exit" << endl;
    cout << "Enter choice: ";

    cin >> ch;

    if (ch == 1)
    {

      display(mynum, i, n);
      continue;
    }
    else if (ch == 2)
    {

      cout << endl
           << "Enter element to insert: ";
      cin >> num;

      cout << "Enter the position you want to insert in: ";
      cin >> pos;
      cout << endl;

      insert(mynum, n, num, pos);
      n++;
      continue;
    }
    else if (ch == 3)
    {

      cout << endl
           << "Enter position you want to delete in: ";
      cin >> x;

      Delete(mynum, n, x);
      n--;
      cout << endl;
      continue;
    }
    else if (ch == 4)
    {
      cout << "Fadhilkhan" << endl;
      cout << "RRN : 220071601060" << endl;
      cout << "B.Tech CSE - A" << endl;
      break;
    }
    else
    {

      cout << endl
           << "Invalid choice" << endl
           << endl;
      continue;
    }

    return 0;
  }
}
