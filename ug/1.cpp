#include <iostream>
using namespace std;

int main()
{
    int n, i, max, min;
    cout << "Enter the size of the array : ";
    cin >> n;
    int mynum[n];
    cout << "Enter the elements of the array : ";
    for (i = 0; i < n; i++)
        cin >> mynum[i];

    max = mynum[0];
    for (i = 0; i < n; i++)
    {
        if (max < mynum[i])
            max = mynum[i];
    }
    min = mynum[0];
    for (i = 0; i < n; i++)
    {
        if (min > mynum[i])
            min = mynum[i];
    }
    cout << "Largest element : " << max << endl;
    cout << "Smallest element : " << min << endl;

    cout << "Fadhilkhan" << endl;
    cout << "220071601060" << endl;
    return 0;
}
