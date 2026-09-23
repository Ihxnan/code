#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
#include <Comb>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
int sz;

void mul(vvl &a, vl &b)
{
    vl res(sz);
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
            res[i] = (res[i] + a[i][j] * b[j]);
    b = res;
}

void mul(vvl &a, vvl &b)
{
    vvl res(sz, vl(sz));
    for (int i = 0; i < sz; ++i)
        for (int k = 0; k < sz; ++k)
            if (a[i][k])
                for (int j = 0; j < sz; ++j)
                    res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod;
    a = res;
}

void qmi(vvl &a, int b)
{
    vvl res(sz, vl(sz));
    for (int i = 0; i < sz; ++i)
        res[i][i] = 1;
    for (; b; b >>= 1, mul(a, a))
        if (b & 1)
            mul(res, a);
    a = res;
}

Comb comb(mod);
void solve()
{
    int n, m;
    cin >> n >> m;
    sz = 1 << n - 2;

    if (n == 1)
    {
        cout << 3 * comb.qmi(2, m - 1) % mod << endl;
        return;
    }

    vi v(n);
    int dn = 0;
    vi k(n - 2);
    map<vi, int> hash;
    auto trans = [&]() -> void {
        vi memo(3, -1);
        memo[v[0]] = 0;
        memo[v[1]] = 1;
        for (auto &p : memo)
            if (p == -1)
                p = 2;
        for (int i = 0; i < n - 2; ++i)
            k[i] = memo[v[i + 2]];
    };

    auto bfs = [&](auto &&self, int pos) -> void {
        if (pos == n)
        {
            trans();
            if (!hash.count(k))
                hash[k] = dn++;
            return;
        }
        for (int i = 0; i < 3; ++i)
            if (!pos || i != v[pos - 1])
                v[pos] = i, self(self, pos + 1);
    };

    bfs(bfs, 0);
    gdb(hash);

    int r, c;
    vvi arr(2, vi(n));
    vvl tr(sz, vl(sz));
    auto dfs = [&](auto &&self, int pos, int flag) -> void {
        if (pos == n)
        {
            if (flag)
            {
                v = arr[0];
                trans();
                r = hash[k];
                v = arr[1];
                trans();
                c = hash[k];
                gdb(r, c);
                ++tr[r][c];
            }
            else
                self(self, 0, 1);
            return;
        }
        for (int i = 0; i < 3; ++i)
            if ((!pos || i != arr[flag][pos - 1]) && (!flag || arr[0][pos] != i))
                arr[flag][pos] = i, self(self, pos + 1, flag);
    };

    dfs(dfs, 0, 0);
    for (auto &p : tr)
        for (auto &q : p)
            q /= 6;
    gdb(tr);

    vl vec(sz, 1);
    qmi(tr, m - 1);
    mul(tr, vec);

    ll ans = 0;
    for (auto &p : vec)
        ans = (ans + p) % mod;
    cout << ans * 6 % mod << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
