#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vl src(n + 1), arr(n + 1);
    rd1(src);

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;
    vl tag(bnum);

    auto sorted = [&](int x) -> void {
        for (int i = bl(x); i <= br(x); ++i)
            arr[i] = src[i];
        sort(arr.begin() + bl(x), arr.begin() + br(x) + 1);
    };

    for (int i = 0; i < bnum; ++i)
        sorted(i);

    auto update = [&](int left, int right, int c) -> void {
        int l = bi(left), r = bi(right);
        if (l == r)
        {
            for (int i = left; i <= right; ++i)
                src[i] += c;
            sorted(l);
        }
        else
        {
            for (int i = left; i <= br(l); ++i)
                src[i] += c;
            sorted(l);
            for (int i = bl(r); i <= right; ++i)
                src[i] += c;
            sorted(r);
            for (int i = l + 1; i < r; ++i)
                tag[i] += c;
        }
    };

    auto query = [&](int left, int right, ll c) -> int {
        int ans = 0;
        int l = bi(left), r = bi(right);
        if (l == r)
            for (int i = left; i <= right; ++i)
                ans += src[i] + tag[l] < c * c;
        else
        {
            for (int i = left; i <= br(l); ++i)
                ans += src[i] + tag[l] < c * c;
            for (int i = bl(r); i <= right; ++i)
                ans += src[i] + tag[r] < c * c;
            for (int i = l + 1; i < r; ++i)
                ans += lower_bound(arr.begin() + bl(i), arr.begin() + br(i) + 1, c * c - tag[i]) - arr.begin() - bl(i);
        }
        return ans;
    };

    for (int i = 0, op, l, r, c; i < n; ++i)
    {
        cin >> op >> l >> r >> c;
        if (op == 0)
            update(l, r, c);
        else
            cout << query(l, r, c) << endl;
    }
}
