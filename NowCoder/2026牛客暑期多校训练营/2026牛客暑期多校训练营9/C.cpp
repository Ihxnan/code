#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;

    map<int, int> hash;
    for (int i = 0, t; i < n; ++i)
        cin >> t, ++hash[t];
    auto tmp = hash;

    if (hash[0] != 1 && hash[0] != 3)
        return cout << 0 << endl, void();

    for (int i = n + 2; i >= 1; --i)
        hash[i] += (hash[i + 1] + (hash[i + 2] + hash[i + 1] / 2 + hash[i + 1] % 2) / 2) / 2;

    if (hash[0] == 1 && hash[1] > 1 || hash[0] == 3 && hash[1] > 0)
        cout << 0 << endl;
    else
    {
        int ans = 0;
        for (auto &[k, v] : tmp)
            ans += ans == k;
        cout << ans << endl;
    }
}
