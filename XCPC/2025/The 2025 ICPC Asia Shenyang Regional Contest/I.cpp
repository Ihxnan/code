#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vector<set<int>> arr(411);
    for (int i = 0, a, b, c; i < n; ++i)
    {
        cin >> a >> b >> c;
        int ans = 0;
        if (c < 240)
        {
            if (arr[a].count(b) == 0)
                ans = b, arr[a].insert(b);
        }
        else
        {
            if (arr[a].count(b) == 0)
                if (arr[a].size() < 3)
                    ans = b, arr[a].insert(b);
        }
        cout << ans << endl;
    }
}
