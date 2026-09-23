#include <ihxnan>

void solve()
{
    int n;
    cin >> n;

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    vi arr(n + 1);
    rd1(arr);

    vi tag(bnum);
    vl sum(bnum);

    for (int i = 0; i < bnum; ++i)
        for (int j = bl(i); j <= br(i); ++j)
            tag[i] = max(tag[i], arr[j]), sum[i] += arr[j];

    auto work = [&](int x) -> void {
        tag[x] = 0;
        for (int i = bl(x); i <= br(x); ++i)
            tag[x] = max(tag[x], arr[i]);
    };

    auto update = [&](int left, int right) -> void {
        int l = bi(left), r = bi(right);
        if (l == r)
        {
            for (int i = left; i <= right; ++i)
                sum[l] -= arr[i], sum[l] += arr[i] = sqrt(arr[i]);
            work(l);
        }
        else
        {
            for (int i = left; i <= br(l); ++i)
                sum[l] -= arr[i], sum[l] += arr[i] = sqrt(arr[i]);
            work(l);
            for (int i = bl(r); i <= right; ++i)
                sum[r] -= arr[i], sum[r] += arr[i] = sqrt(arr[i]);
            work(r);
            for (int i = l + 1; i < r; ++i)
                if (tag[i] > 1)
                {
                    for (int j = bl(i); j <= br(i); ++j)
                        sum[i] -= arr[j], sum[i] += arr[j] = sqrt(arr[j]);
                    work(i);
                }
        }
    };

    auto query = [&](int left, int right) -> ll {
        ll res = 0;
        int l = bi(left), r = bi(right);
        if (l == r)
            for (int i = left; i <= right; ++i)
                res += arr[i];
        else
        {
            for (int i = left; i <= br(l); ++i)
                res += arr[i];
            for (int i = bl(r); i <= right; ++i)
                res += arr[i];
            for (int i = l + 1; i < r; ++i)
                res += sum[i];
        }
        return res;
    };

    int op, l, r;
    for (int i = 0; i < n; ++i)
    {
        cin >> op >> l >> r;
        if (op == 0)
            update(l, r);
        else
            cout << query(l, r) << endl;
    }
}
