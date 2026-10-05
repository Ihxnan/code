#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    cin >> n >> k;
    int len = log2(k);
    vl cnt(len + 1);
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        for (int j = 0; j <= len; ++j)
            cnt[j] += t / (1 << j);
    }
    for (int i = 0; i <= len; ++i)
        if (cnt[i] % 2)
            return cout << "Alice" << endl, void();
    cout << "Bob" << endl;
}
