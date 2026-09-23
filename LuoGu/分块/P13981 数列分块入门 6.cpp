#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vi arr(n + 1);
    rd1(arr);

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    vvi v2(bnum);
    for (int i = 0; i < bnum; ++i)
        for (int j = bl(i); j <= br(i); ++j)
            v2[i].push_back(arr[j]);

    auto rebuild = [&]() -> void {
        arr.assign(1, 0);
        for (auto &p : v2)
            for (auto &q : p)
                arr.push_back(q);
        n = arr.size() - 1;
        blen = sqrt(n);
        bnum = (n + blen - 1) / blen;
        v2.resize(bnum);
        for (int i = 0; i < bnum; ++i)
        {
            v2[i].clear();
            for (int j = bl(i); j <= br(i); ++j)
                v2[i].push_back(arr[j]);
        }
    };

    auto update = [&](int l, int r) -> void {
        int idx = 0;
        while (l > v2[idx].size())
            l -= v2[idx++].size();
        v2[idx].insert(v2[idx].begin() + l - 1, r);
    };

    auto query = [&](int c) -> int {
        int idx = 0;
        while (c > v2[idx].size())
            c -= v2[idx++].size();
        return v2[idx][c - 1];
    };

    int op, l, r, c, cnt = 0;
    while (cin >> op)
    {
        if (op == 0)
        {
            cin >> l >> r;
            update(l, r);
        }
        else
        {
            cin >> c;
            cout << query(c) << endl;
        }
        if (++cnt % (8 * blen) == 0)
            rebuild();
    }
}
