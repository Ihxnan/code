#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m, x, y, k;
    cin >> n >> m >> x >> y >> k;

    auto work1 = [&](int n, int x, int check) -> int {
        int res = 0;
        int cnt = 0;
        while (n-- > 0)
        {
            ++cnt;
            res += x;
            if (cnt == 2 && check > 0)
                --check, --n, cnt = 0;
        }
        return res;
    };

    auto work2 = [&](int m, int y, int check) -> int {
        int res = 0;
        int cnt = 0;
        while (m-- > 0)
        {
            ++cnt;
            res += y;
            if (cnt == 3 && check > 0)
                --check, --m, cnt = 0;
        }
        return res;
    };

    int ans = iINF;
    for (int check = 0; check <= k; ++check)
        ans = min(ans, work1(n, x, check) + work2(m, y, k - check));
    cout << ans << endl;
}
