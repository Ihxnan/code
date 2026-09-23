#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;

    vi a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    vi p(n + 1);
    for (int i = 2; i <= n; ++i)
        cin >> p[i];

    vi av;
    vector<priority_queue<int, vi, greater<int>>> pq(n + 1);

    for (int i = n; i; --i)
    {
        if (pq[i].empty())
            pq[i].push(a[i]);
        else
        {
            int x = pq[i].top();
            pq[i].pop();
            pq[i].push(max(x, a[i]));
            av.push_back(min(x, a[i]));
        }

        if (i > 1)
        {
            int fa = p[i];
            if (pq[fa].size() < pq[i].size())
                swap(pq[fa], pq[i]);
            while (pq[i].size())
                pq[fa].push(pq[i].top()), pq[i].pop();
        }
    }

    ll sum = 0;
    int cnt = pq[1].size();

    while (pq[1].size())
        sum += pq[1].top(), pq[1].pop();

    vl ans(n + 1, -1);
    ans[cnt] = sum;
    sort(av.rbegin(), av.rend());
    for (int i = 0; i < av.size(); ++i)
        ans[cnt + i + 1] = ans[cnt + i] + av[i];

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
    cout << endl;
}
