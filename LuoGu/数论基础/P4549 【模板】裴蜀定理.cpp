#include <iostream>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    int g;
    cin >> g;
    g = abs(g);
    for (int i = 1, t; i < n; ++i)
        cin >> t, g = __gcd(g, abs(t));
    cout << g << endl;
}

int main()
{
    int t = 1;
    //	cin >> t;
    while (t--)
        solve();
    return 0;
}
