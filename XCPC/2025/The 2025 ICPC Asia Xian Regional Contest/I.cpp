#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vvi mat(n + 1, vi(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            cin >> mat[i][j], mat[j][i] = mat[i][j];

    int root = 1;
    vi ru(n + 1);
    vvi adj(n + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (i != j)
                if ((mat[root][i] ^ mat[root][j] ^ mat[i][j]) == i)
                    adj[i].push_back(j), ++ru[j];

    gdb(ru);
    gdb(adj);

    queue<int> que;
    que.push(root);
    vector<pii> edges;
    while (que.size())
    {
        int x = que.front();
        que.pop();
        for (auto &p : adj[x])
            if (!--ru[p])
                que.push(p), edges.emplace_back(x, p);
    }

    for (auto &[u, v] : edges)
        cout << u << ' ' << v << endl;
}
