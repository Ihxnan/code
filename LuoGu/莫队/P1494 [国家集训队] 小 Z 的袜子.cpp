#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    vi arr(n + 1);
    rd1(arr);

    int dn = 0;
    vector<ti> qry(m);
    for (auto &[l, r, id] : qry)
        cin >> l >> r, id = dn++;

    int blen = sqrt(n);
    sort(qry.begin(), qry.end(), [&](auto &x, auto &y) {
        auto &[l1, r1, id1] = x;
        auto &[l2, r2, id2] = y;
        if (bi(l1) != bi(l2))
            return bi(l1) < bi(l2);
        return bi(l1) & 1 ? r1 > r2 : r1 < r2;
    });

    vector<pll> ans(m);

    vi cnt(n + 1);
    ll A = 0, B = 0;
    int left = 1, right = 0;

    auto ins = [&](int x) -> void {
        ++B;
        A += 2 * cnt[arr[x]]++;
    };

    auto del = [&](int x) -> void {
        --B;
        A -= 2 * --cnt[arr[x]];
    };

    for (auto &[l, r, id] : qry)
    {
        while (left < l)
            del(left++);
        while (left > l)
            ins(--left);
        while (right < r)
            ins(++right);
        while (right > r)
            del(right--);
        int g = gcd(A, B * (B - 1));
        if (g == 0)
            ans[id] = {0, 1};
        else
            ans[id] = {A / g, B * (B - 1) / g};
    }

    for (auto &[a, b] : ans)
        cout << a << '/' << b << endl;
}
