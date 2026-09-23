#include <ihxnan>

vvl mul(vvl a, vvl b)
{
    vvl res(4, vl(4));
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod;
    return res;
}

vvl qmi(vvl a, ll b)
{
    vvl res(4, vl(4));
    for (int i = 0; i < 4; ++i)
        res[i][i] = 1;
    for (; b; b >>= 1, a = mul(a, a))
        if (b & 1)
            res = mul(res, a);
    return res;
}

void solve()
{
    ll n, r;
    cin >> n >> r;
    vl dp{1, 1, 0, 1};

    vvl base{{1, 1, 0, 1}, {1, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 1, 1}};
    base = qmi(base, n - 1);

    vl ans(4);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ans[i] += dp[j] * base[i][j];

    cout << ans[r] % mod << endl;
}
