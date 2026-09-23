#include <ihxnan>
#include <HLD>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    HLD hld(n);
    int root = 1;
    for (int i = 1, p; i <= n; ++i)
    {
        cin >> p;
        if (p == i)
            root = i;
        else
            hld.add(p, i);
    }
    hld.work(root);

    vvi paths;
    auto &adj = hld.adj;

    auto dfs = [&](auto &&self, int root, int pos) -> void {
        if (adj[root].empty())
            return;
        paths[pos].push_back(adj[root][0]);
        self(self, adj[root][0], pos);
        for (int i = 1; i < adj[root].size(); ++i)
        {
            paths.push_back(vi{adj[root][i]});
            self(self, adj[root][i], paths.size() - 1);
        }
    };

    paths.push_back(vi{root});
    dfs(dfs, root, paths.size() - 1);

    cout << paths.size() << endl;
    for (auto &p : paths)
    {
        cout << p.size() << endl;
        for (auto &q : p)
            cout << q << ' ';
        cout << endl;
    }
    cout << endl;
}
