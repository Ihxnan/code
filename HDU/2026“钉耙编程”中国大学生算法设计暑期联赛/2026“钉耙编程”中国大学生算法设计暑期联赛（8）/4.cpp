#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vvi t1(n + 1);
    set<pii> h1, h2, sta;
    vector<pii> e1(n), e2;
    for (int i = 1, u, v; i < n; ++i)
    {
        cin >> u >> v;
        if (u > v)
            swap(u, v);
        h1.emplace(u, v);
        t1[u].push_back(v);
        t1[v].push_back(u);
    }
    for (int i = 1, u, v; i < n; ++i)
    {
        cin >> u >> v;
        if (u > v)
            swap(u, v);
        h2.emplace(u, v);
        if (h1.count({u, v}))
            e2.emplace_back(u, v), sta.emplace(u, v);
    }
    for (int i = 0; i < e2.size(); ++i)
    {
        auto [u, v] = e2[i];
        for (auto &p : t1[u])
            if (!sta.count({min(p, v), max(p, v)}))
                if (h2.count({min(p, v), max(p, v)}))
                {
                    sta.emplace(min(p, v), max(p, v));
                    e2.emplace_back(min(p, v), max(p, v));
                    break;
                }
        for (auto &p : t1[v])
            if (!sta.count({min(p, u), max(p, u)}))
                if (h2.count({min(p, u), max(p, u)}))
                {
                    sta.emplace(min(p, u), max(p, u));
                    e2.emplace_back(min(p, u), max(p, u));
                    break;
                }
    }

    cout << (e2.size() + 1 == n ? "YES" : "NO") << endl;
}
