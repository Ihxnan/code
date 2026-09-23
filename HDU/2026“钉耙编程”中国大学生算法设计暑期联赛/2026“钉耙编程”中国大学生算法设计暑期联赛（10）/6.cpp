#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;

    vi arr(n);
    for (auto &p : arr)
        cin >> p;

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    gdb(bnum, blen);

    vi bi(n);
    vi bl(bnum), br(bnum), sum(bnum), sta(bnum, -1), flag(bnum);

    for (int i = 0; i < n; ++i)
        bi[i] = i / blen;

    auto func = [&](int b) -> void {
        sum[b] = 0;
        for (int i = bl[b] + 1; i < br[b]; ++i)
            sum[b] += arr[i] != arr[i - 1];
    };

    for (int i = 0; i < bnum; ++i)
    {
        bl[i] = i * blen, br[i] = min(bl[i] + blen, n);
        func(i);
    }

    gdb(sum);

    auto push_down = [&](int b) -> void {
        if (sta[b] != -1)
            for (int i = bl[b]; i < br[b]; ++i)
                arr[i] = sta[b];
        if (flag[b])
            for (int i = bl[b]; i < br[b]; ++i)
                arr[i] ^= 1;
        sta[b] = -1;
        flag[b] = 0;
    };

    auto update = [&](int s, int e, int x) -> void {
        int l = bi[s], r = bi[e - 1];
        if (l == r)
        {
            push_down(l);
            for (; s < e; ++s)
                arr[s] = x;
            func(l);
        }
        else
        {
            push_down(l);
            for (int i = s; i < br[l]; ++i)
                arr[i] = x;
            func(l);

            push_down(r);
            for (int i = bl[r]; i < e; ++i)
                arr[i] = x;
            func(r);

            for (int i = l + 1; i < r; ++i)
                sta[i] = x, flag[i] = 0, sum[i] = 0;
        }
    };

    auto fan = [&](int s, int e) -> void {
        int l = bi[s], r = bi[e - 1];
        if (l == r)
        {
            push_down(l);
            for (; s < e; ++s)
                arr[s] ^= 1;
            func(l);
        }
        else
        {
            push_down(l);
            for (int i = s; i < br[l]; ++i)
                arr[i] ^= 1;
            func(l);

            push_down(r);
            for (int i = bl[r]; i < e; ++i)
                arr[i] ^= 1;
            func(r);

            for (int i = l + 1; i < r; ++i)
                if (sta[i] != -1)
                    sta[i] ^= 1;
                else
                    flag[i] ^= 1;
        }
    };

    auto get = [&](int pos) -> int {
        int res = arr[pos];
        if (sta[bi[pos]] != -1)
            return sta[bi[pos]];
        return arr[pos] ^ flag[bi[pos]];
    };

    auto query = [&](int s, int e) -> int {
        int l = bi[s], r = bi[e - 1];
        int ans = 0;
        if (l == r)
        {
            push_down(l);
            for (++s; s < e; ++s)
                ans += arr[s] != arr[s - 1];
        }
        else
        {
            push_down(l);
            for (int i = s + 1; i < br[l]; ++i)
                ans += arr[i] != arr[i - 1];

            push_down(r);
            for (int i = bl[r] + 1; i < e; ++i)
                ans += arr[i] != arr[i - 1];

            for (int i = l + 1; i < r; ++i)
                ans += sum[i];

            for (int i = l + 1; i <= r; ++i)
                ans += get(bl[i]) != get(bl[i] - 1);
        }
        return ans;
    };

    for (int i = 0, op, l, r, x; i < m; ++i)
    {
        cin >> op >> l >> r;
        if (op == 1)
        {
            cin >> x;
            update(l - 1, r, x);
            gdb(i);
            // for (int j = 0; j < n; ++j)
            //     cout << get(j) << ' ';
            // cout << endl;
        }
        else if (op == 2)
        {
            fan(l - 1, r);
            gdb(i);
            // for (int j = 0; j < n; ++j)
            //     cout << get(j) << ' ';
            // cout << endl;
        }
        else
            cout << query(l - 1, r) << endl;
    }
}
