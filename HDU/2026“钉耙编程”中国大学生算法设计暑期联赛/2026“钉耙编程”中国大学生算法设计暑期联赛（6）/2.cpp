#include <ihxnan>

int memo[] = {0, 6, 7, 11, 13, 15, 18, 14, 20, 21};
map<pii, int> tr{
    {{0, 0}, 0}, {{0, 1}, 1}, {{1, 0}, 2}, {{0, 2}, 3}, {{1, 1}, 4},
    {{0, 3}, 5}, {{1, 2}, 6}, {{2, 0}, 7}, {{2, 1}, 8}, {{3, 0}, 9},
};
int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;

    vvi mp(n + 2, vi(m + 2));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mp[i][j];

    ll ans = 0;
    int dx[] = {1, -1, 0, 0, 0};
    int dy[] = {0, 0, 1, -1, 0};

    array<int, 5> sta;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            gdb(ans);
            gdb(i, j, mp[i][j]);
            for (int k = 0; k < 5; ++k)
                sta[k] = min(mp[i + dx[k]][j + dy[k]], mp[i][j]);
            vi arr{0, 1, 2, 3, 4};
            sort(arr.begin(), arr.end(), [&](int a, int b) { return sta[a] < sta[b]; });
            bool first = true;
            if (sta[arr[0]])
                ans += 6, first = false;
            if (sta[arr[0]] == 1 && sta[arr[0]] == sta[arr[4]])
                ++ans;
            if (sta[arr[0]] > 1 && sta[arr[0]] == sta[arr[4]])
                ans += 6;

            for (int k = 1, t = 1; k < 5; t = ++k)
            {
                ll cnt = sta[arr[k]] - sta[arr[k - 1]];
                if (cnt)
                {
                    int c1 = 0, c2 = 0;
                    if (k == 1)
                        c1 = 1;
                    else if (k == 2)
                    {
                        if ((arr[0] ^ 1) == arr[1])
                            c2 = 1;
                        else
                            c1 = 2;
                    }
                    else if (k == 3)
                        c1 = c2 = 1;
                    else if (k == 4)
                        c2 = 2;

                    if (first && mp[i][j] == 1)
                    {
                        ans += memo[tr[{c2 + 1, c1}]];
                        break;
                    }

                    if (first)
                        ans += memo[tr[{c2, c1 + 1}]], --cnt, first = false;

                    if (sta[arr[k]] == mp[i][j])
                        ans += memo[tr[{c2, c1 + 1}]], --cnt;

                    ans += cnt * memo[tr[{c2, c1}]];
                }
            }
        }

    cout << ans << endl;
}
