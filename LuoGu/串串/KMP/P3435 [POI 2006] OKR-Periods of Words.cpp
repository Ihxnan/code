#include <ihxnan>
#include <KMP>

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    str = '^' + str;
    ll ans = 0;
    vi nxt = NXT(str);
    for (int i = 1; i <= n; ++i)
    {
        int j = nxt[i];
        while (nxt[j] > 0)
            j = nxt[j];
        if (j)
            nxt[i] = j, ans += i - j;
    }
    cout << ans << endl;
}
