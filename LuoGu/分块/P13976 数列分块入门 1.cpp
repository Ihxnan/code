#include <ihxnan>

void solve()
{
    int n;
    cin >> n;

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    vl arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    vl tag(bnum);

    auto update = [&](int left, int right, ll c) -> void {
        int l = bi(left), r = bi(right);
        if (l == r)
            for (int i = left; i <= right; ++i)
                arr[i] += c;
        else
        {
            for (int i = left; i <= br(l); ++i)
                arr[i] += c;
            for (int i = bl(r); i <= right; ++i)
                arr[i] += c;
            for (int i = l + 1; i < r; ++i)
                tag[i] += c;
        }
    };

    ll op, l, r, c;
    for (int i = 0; i < n; ++i)
    {
        cin >> op >> l >> r >> c;
        if (op == 0)
            update(l, r, c);
        else
            cout << arr[r] + tag[bi(r)] << endl;
    }
}
