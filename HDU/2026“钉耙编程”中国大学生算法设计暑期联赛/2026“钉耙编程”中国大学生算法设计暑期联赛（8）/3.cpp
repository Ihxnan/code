#include <ihxnan>
#include <Comb>

ll memo[100001][317];

int init = [] {
    memset(memo, -1, sizeof memo);
    return cin >> t, 0;
}();

ll f(int n, int k)
{
    if (n <= 0)
        return 1;
    if (memo[n][k] != -1)
        return memo[n][k];
    return memo[n][k] = (f(n - 1, k) + f(n - k, k)) % mod;
}

Comb comb(mod);

ll g(int n, int k)
{
    ll ans = 1;
    for (int i = 1; (i - 1) * (k - 1) < n; ++i)
        ans = (ans + comb.C(n - (i - 1) * (k - 1), i)) % mod;
    return ans;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    for (int i = 0, x, k; i < q; ++i)
    {
        cin >> x >> k;
        if (k < 317)
            cout << (f(n, k) - f(x - k, k) * f(n - x - k + 1, k) % mod + mod) % mod << endl;
        else
            cout << (g(n, k) - g(x - k, k) * g(n - x - k + 1, k) % mod + mod) % mod << endl;
    }
}
