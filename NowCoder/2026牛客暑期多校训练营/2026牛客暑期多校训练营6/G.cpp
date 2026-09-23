#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vvi adj(n + 1);
    for (int i = 0, u, v; i < m; ++i)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vb te(n + 1);
    vb win(n + 1);
    vi cnt(n + 1);
    queue<int> que;
    for (int i = 0, t; i < k; ++i)
        cin >> t, te[t] = win[t] = true, que.push(t);

    gdb(te);

    while (que.size())
    {
        int x = que.front();
        que.pop();
        gdb(win[x]);
        for (auto &y : adj[x])
            if (!win[y])
                if (++cnt[y] == 2)
                {
                    win[y] = true;
                    que.push(y);
                }
    }

    gdb(win);
    gdb(cnt);

    vb sta(n + 1);
    for (int i = 1; i <= n; ++i)
        if (win[i])
            for (auto &p : adj[i])
                if (!te[p])
                    sta[p] = true;

    vi ans;
    for (int i = 1; i <= n; ++i)
        if (sta[i])
            ans.push_back(i);

    cout << ans.size() << endl;
    for (auto &p : ans)
        cout << p << ' ';
    cout << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
