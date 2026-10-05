#include <ihxnan>

#undef cin
#undef cout
#undef endl

int init = [] { return cin >> t, 0; }();

struct Tree {
    int n, cog, sz_cog;
    vi fa, sz;
    vvi adj;

    Tree(int n) : n(n), cog(0), sz_cog(iINF), fa(n + 1), sz(n + 1, 1), adj(n + 1)
    {
    }

    void add(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int f, int r)
    {
        int ma = 0;
        for (auto &s : adj[r])
            if (s != f)
            {
                fa[s] = r;
                dfs(r, s);
                sz[r] += sz[s];
                ma = max(ma, sz[s]);
            }
        ma = max(ma, n - sz[r]);
        if (ma < sz_cog)
            sz_cog = ma, cog = r;
    }
};

void solve()
{
    int n;
    cin >> n;

    Tree tree(n);
    vi vis(n + 1);
    for (int i = 1, u, v; i <= n; ++i)
    {
        cin >> u >> v;
        if (u)
            tree.add(i, u);
        if (v)
            tree.add(i, v);
        ++vis[u], ++vis[v];
    }

    int root;
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            root = i;

    gdb(tree.adj);

    auto init = [&](auto &&self, int f, int r, Tree &tree, Tree &tr) -> void {
        for (auto &s : tree.adj[r])
            if (s != f)
            {
                tr.add(r, s);
                self(self, r, s, tree, tr);
            }
    };

    int ans;
    auto dfs = [&](auto &&self, int r, Tree &tr) -> void {
        tr.dfs(0, r);
        int cog = tr.cog;
        gdb(tr.cog);
        vector<pii> arr;
        for (auto &s : tr.adj[cog])
            if (s != tr.fa[cog])
                arr.emplace_back(tr.sz[s], s);
        if (tr.fa[cog])
            arr.emplace_back(tr.n - tr.sz[cog], tr.fa[cog]);

        sort(arr.rbegin(), arr.rend());

        if (arr.empty())
            return cout << "! " << r << endl, void();

        if (arr.size() == 1)
        {
            cout << "? " << cog << ' ' << arr[0].second << endl;
            cin >> ans;
            if (ans == 0)
                cout << "! " << cog << endl;
            else
                cout << "! " << arr[0].second << endl;
            return;
        }

        cout << "? " << arr[0].second << ' ' << arr[1].second << endl;
        cin >> ans;

        Tree tree(n);

        if (ans == 1)
        {
            if (arr.size() == 2)
                return cout << "! " << cog << endl, void();

            tree.n = arr[2].first + 1;
            tree.add(cog, arr[2].second);
            init(init, cog, arr[2].second, tr, tree);
            self(self, cog, tree);
        }
        else if (ans == 0)
        {
            tree.n = arr[0].first;
            init(init, cog, arr[0].second, tr, tree);
            self(self, arr[0].second, tree);
        }
        else
        {
            tree.n = arr[1].first;
            init(init, cog, arr[1].second, tr, tree);
            self(self, arr[1].second, tree);
        }
    };

    dfs(dfs, root, tree);
}
