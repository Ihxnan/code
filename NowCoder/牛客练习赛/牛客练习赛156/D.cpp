#include <ihxnan>
#include <HLD>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi w(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    HLD hld(n);
    for (int i = 1, u, v; i < n; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work();

    vl sz(n + 1);
    vvl cnt(n + 1, vl(31));

    auto &seq = hld.seq, &fa = hld.fa;
    for (int i = 1; i <= n; ++i)
    {
        int cur = 1;
        int t = seq[i];

        while (fa[t])
        {
            sz[fa[t]] += cur;
            for (int j = 0; j < 31; ++j)
                cnt[fa[t]][j] += (w[seq[i]] >> j & 1) * cur;
            ++cur;
            t = fa[t];
        }
    }

    gdb(sz);
    gdb(cnt);
    vector<lll> vec(31);
}
