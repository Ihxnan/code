#include <ihxnan>
#include <MinCostFlow>

int n, k;
string strs[1001];

int init = [] { return cin >> t, 0; }();

bool check(int mid)
{
    int s = 0, t = n + k * 2 + 1;
    MinCostFlow<int> flow(t + 1);

    for (int i = 1; i <= n; ++i)
        flow.add(s, i, 1, 0);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= k; ++j)
            if (strs[i - 1][j - 1] == '1')
                flow.add(i, n + j, 1, 0);

    for (int i = 1; i <= k; ++i)
        flow.add(n + i, n + k + i, mid, 0);

    for (int i = 1; i <= k; ++i)
        flow.add(n + k + i, t, iINF, 0);

    return flow.flow(s, t).first == mid * k;
}

void solve()
{
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> strs[i];
    int l = -1, r = n + 1, mid;
    check(1);
    while (l + 1 < r)
        check(mid = l + r >> 1) ? l = mid : r = mid;
    cout << l << endl;
}
