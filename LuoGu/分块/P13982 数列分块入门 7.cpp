#include <ihxnan>

#define mod 10007
void solve()
{
    int n;
    cin >> n;
    vl arr(n + 1);
    rd1(arr);

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    vl add(bnum), mul(bnum, 1);

    auto update = [&](int x) -> void {
        for (int i = bl(x); i <= br(x); ++i)
            arr[i] = (arr[i] * mul[x] + add[x]) % mod;
        add[x] = 0;
        mul[x] = 1;
    };

    auto Add = [&](int left, int right, int c) -> void {
        int l = bi(left), r = bi(right);
        if (l == r)
        {
            update(l);
            for (int i = left; i <= right; ++i)
                arr[i] = (arr[i] + c) % mod;
        }
        else
        {
            update(l);
            for (int i = left; i <= br(l); ++i)
                arr[i] = (arr[i] + c) % mod;
            update(r);
            for (int i = bl(r); i <= right; ++i)
                arr[i] = (arr[i] + c) % mod;
            for (int i = l + 1; i < r; ++i)
                add[i] = (add[i] + c) % mod;
        }
    };

    auto Mul = [&](int left, int right, int c) -> void {
        int l = bi(left), r = bi(right);
        if (l == r)
        {
            update(l);
            for (int i = left; i <= right; ++i)
                arr[i] = arr[i] * c % mod;
        }
        else
        {
            update(l);
            for (int i = left; i <= br(l); ++i)
                arr[i] = arr[i] * c % mod;
            update(r);
            for (int i = bl(r); i <= right; ++i)
                arr[i] = arr[i] * c % mod;
            for (int i = l + 1; i < r; ++i)
                add[i] = add[i] * c % mod, mul[i] = mul[i] * c % mod;
        }
    };

    for (int i = 0, op, l, r, c; i < n; ++i)
    {
        cin >> op >> l >> r >> c;
        if (op == 0)
            Add(l, r, c);
        else if (op == 1)
            Mul(l, r, c);
        else
            cout << ((arr[r] * mul[bi(r)] + add[bi(r)]) % mod + mod) % mod << endl;
    }
}
