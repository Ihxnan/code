#include <ihxnan>
#include <KMP>

void solve()
{
    int n;
    cin >> n;
    string str;
    map<string, ll> memo;
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t;
        cin >> str;
        str = '^' + str;
        auto fail = get_fail(str);
        int res = t + 1;
        if (t % (t - fail.back()) == 0)
            res = t - fail.back();
        ++memo[str.substr(1, res)];
    }
    ll ans = 0;
    for (auto &[k, v] : memo)
        ans += v * v;
    cout << ans << endl;
}
