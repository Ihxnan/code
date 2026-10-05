#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi l(n), r(n);
    for (auto &p : l)
        cin >> p;
    for (auto &p : r)
        cin >> p;
    vi sta(n);
    for (int i = 0; i < n; ++i)
        if (l[i] == r[i])
            sta[i] = l[i];
        else if (r[i] - l[i] > 1)
            sta[i] = -1;

    vector<map<pii, ll>> memo(n);

    auto dfs = [&](auto &&self, int pos, int last, int len) -> ll {
        if (pos == n)
            return 0;

        if (memo[pos].count({last, len}))
            return memo[pos][{last, len}];

        if (sta[pos] == -1)
            return memo[pos][{last, len}] = 1 + self(self, pos + 1, -1, 0);

        if (sta[pos] > 0)
        {
            if (sta[pos] == last)
                return memo[pos][{last, len}] = 2 * len + 1 + self(self, pos + 1, last, len + 1);
            return memo[pos][{last, len}] = 1 + self(self, pos + 1, sta[pos], 1);
        }

        ll ans = lINF;

        if (l[pos] == last)
            ans = min(ans, 2 * len + 1 + self(self, pos + 1, last, len + 1));
        else
            ans = min(ans, 1 + self(self, pos + 1, l[pos], 1));

        if (r[pos] == last)
            ans = min(ans, 2 * len + 1 + self(self, pos + 1, last, len + 1));
        else
            ans = min(ans, 1 + self(self, pos + 1, r[pos], 1));

        return memo[pos][{last, len}] = ans;
    };

    cout << dfs(dfs, 0, -1, 0) << endl;
}
