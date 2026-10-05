#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;

    vi ru(n + 1);
    vb sta(n + 1);
    vvi adj(n + 1);

    for (int i = 0, l, r, t, last; i < m; ++i)
    {
        cin >> l >> r;
        cin >> last;
        for (; l < r; ++l)
        {
            cin >> t;
            ++ru[t];
            adj[last].push_back(t);
            sta[last] = sta[t] = true;
            last = t;
        }
    }

    vi vec;
    vi ans(n + 1);
    for (int i = n; i; --i)
        if (sta[i] == false)
            ans[i] = i;
        else
            vec.push_back(i);

    priority_queue<int, vi, greater<int>> que;
    for (int i = 1; i <= n; ++i)
        if (sta[i] && !ru[i])
            que.push(i);

    while (que.size())
    {
        int x = que.top();
        que.pop();
        ans[x] = vec.back();
        vec.pop_back();
        for (auto &y : adj[x])
            if (!--ru[y])
                que.push(y);
    }

    if (vec.size())
        return cout << -1 << endl, void();

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
    cout << endl;
}
