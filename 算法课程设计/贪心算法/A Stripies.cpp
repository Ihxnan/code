#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    priority_queue<double> que;
    for (int i = 0, t; i < n; ++i)
        cin >> t, que.push(t);
    while (que.size() > 1)
    {
        double x = que.top();
        que.pop();
        double y = que.top();
        que.pop();
        que.push(2 * sqrt(x * y));
    }
    printf("%.3f", que.top());
}
