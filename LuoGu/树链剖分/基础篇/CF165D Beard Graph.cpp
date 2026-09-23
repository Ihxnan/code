#include <ihxnan>
#include <HLD>

int n;
int tree[100001];
void add(int x, int w)
{
    for (; x <= n; x += x & -x)
        tree[x] += w;
}

int qry(int x)
{
    int ans = 0;
    for (; x; x -= x & -x)
        ans += tree[x];
    return ans;
}

int qry(int x, int y)
{
    return qry(y) - qry(x - 1);
}

void solve()
{
    cin >> n;
    HLD hld(n);
    vector<pii> edges(n - 1);
    for (auto &[u, v] : edges)
        cin >> u >> v, hld.add(u, v);
    hld.work();

    vi dfn(n);
    for (int i = 0; i < n - 1; ++i)
        dfn[i] = max(hld.in[edges[i].first], hld.in[edges[i].second]);

    auto query = [&](int u, int v) -> int {
        int ans = 0;
        while (hld.top[u] != hld.top[v])
        {
            if (hld.fa[hld.top[u]] < hld.fa[hld.top[v]])
                swap(u, v);
            ans += qry(hld.in[hld.top[u]], hld.in[u]);
            u = hld.fa[hld.top[u]];
        }
        if (hld.dep[u] > hld.dep[v])
            swap(u, v);
        if (hld.in[u] < hld.in[v])
            ans += qry(hld.in[u] + 1, hld.in[v]);
        return ans;
    };

    int m;
    cin >> m;
    vi color(n + 1);
    for (int i = 0, op, a, b; i < m; ++i)
    {
        cin >> op >> a;
        if (op == 3)
        {
            cin >> b;
            if (query(a, b))
                cout << -1 << endl;
            else
                cout << hld.dist(a, b) << endl;
        }
        else
        {
            --a;
            if (op == 1)
                add(dfn[a], -1);
            else
                add(dfn[a], 1);
        }
    }
}
