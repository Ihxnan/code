#include <ihxnan>

int dx[] = {0, 1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {0, 2, -2, 1, -1, 2, -2, 1, -1};

void solve()
{
    int ex, ey, hx, hy;
    cin >> ex >> ey >> hx >> hy;
    ex += 2, ey += 2, hx += 2, hy += 2;

    vvi sta(ex + 3, vi(ey + 3));
    for (int i = 0; i < 9; ++i)
        sta[hx + dx[i]][hy + dy[i]] = 1;

    vl dp(ey + 3);
    dp[2] = 1;

    for (int i = 2; i <= ex; ++i)
        for (int j = 2; j <= ey; ++j)
            dp[j] = sta[i][j] ? 0 : dp[j] + dp[j - 1];

    cout << dp[ey];
}
