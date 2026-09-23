#include <ihxnan>

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vi arr(n + 1);
    rd1(arr);
    vector<ti> qry(m);
    int cnt = 0;
    for (auto &[l, r, id] : qry)
        cin >> l >> r, id = cnt++;
    int blen = sqrt(n);
    sort(qry.begin(), qry.end(), [&](auto &x, auto &y) {
        auto &[l1, r1, id1] = x;
        auto &[l2, r2, id2] = y;
        if (bi(l1) != bi(l2))
            return bi(l1) < bi(l2);
        return bi(l1) & 1 ? r1 > r2 : r1 < r2;
    });

    vl ans(m);
    ll res = 0;
    vi counter(k + 1);
    int left = 1, right = 0;

    auto ins = [&](int x) -> void { res += ++counter[arr[x]] * 2 - 1; };

    auto del = [&](int x) -> void { res -= counter[arr[x]]-- * 2 - 1; };

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
        ans[id] = res;
    }

    for (auto &p : ans)
        cout << p << endl;
}
