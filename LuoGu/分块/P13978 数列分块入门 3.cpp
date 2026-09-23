#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vl arr(n + 1);
    rd1(arr);

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    vl tmp(n + 1), tag(bnum);

    auto sorted = [&](int x) -> void {
        for (int i = bl(x); i <= br(x); ++i)
            tmp[i] = arr[i];
        sort(tmp.begin() + bl(x), tmp.begin() + br(x) + 1);
    };

    for (int i = 0; i < bnum; ++i)
        sorted(i);

    auto update = [&](int left, int right, int c) -> void {
        int l = bi(left), r = bi(right);
        if (l == r)
        {
            for (int i = left; i <= right; ++i)
                arr[i] += c;
            sorted(l);
        }
        else
        {
            for (int i = left; i <= br(l); ++i)
                arr[i] += c;
            sorted(l);
            for (int i = bl(r); i <= right; ++i)
                arr[i] += c;
            sorted(r);
            for (int i = l + 1; i < r; ++i)
                tag[i] += c;
        }
    };

    auto query = [&](int left, int right, int c) -> int {
        ll ans = -lINF;
        int l = bi(left), r = bi(right);
        if (l == r)
        {
            for (int i = left; i <= right; ++i)
                if (arr[i] + tag[l] < c)
                    ans = max(ans, arr[i] + tag[l]);
        }
        else
        {
            for (int i = left; i <= br(l); ++i)
                if (arr[i] + tag[l] < c)
                    ans = max(ans, arr[i] + tag[l]);
            for (int i = bl(r); i <= right; ++i)
                if (arr[i] + tag[r] < c)
                    ans = max(ans, arr[i] + tag[r]);
            for (int i = l + 1; i < r; ++i)
            {
                int idx = lower_bound(tmp.begin() + bl(i), tmp.begin() + br(i) + 1, c - tag[i]) - tmp.begin() - 1;
                if (idx >= bl(i))
                    ans = max(ans, tmp[idx] + tag[i]);
            }
        }
        return ans == -lINF ? -1 : ans;
    };

    int op, l, r, c;
    while (cin >> op >> l >> r >> c)
        if (op == 0)
            update(l, r, c);
        else
            cout << query(l, r, c) << endl;
}
