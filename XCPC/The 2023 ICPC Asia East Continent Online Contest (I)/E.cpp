#include <ihxnan>

int init = [] { return cin >> t, 0; }();

vector<int> Bases{2, 3, 5, 7, 11, 13, 17, 19, 23};

ll mul(ll a, ll b, ll m)
{
    return lll(a) * b % m;
}

ll qmi(ll a, ll b, ll mod)
{
    ll res = 1;
    for (; b; b >>= 1, a = mul(a, a, mod))
        if (b & 1)
            res = mul(res, a, mod);
    return res;
}

bool is_prime(ll n)
{
    if (n < 2)
        return false;
    int s = __builtin_ctzll(n - 1);
    ll d = (n - 1) >> s;
    for (auto &p : Bases)
    {
        if (p == n)
            return true;
        ll x = qmi(p, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool ok = false;
        for (int i = 0; i < s - 1; ++i)
        {
            x = mul(x, x, n);
            if (x == n - 1)
            {
                ok = true;
                break;
            }
        }
        if (!ok)
            return false;
    }
    return true;
}

void func(int n)
{
    int cnt = 0;
    for (int i = 1; i <= n * n - n; ++i)
        for (int j = 1; j <= n * n - n; ++j)
            if (qmi(i, j, n) == qmi(j, i, n))
                ++cnt;
    cout << cnt << endl;
}

void solve()
{
    for (int i = 2; i <= 100; ++i)
        if (is_prime(i))
            gdb(i), func(i);
}
