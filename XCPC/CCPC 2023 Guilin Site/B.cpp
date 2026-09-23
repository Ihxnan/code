#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    vi a(n), b(m);
    read(a);
    read(b);
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    ll sum = 0;
    for (int i = 0; i < m; ++i)
        if (a[i] > b[i])
            return cout << -1 << endl, void();
        else
            sum += b[i] - a[i];

    if (sum > n - m)
        return cout << -1 << endl, void();

    vi tmp;
    for (int i = 0; i < m; ++i)
        while (a[i] < b[i])
            tmp.push_back(a[i]++);

    sort(tmp.rbegin(), tmp.rend());
    int need = n - m - sum;

    priority_queue<int, vi, greater<int>> que;
    for (int i = 0; i < n; ++i)
        que.push(a[i]);

    vi ans;

    while (need--)
    {
        if (que.size() < 2)
            break;
        int x = que.top();
        que.pop();
        int y = que.top();
        if (x < y)
            ans.push_back(x);
        else if (x == y)
        {
            ++y;
            if (y >= b.back())
            {
                --sum, ++need;
                if (tmp.size())
                    ans.push_back(tmp.back()), tmp.pop_back();
            }
            else
                que.pop(), que.push(y), ans.push_back(y - 1);
        }
    }

    if (sum < 0)
        return cout << -1 << endl, void();

    while (tmp.size())
        ans.push_back(tmp.back()), tmp.pop_back();

    cout << ans.size() << endl;
    for (auto &p : ans)
        cout << p << ' ';
    cout << endl;
}
