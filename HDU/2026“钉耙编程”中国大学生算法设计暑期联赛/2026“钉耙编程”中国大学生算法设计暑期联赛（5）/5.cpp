#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, k, m, q;
    cin >> n >> k >> m >> q;

    vi ans;
    vector<string> arr(n);
    map<string, pair<int, bool>> cnt;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        if (cnt[arr[i]].first == q)
            continue;

        ++(cnt[arr[i]].first);
        if (cnt[arr[i]].second)
        {
            if (cnt[arr[i]].first > m)
                ans.push_back(i);
        }
        else if (i + 1 >= k)
        {
            bool flag = true;
            for (int j = i - 1; j >= i + 1 - k; --j)
                if (arr[j] != arr[i])
                {
                    flag = false;
                    break;
                }
            cnt[arr[i]].second = flag;
        }
    }
    if (ans.empty())
        cout << "empty";
    for (auto &p : ans)
        cout << p + 1 << ' ';
    cout << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
