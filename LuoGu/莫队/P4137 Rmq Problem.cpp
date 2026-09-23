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
    int bnum = (n + blen - 1) / blen;

    sort(qry.begin(), qry.end(), [&](auto &x, auto &y) {
        auto &[l1, r1, id1] = x;
        auto &[l2, r2, id2] = y;
        if (bi(l1) != bi(l2))
            return l1 < l2;
        return bi(l1) & 1 ? r1 > r2 : r1 < r2;
    });

    vi tag(bnum);
    vi ans(m), cnt(n + 1);
    int left = 1, right = 0;

    auto ins = [&](int x) -> void {
        if (arr[x] <= n)
            if (++cnt[arr[x]] == 1)
                ++tag[bi(arr[x])];
    };

    auto del = [&](int x) -> void {
        if (arr[x] <= n)
            if (!--cnt[arr[x]])
                --tag[bi(arr[x])];
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

        int idx = 0;
        while (tag[idx] == br(idx) - bl(idx) + 1 + !idx)
            ++idx;

        idx = bl(idx) - !idx;
        while (cnt[idx])
            ++idx;

        ans[id] = idx;
    }

    for (auto &p : ans)
        cout << p << endl;
}
