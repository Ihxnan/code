#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    ll x;
    cin >> x;
    bitset<64> b(x);
    int cnt = 0;
    for (int i = 0; i < 64; ++i)
        cnt += b[i];
    if (cnt == 0)
        return cout << "0 -1 -1" << endl, void();
    cout << cnt << ' ';
    for (int i = 0; i < 64; ++i)
        if (b[i])
        {
            cout << i << ' ';
            break;
        }

    for (int i = 63; i >= 0; --i)
        if (b[i])
        {
            cout << i << endl;
            break;
        }
}
