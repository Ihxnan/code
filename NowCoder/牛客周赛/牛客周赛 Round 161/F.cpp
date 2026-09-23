#include <ihxnan>

void solve()
{
    int n, k, x;
    cin >> n >> k >> x;

    if (k == 0 && x == 0)
        return cout << 1 << endl, void();

    if (k == 0)
        return cout << 0 << endl, void();

    vi a(n / 2), b((n + 1) / 2);
    rd0(a);
    rd0(b);
    vector<unordered_map<int, int>> pre(a.size() + 2), suf(b.size() + 2);

    auto dfs = [&](auto &&self, int pos, int cnt, int sum, vi &arr, auto &hash) -> ll {
        if (pos == arr.size())
            return sum == x && cnt == k;
        ++hash[cnt + 1][sum ^ arr[pos]];
        return (self(self, pos + 1, cnt, sum, arr, hash) + self(self, pos + 1, cnt + 1, sum ^ arr[pos], arr, hash)) %
               MOD;
    };

    ll ans = (dfs(dfs, 0, 0, 0, a, pre) + dfs(dfs, 0, 0, 0, b, suf)) % MOD;

    for (int i = 1; i < k && i < pre.size(); ++i)
        for (auto &[sum, times] : pre[i])
            if (k - i > 0 && k - i < suf.size())
                ans = (ans + times * suf[k - i][x ^ sum]) % MOD;

    cout << ans << endl;
}
