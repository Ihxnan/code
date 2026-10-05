#include <ihxnan>
#include <DSU>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, q;
    cin >> n >> q;

    char op;
    ll ans = 0;
    vector<DSU> dsu(1 << 12, n);
    for (int i = 0, x, y, w; i < q; ++i)
    {
        cin >> op >> x >> y;
        if (op == '+')
        {
            cin >> w;
            auto dfs = [&](auto &&self, int w) -> void {
                if (dsu[w].merge(x, y))
                    for (int j = 0; j < 12; ++j)
                        if (w >> j & 1)
                            self(self, w ^ 1 << j);
            };
            dfs(dfs, w);
        }
        else if (dsu[0].same(x, y))
        {
            int res = 0;
            for (int j = 11; j >= 0; --j)
                if (dsu[res | (1 << j)].same(x, y))
                    res |= 1 << j;
            ans += res;
        }
        else
            --ans;
    }

    cout << ans << endl;
}
