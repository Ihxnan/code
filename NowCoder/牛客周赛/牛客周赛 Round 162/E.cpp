#include <ihxnan>
#include <ST>

void solve()
{
    int n;
    cin >> n;
    vi arr(n + 1);
    vi prema(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], prema[i] = max(prema[i - 1], arr[i]);
    vi sufmi(n + 2, iINF);
    for (int i = n; i >= 1; --i)
        sufmi[i] = min(sufmi[i + 1], arr[i]);

    ST ma(arr), mi(arr, [&](int x, int y) { return min(x, y); });
    ma.init(), mi.init();

    auto check = [&](int l, int r) -> bool {
        int big = ma.query(l, r), sml = mi.query(l, r);
        return big > prema[l - 1] && sml < sufmi[r + 1];
    };

    ll ans = 0;
    for (int r = 1; r <= n; ++r)
    {
        int left = 0, right = r + 1, mid;
        while (left + 1 < right)
            check(mid = left + right >> 1, r) ? left = mid : right = mid;
        ans += left;
    }
    cout << ans << endl;
}
