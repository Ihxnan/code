#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    cin >> n >> k;
    vl a;
    ll res = 0, x;
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        res = max(res, x);
        if (x)
            a.push_back(x);
    }

    if (a.empty())
    {
        cout << 0 << endl;
        return;
    }

    sort(a.begin(), a.end());
    a.pop_back();
    int cnt = 0, tmp = res;
    k -= 1;
    while (!a.empty())
    {
        cnt += 1;
        tmp = tmp * a.back() % mod;
        if (cnt == k)
        {
            res = tmp;
            cnt = 0;
        }
        a.pop_back();
    }
    cout << res % mod << "\n";
}
