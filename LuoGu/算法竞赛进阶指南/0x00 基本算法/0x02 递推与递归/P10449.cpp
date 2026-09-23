#define MULTIT
#include <ihxnan>

void solve()
{
    vector<vector<char>> mp(7, vector<char>(7));
    for (int i = 1; i <= 5; ++i)
        for (int j = 1; j <= 5; ++j)
            cin >> mp[i][j];

    auto hit = [&](int x, int y) -> void {
        mp[x][y] ^= 1;
        mp[x + 1][y] ^= 1;
        mp[x - 1][y] ^= 1;
        mp[x][y + 1] ^= 1;
        mp[x][y - 1] ^= 1;
    };

    auto back = mp;

    int ans = 7;
    for (int i = 0; i < 1 << 5; ++i)
    {
        int cnt = 0;
        for (int j = 1; j <= 5; ++j)
            if (i >> j - 1 & 1)
                hit(1, j), ++cnt;

        for (int j = 2; j <= 5; ++j)
            for (int k = 1; k <= 5; ++k)
                if (mp[j - 1][k] == '0')
                    hit(j, k), ++cnt;

        int j = 1;
        for (; j <= 5; ++j)
            if (mp[5][j] == '0')
                break;

        if (j > 5)
            ans = min(ans, cnt);

        mp = back;
    }
    cout << (ans <= 6 ? ans : -1) << endl;
}
