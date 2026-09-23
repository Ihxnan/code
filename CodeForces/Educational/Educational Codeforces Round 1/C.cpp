#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
#define double long double
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
struct node
{
    int x, y, id;
    double a;
    bool operator<(const node &b)
    {
        return a < b.a;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<node> arr(n);
    int dn = 0;
    double pi = acosl(-1);
    for (auto &[x, y, id, a] : arr)
        cin >> x >> y, id = ++dn, a = atan2l(y, x), a += a < 0 ? 2 * pi : 0;
    sort(arr.begin(), arr.end());
    double ans = arr.front().a - arr.back().a + pi * 2.;
    int ans1 = arr.front().id, ans2 = arr.back().id;
    for (int i = 1; i < n; i++)
        if (arr[i].a - arr[i - 1].a < ans)
            ans = arr[i].a - arr[i - 1].a, ans2 = arr[i].id, ans1 = arr[i - 1].id;
    cout << ans1 << " " << ans2;
}
/* ╚══════════ /SOLVE ══════════╝ */
