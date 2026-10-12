#include <iostream>
using namespace std;

int main()
{

  string text;
  int i;

  cout << "Enter a text: " << endl;
  cin >> text;
  cout << text[0];

  for (i = 1; i < text.length() && text[i] != '\0'; i++)
  {
    if (text[i] == text[i - 1] + 1)
    {
      cout << text[i];
    }
    else
    {
      cout << endl
           << text[i];
    }
  }

  cout << "Fadhilkhan" << endl;
  cout << "RRN : 220071601060" << endl;
  cout << "B.Tech CSE - A" << endl;
  return 0;
}