#include <iostream>

using namespace std;

int mygcd(int a, int b)
{
    return b ? mygcd(b, a % b) : a;
}

void solve()
{
    int a, b;
    cin >> a >> b;
    cout << mygcd(a, b);
}

int main()
{
    int t = 1;
    //	cin >> t;
    while (t--)
        solve();
    return 0;
}
