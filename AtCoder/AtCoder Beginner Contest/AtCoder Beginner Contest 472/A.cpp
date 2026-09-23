#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    string str;
    cin >> str;
    for (auto &p : str)
        if (p == 'A')
            cout << 'A';
        else
            cout << '.';
}
