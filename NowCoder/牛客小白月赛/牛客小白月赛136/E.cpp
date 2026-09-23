#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    string str[3];
    cin >> n >> m >> str[0];
    str[1] = str[1] + str[0][1] + str[0][2] + str[0][0];
    str[2] = str[2] + str[0][2] + str[0][0] + str[0][1];

    vector<vector<char>> mp(n + 1, vector<char>(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mp[i][j];

    vector<vvi> dp(n + 1, vvi(m + 1, vi(3, -1)));

    int dx[] = {0, 0, 0, -1, -2, -3, 0, 0, 0, 1, 2, 3};
    int dy[] = {-1, -2, -3, 0, 0, 0, 1, 2, 3, 0, 0, 0};
    int dz[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2};

    int a, b;
    auto bfs = [&](int x, int y) -> void {
        queue<ti> que;
        dp[x][y][0] = dp[x][y][1] = dp[x][y][2] = 0;
        que.emplace(x, y, 0);
        que.emplace(x, y, 1);
        que.emplace(x, y, 2);
        while (que.size())
        {
            auto [i, j, sta] = que.front();
            que.pop();
            int flag = (sta + 2) % 3;
            for (int k = 0; k < 12; ++k)
            {
                a = i + dx[k];
                b = j + dy[k];
                if (a < 1 || a > n || b < 1 || b > m || str[flag][dz[k]] != mp[i][j] || dp[a][b][flag] != -1)
                    continue;
                dp[a][b][flag] = dp[i][j][sta] + 1;
                que.emplace(a, b, flag);
            }
        }
    };

    bfs(n, m);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            cout << dp[i][j][0] << ' ';
        cout << endl;
    }
}
