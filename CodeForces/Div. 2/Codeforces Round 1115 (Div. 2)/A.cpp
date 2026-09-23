#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    int sum = 0;
    map<int, int> cnt;
    for (int i = 0, t; i < n; ++i)
        cin >> t, sum += t, ++cnt[t];
    priority_queue<pii> que;
    for (auto &[k, v] : cnt)
        que.emplace(v, k);
    int ma = 0;
    while (que.top().first >= (n-- + 3) / 2)
    {
        auto [times, num] = que.top();
        que.pop();
        sum -= num;
        ma = max(ma, num);
        if (--times)
            que.emplace(times, num);
    }
    cout << sum + ma << endl;
}
