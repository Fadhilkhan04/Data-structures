#include <iostream>
using namespace std;

void sum(int *a, int *b, int r, int c)
{
  int i, j;
  int sum[r][c];
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
    {
      sum[i][j] = *(a + i * c + j) + *(b + i * c + j);
    }
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
    {
      cout << sum[i][j] << "\t";
      if (j == c - 1)
      {
        cout << "\n\n";
      }
    }
}

void mult(int *a, int *b, int r, int c)
{
  int i, j, k;
  int mult[r][c];
  for (i = 0; i < r; i++)
  {
    for (j = 0; j < c; j++)
    {
      mult[i][j] = 0;
      for (k = 0; k < c; k++)
      {
        mult[i][j] += (*(a + ((i * c) + k))) * (*(b + ((k * c)) + j));
      }
    }
  }
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
    {
      cout << mult[i][j] << "\t";
      if (j == c - 1)
      {
        cout << "\n\n";
      }
    }
}

int main()
{

  int r, c, i, j, ch;
  cout << "enter the no of rows in the matrix :" << endl;
  cin >> r;
  cout << "enter the no of columns in the matrix :" << endl;
  cin >> c;

  int a[r][c], b[r][c];
  cout << "enter the elements of 1st matrix :" << endl;
  for (i = 0; i < r; i++)
  {
    for (j = 0; j < c; j++)
    {
      cout << "enter the element a" << i << j << endl;
      cin >> a[i][j];
    }
  }
  cout << "enter the elements of 2nd matrix :" << endl;
  for (i = 0; i < r; i++)
  {
    for (j = 0; j < c; j++)
    {
      cout << "enter the element b" << i << j << endl;
      cin >> b[i][j];
    }
  }

  while (true)
  {
    cout << endl;
    cout << "___________________" << endl;
    cout << "1.sum" << endl;
    cout << "2.multiplication" << endl;
    cout << "3.exit" << endl;
    cout << "enter your choice:";
    cin >> ch;

    if (ch == 1)
    {
      sum((int *)a, (int *)b, r, c);
      continue;
    }
    else if (ch == 2)
    {
      mult((int *)a, (int *)b, r, c);
      continue;
    }
    else if (ch == 3)
    {
      cout << "Fadhilkhan" << endl;
      cout << "RRN : 220071601060" << endl;
      cout << "B.Tech CSE - A" << endl;
      break;
    }
    else
    {
      cout << "invalid try again";
      continue;
    }
  }

  return 0;
}