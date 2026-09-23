#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    set<char> s;
    for (auto &p : str)
        s.insert(p);
    if (s.size() == 1)
        return cout << 1 << endl, void();

    str = '^' + str;
    vvi tree(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i)
    {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    queue<int> que;
    vi vis(n + 1);
    vector<pii> sta(n + 1);

    for (int i = 1; i <= n; ++i)
        if (str[i] == 'R')
            sta[i].first = 1;
        else
            sta[i].second = 1;

    for (int i = 1; i <= n; ++i)
        if (tree[i].size() == 1)
            que.push(i);

    int tmp = 0;
    while (que.size())
    {
        int x = que.front();
        que.pop();
        if (vis[x])
            continue;
        vis[x] = 1;
        if (++tmp == n - 1)
            break;

        for (auto &y : tree[x])
            if (!vis[y])
            {
                if (sta[x].first)
                    sta[y].first = 1;
                if (sta[x].second)
                    sta[y].second = 1;
                que.push(y);
            }
    }

    int tar;
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 0)
            tar = i;

    if (str[tar] == 'R')
        sta[tar].first = 1, sta[tar].second = 0;
    else
        sta[tar].first = 0, sta[tar].second = 1;

    bool flag = false;
    for (auto &p : tree[tar])
        if (!sta[p].first && !sta[tar].first || !sta[p].second && !sta[tar].second)
            flag = true;

    int cnt = 1;
    for (int i = 1; i <= n; ++i)
        cnt += sta[i].first && sta[i].second;

    cout << cnt - flag << endl;
}
