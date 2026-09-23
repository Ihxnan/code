#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    rd0(arr);
    int c0 = 0, c13 = 0, c2 = 0;
    for (auto &p : arr)
        if (p % 4 == 0)
            ++c0;
        else if (p % 4 == 2)
            ++c2;
        else
            ++c13;
    cout << max({c0, c13, c2}) << endl;
}
