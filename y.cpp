#include <iostream>
using namespace std;

int count=10;

int main()
{
    cout<<::count;
    int a[100], count;
    cin >> count;
    cout<<count;
    cout<<::count<<endl;
    cin>>::count;
    cout<<::count;

    return 1;
}