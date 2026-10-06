#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
  int choice;

  cout << "1. Numbers" << endl;
  cout << "2. Strings" << endl;
  cout << "Enter your choice: ";
  cin >> choice;

  if (choice == 1)
  {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int a[100], dp[100];

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
    {
      cin >> a[i];
      dp[i] = 1;
    }

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j < i; j++)
      {
        if (a[i] > a[j])
          dp[i] = max(dp[i], dp[j] + 1);
      }
    }

    int longest = 0;

    for (int i = 0; i < n; i++)
      longest = max(longest, dp[i]);

    cout << "Longest Ascending Subsequence Length: "
         << longest << endl;
  }

  else if (choice == 2)
  {
    int n;
    cout << "Enter number of strings: ";
    cin >> n;

    string a[100];
    int dp[100];

    cout << "Enter the strings: ";
    for (int i = 0; i < n; i++)
    {
      cin >> a[i];
      dp[i] = 1;
    }

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j < i; j++)
      {
        if (a[i] > a[j])
          dp[i] = max(dp[i], dp[j] + 1);
      }
    }

    int longest = 0;

    for (int i = 0; i < n; i++)
      longest = max(longest, dp[i]);

    cout << "Longest Ascending Subsequence Length: "
         << longest << endl;
  }

  else
  {
    cout << "Invalid choice!" << endl;
  }

  return 0;
}