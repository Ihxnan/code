#include <ihxnan>

void solve()
{
    int n;
    cin >> n;

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    vl arr(n + 1);
    rd1(arr);

    vl tag(bnum), sum(bnum);

    for (int i = 0; i < bnum; ++i)
        for (int j = bl(i); j <= br(i); ++j)
            sum[i] += arr[j];

    auto update = [&](int left, int right, ll c) -> void {
        int l = bi(left), r = bi(right);
        if (l == r)
            for (int i = left; i <= right; ++i)
                arr[i] += c, sum[l] += c;
        else
        {
            for (int i = left; i <= br(l); ++i)
                arr[i] += c, sum[l] += c;
            for (int i = bl(r); i <= right; ++i)
                arr[i] += c, sum[r] += c;
            for (int i = l + 1; i < r; ++i)
                tag[i] += c;
        }
    };

    auto query = [&](int left, int right, ll c) -> ll {
        ll res = 0;
        int l = bi(left), r = bi(right);
        if (l == r)
            for (int i = left; i <= right; ++i)
                res += arr[i] + tag[l];
        else
        {
            for (int i = left; i <= br(l); ++i)
                res += arr[i] + tag[l];
            for (int i = bl(r); i <= right; ++i)
                res += arr[i] + tag[r];
            for (int i = l + 1; i < r; ++i)
                res += sum[i] + tag[i] * (br(i) - bl(i) + 1);
        }
        return (res % c + c) % c;
    };

    ll op, l, r, c;
    for (int i = 0; i < n; ++i)
    {
        cin >> op >> l >> r >> c;
        if (op == 0)
            update(l, r, c);
        else
            cout << query(l, r, c + 1) << endl;
    }
}
