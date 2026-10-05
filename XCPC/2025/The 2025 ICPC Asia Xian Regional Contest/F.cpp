#include <ihxnan>

struct Pen {
    int pos, tar, flag, id;
};

void solve()
{
    int n;
    cin >> n;
    vvi adj(n + 1);
    vector<Pen> arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i].tar, arr[i].id = i, adj[arr[i].tar].push_back(i);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i].pos;
    for (int i = 1; i <= n; ++i)
        arr[i].flag = arr[arr[i].tar].pos > arr[i].pos;

    vector<Pen> vec = arr;
    sort(vec.begin() + 1, vec.end(), [&](auto &x, auto &y) { return x.pos < y.pos; });

    vi ans(n + 1);
    vector<Pen> stk;
    auto end = [&](int x) -> double { return 0.5 * ans[x] * (arr[x].flag ? 1 : -1) + arr[x].pos; };

    queue<Pen> que;

    int idx = 1;
    while (idx <= n)
    {
        if (ans[vec[idx].id] == 0)
            if (arr[vec[idx].id].flag == 0)
            {
                ans[vec[idx].id] = vec[idx].pos - arr[vec[idx].tar].pos;
                for (auto &p : adj[vec[idx].id])
                    que.push(arr[p]);
            }

        while (que.size())
        {
            auto [p1, t1, f1, i1] = que.front();
            que.pop();
            if (ans[i1])
                continue;
            auto [p2, t2, f2, i2] = arr[t1];
            if (f1 == f2)
                ans[i1] = 2 * abs(end(i2) - p1);
            else
            {
                int time = abs(p2 - p1);
                if (ans[i2] <= time)
                    ans[i1] = 2 * abs(end(i2) - p1);
                else
                    ans[i1] = abs(p2 - p1);
            }
            for (auto &p : adj[i1])
                que.push(arr[p]);
        }

        ++idx;
    }

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
    cout << endl;
}
