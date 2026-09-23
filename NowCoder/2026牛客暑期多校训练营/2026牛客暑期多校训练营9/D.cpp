#include <ihxnan>

struct Node
{
    int d, id;
    Node(int d, int id) : d(d), id(id)
    {
    }
    bool operator<(const Node &oth) const
    {
        return d < oth.d;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vvi tree(n + 1);
    for (int i = 1, u, v; i < n; ++i)
        cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);
    vi depth(n + 1);
    auto dfs = [&](auto &&self, int f, int r) -> void {
        for (auto &s : tree[r])
            if (s != f)
                depth[s] = depth[r] + 1, self(self, r, s);
    };
    dfs(dfs, 0, 1);

    Node t(0, 0);
    vi ans(m, 1);
    set<pair<int, Node>> hash;
    vector<set<Node>> arr(n + 1);
    for (int i = 0, x, s; i < m; ++i)
    {
        cin >> x >> s;
        t.d = depth[x] + s, t.id = i;
        if (arr[x].count(t))
            ans[i] = 0, ans[arr[x].find(t)->id] = 0, hash.emplace(x, t);
        else
            arr[x].emplace(depth[x] + s, i);
    }

    for (auto &[id, t] : hash)
        arr[id].erase(t);

    auto dfs2 = [&](auto &&self, int f, int r) -> void {
        set<Node> stk;

        for (auto &s : tree[r])
            if (s != f)
            {
                self(self, r, s);
                if (arr[r].size() < arr[s].size())
                    swap(arr[r], arr[s]);
                for (auto &p : arr[s])
                    if (arr[r].count(p))
                    {
                        ans[p.id] = false;
                        stk.insert(p);
                    }
                    else
                        arr[r].insert(p);
            }

        for (auto &p : stk)
            ans[arr[r].find(p)->id] = false, arr[r].erase(p);
    };

    dfs2(dfs2, 0, 1);

    for (auto &p : ans)
        cout << p;
}
