#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
#include <Comb>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
Comb comb(mod);
void solve()
{
    int n;
    cin >> n;
    vi hash(n + 1);
    vvi adj(n + 1);
    vector<pii> arr(n);
    for (auto &[a, b] : arr)
    {
        cin >> a >> b;
        ++hash[a], ++hash[b];
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    queue<int> que;
    for (int i = 1; i <= n; ++i)
        if (hash[i] == 1)
            que.push(i);

    int cnt = 0;
    while (que.size())
    {
        ++cnt;
        int x = que.front();
        que.pop();
        for (auto &p : adj[x])
            if (--hash[p] == 1)
                que.push(p);
    }

    gdb(cnt, n - cnt);
    cout << (cnt + (n - cnt) * comb.inv(2) % mod) % mod << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
