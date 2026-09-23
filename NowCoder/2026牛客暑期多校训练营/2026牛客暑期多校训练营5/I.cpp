#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
#define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n;
    cin >> n;
    n = (1 << n) - 1;
    string str;
    cin >> str;
    str = '^' + str;
    set<int> hash;
    for (int i = 1; i <= n; ++i)
        if (str[i] == '1')
            hash.insert(i);
    int cnt = hash.size();
    vi ans(n + 1);
    while (cnt > 1)
    {
        int x = *hash.begin();
        hash.erase(hash.begin());
        int y = *hash.begin();
        hash.erase(hash.begin());

        cnt -= 2;
        if ((str[x ^ y]) == '0')
            ++cnt, hash.insert(x ^ y);
        else
            --cnt, hash.erase(x ^ y);

        str[x] ^= 1, str[y] ^= 1, str[x ^ y] ^= 1;

        vi arr{x, y, x ^ y};
        sort(arr.begin(), arr.end());

        for (int i = 0; i < 3; ++i)
            if (ans[arr[i]] == 0)
            {
                ans[arr[i]] = arr[(i + 2) % 3];
                break;
            }
    }

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
    cout << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
