#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    rd0(arr);
    int cnt = 0;
    for (auto &p : arr)
        cnt += p == 0;
    if (cnt == 0)
        cout << "YES" << endl << string(n, 'A') << endl;
    else if (cnt == 1)
        cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;
        bool first = true;
        for (auto &p : arr)
            cout << (p != 0 ? 'C' : (first ? first = false, 'A' : 'B'));
        cout << endl;
    }
}
