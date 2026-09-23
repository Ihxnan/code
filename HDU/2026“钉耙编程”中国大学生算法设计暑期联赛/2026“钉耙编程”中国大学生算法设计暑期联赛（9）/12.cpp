#include <ihxnan>
#include <Treap>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vl arr(n);
    for (auto &p : arr)
        cin >> p;

    if (n == 1)
        return cout << 0 << endl, void();

    auto work = [&](int x) -> ll {
        if (x >= n || x - 1 < 0)
            return 0;
        return (arr[x] - arr[x - 1]) * (arr[x] - arr[x - 1]);
    };

    auto check = [&](int x, int y) -> bool {
        if (x + 1 == y)
        {
            ll src = work(x) + work(y + 1);
            swap(arr[x], arr[y]);
            ll dist = work(x) + work(y + 1);
            swap(arr[x], arr[y]);
            return src < dist;
        }
        ll src = work(x) + work(x + 1) + work(y) + work(y + 1);
        swap(arr[x], arr[y]);
        ll dist = work(x) + work(x + 1) + work(y) + work(y + 1);
        swap(arr[x], arr[y]);
        return src < dist;
    };

    ll ans = 0;
    for (int i = 1; i < n; ++i)
        ans += check(i - 1, i);
    for (int i = 2; i < n; ++i)
        ans += check(i - 2, i);

    for (int i = 3; i < n; ++i)
        ans += check(0, i);
    for (int i = n - 4; i > 0; --i)
        ans += check(n - 1, i);

    vb sta(n, 0);
    vi v(n - 2);
    iota(v.begin(), v.end(), 1);

    auto S = [&](int x) { return arr[x - 1] + arr[x + 1]; };

    auto ok = [&](int q) { return 1 <= q && q <= n - 2 && sta[q]; };

    auto com = [&](int pos) -> int {
        int res = 0;
        if (ok(pos - 1) && arr[pos - 1] < arr[pos])
            ++res;
        if (ok(pos - 2) && arr[pos - 2] < arr[pos])
            ++res;
        if (ok(pos + 1) && arr[pos + 1] < arr[pos])
            ++res;
        if (ok(pos + 2) && arr[pos + 2] < arr[pos])
            ++res;
        return res;
    };

    sort(v.begin(), v.end(), [&](int x, int y) { return S(x) < S(y); });

    Treap<int> treap(n);
    int l = 0;
    while (l < v.size())
    {
        int r = l;
        while (r + 1 < v.size() && S(v[r + 1]) == S(v[l]))
            r++;
        for (int k = l; k <= r; ++k)
        {
            int p = v[k];
            ans += treap.rank(arr[p]) - 1 - com(p);
        }
        for (int k = l; k <= r; ++k)
        {
            int p = v[k];
            treap.insert(arr[p]);
            sta[p] = 1;
        }
        l = r + 1;
    }

    cout << ans << endl;
}
