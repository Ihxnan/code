#include <ihxnan>

void solve()
{
    int n, t;
    cin >> n >> t;
    string str;
    cin >> str;
    for (auto &p : str)
        p = p == 'N' ? 0 : 1;
    str = '^' + str + '$';

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    vi tag(bnum);
    vvi cnt(2, vi(bnum));
    for (int i = 0; i < bnum; ++i)
        for (int j = bl(i); j <= br(i); ++j)
            str[j] ? ++cnt[1][i] : ++cnt[0][i];

    auto query = [&](int pos, int flag, int zero) -> int {
        if (flag == 1)
        {
            int l = bi(pos);
            for (int i = pos; i <= br(l); ++i)
                if ((str[i] ^ tag[l]) == zero)
                    return i;

            for (++l; l < bnum; ++l)
                if (cnt[zero][l] > 0)
                    for (int i = bl(l); i <= br(l); ++i)
                        if ((str[i] ^ tag[l]) == zero)
                            return i;

            return n;
        }

        int r = bi(pos);
        for (int i = pos; i >= bl(r); --i)
            if ((str[i] ^ tag[r]) == zero)
                return i;

        for (--r; r >= 0; --r)
            if (cnt[zero][r] > 0)
                for (int i = br(r); i >= bl(r); --i)
                    if ((str[i] ^ tag[r]) == zero)
                        return i;

        return 1;
    };

    auto update = [&](int left, int right) -> void {
        if (left > right)
            swap(left, right);
        int l = bi(left), r = bi(right);
        if (l == r)
            for (int i = left; i <= right; ++i)
            {
                str[i] ^= 1;
                ++cnt[str[i] ^ tag[l]][l];
                --cnt[str[i] ^ 1 ^ tag[l]][l];
            }
        else
        {
            for (int i = left; i <= br(l); ++i)
            {
                str[i] ^= 1;
                ++cnt[str[i] ^ tag[l]][l];
                --cnt[str[i] ^ 1 ^ tag[l]][l];
            }
            for (int i = bl(r); i <= right; ++i)
            {
                str[i] ^= 1;
                ++cnt[str[i] ^ tag[r]][r];
                --cnt[str[i] ^ 1 ^ tag[r]][r];
            }
            for (int i = l + 1; i < r; ++i)
            {
                tag[i] ^= 1;
                swap(cnt[0][i], cnt[1][i]);
            }
        }
    };

    auto work = [&](int pos, int flag, ll k, int zero) -> void {
        while (pos >= 1 && pos <= n && k > 1)
        {
            if (k & 1)
            {
                int b = bi(pos);
                str[pos] ^= 1;
                ++cnt[str[pos] ^ tag[b]][b];
                --cnt[str[pos] ^ 1 ^ tag[b]][b];
                k += (str[pos] ^ tag[b]) == zero;
            }
            pos += flag;
            k >>= 1;
        }

        if (pos < 1 || pos > n)
            return;

        int idx = query(pos, flag, zero);

        update(pos, idx);
    };

    for (ll i = 0, op, pos, k; i < t; ++i)
    {
        cin >> op >> pos >> k;
        if (!k)
            continue;
        if (op == 1)
            work(pos, 1, k, 0);
        else if (op == 2)
            work(pos, 1, k, 1);
        else if (op == 3)
            work(pos, -1, k, 0);
        else
            work(pos, -1, k, 1);
    }

    for (int i = 1; i <= n; ++i)
        cout << ((str[i] ^ tag[bi(i)]) == 0 ? 'N' : 'H');
}
