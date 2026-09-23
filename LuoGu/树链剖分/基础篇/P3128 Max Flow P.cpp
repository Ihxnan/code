#include <ihxnan>
#include <HLD>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    cin >> n >> k;
    HLD hld(n);
    for (int i = 0, u, v; i < n - 1; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work();
    vi cnt(n + 1);
    for (int i = 0, s, t, f; i < k; ++i)
    {
        cin >> s >> t;
        ++cnt[s], ++cnt[t];
        f = hld.lca(s, t);
        --cnt[f], --cnt[hld.fa[f]];
    }
    for (int i = n, t; i >= 1; --i)
    {
        t = hld.seq[i];
        cnt[hld.fa[t]] += cnt[t];
    }
    cout << *max_element(cnt.begin(), cnt.end());
}
