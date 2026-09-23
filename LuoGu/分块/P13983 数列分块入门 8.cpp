#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vi arr(n + 1);
    rd1(arr);

    int blen = sqrt(n) / 3 + 1;
    int bnum = (n + blen - 1) / blen;

    vi tag(bnum, -1);

    auto update = [&](int x) -> void {
        if (tag[x] != -1)
        {
            for (int i = bl(x); i <= br(x); ++i)
                arr[i] = tag[x];
            tag[x] = -1;
        }
    };

    for (int left, right, c; cin >> left >> right >> c;)
    {
        int l = bi(left), r = bi(right);
        int res = 0;
        if (l == r)
        {
            update(l);
            for (int i = left; i <= right; ++i)
                res += arr[i] == c, arr[i] = c;
        }
        else
        {
            update(l);
            for (int i = left; i <= br(l); ++i)
                res += arr[i] == c, arr[i] = c;
            update(r);
            for (int i = bl(r); i <= right; ++i)
                res += arr[i] == c, arr[i] = c;
            for (int i = l + 1; i < r; ++i)
                if (tag[i] == c)
                    res += br(i) - bl(i) + 1;
                else if (tag[i] != -1)
                    tag[i] = c;
                else
                {
                    for (int j = bl(i); j <= br(i); ++j)
                        res += arr[j] == c;
                    tag[i] = c;
                }
        }
        cout << res << endl;
    }
}
