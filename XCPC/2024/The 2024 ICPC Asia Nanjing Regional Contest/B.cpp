#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    string str;
    cin >> str;
    for (auto &p : str)
        p ^= 48;
    for (int i = 0; i < str.size(); i += 2)
        if (str[i] != 2)
            str[i] ^= 1;

    vi cnt(3);
    for (auto &p : str)
        ++cnt[p];

    int ans = abs(cnt[0] - cnt[1]) - cnt[2];
    if (ans >= 0)
        cout << ans << endl;
    else
        cout << (-ans & 1) << endl;
}
