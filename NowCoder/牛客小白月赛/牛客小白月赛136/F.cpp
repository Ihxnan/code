#include <ihxnan>
#include <HLD>

int init = [] { return cin >> t, 0; }();

int n, w;

struct Que
{
    int sum = 0;
    priority_queue<int> que;
    void push(int x)
    {
        sum += x;
        que.push(x);
        if (sum > w)
            sum -= que.top(), que.pop();
    }
};

void solve()
{
    cin >> n >> w;
    HLD hld(n);
    vvi mp(n + 1);
    for (int i = 1, t; i <= n; ++i)
        cin >> t, mp[t].push_back(i);
    for (int i = 0, u, v; i < n - 1; ++i)
        cin >> u >> v, hld.add(u, v);
    hld.work();

    vector<Que> arr(n + 1);
    for (int i = 1; i <= n; ++i)
        if (mp[i].size())
        {
            int p = mp[i][0];
            for (int j = 1; j < mp[i].size(); ++j)
                p = hld.lca(p, mp[i][j]);
            arr[p].push(mp[i].size());
        }

    size_t ans = 0;
    for (int i = n, t; i >= 1; --i)
    {
        t = hld.seq[i];
        ans = max(ans, arr[t].que.size() * (hld.dep[t] + 1));
        if (arr[t].que.size() > arr[hld.fa[t]].que.size())
            swap(arr[t], arr[hld.fa[t]]);
        while (arr[t].que.size())
        {
            arr[hld.fa[t]].push(arr[t].que.top());
            arr[t].que.pop();
        }
    }
    cout << ans << endl;
}
