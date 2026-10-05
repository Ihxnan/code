#include <ihxnan>

void solve()
{
    int l, d;
    cin >> l >> d;
    int t[3];
    for (int i = 0; i < 3; i++)
        cin >> t[i];

    string str;
    cin >> str;

    vvl dp(l + 1, vl(4, -1));

    auto dfs = [&](auto &&self, int idx, int remain) -> ll {
        if (idx >= l)
            return 0;

        if (dp[idx][remain] != -1)
            return dp[idx][remain];

        ll ans = lINF;
        if (remain)
            ans = min(ans, self(self, idx + d, remain - 1));

        return dp[idx][remain] = min(ans, self(self, idx + 1, remain) + t[str[idx] - '0']);
    };

    cout << dfs(dfs, 0, 3) << endl;
}
