#include <ihxnan>

void solve()
{
    int n, q;
    cin >> n >> q;
    vl arr(n + 1);
    rd1(arr);

    int dn = 0;
    vector<ti> qry(q);
    for (auto &[l, r, id] : qry)
        cin >> l >> r, id = dn++;

    int blen = sqrt(n);
    sort(qry.begin(), qry.end(), [&](auto &x, auto &y) {
        auto &[l1, r1, id1] = x;
        auto &[l2, r2, id2] = y;
        if (bi(l1) != bi(l2))
            return l1 < l2;
        return r1 < r2;
    });

    vl ans(q);
    int block = -1;
    ll cur = 0, back = 0;
    int left = 1, right = 0;
    unordered_map<int, int> cnt;

    auto ins = [&](int x) -> void { cur = max(cur, arr[x] * ++cnt[arr[x]]); };

    auto del = [&](int x) -> void { --cnt[arr[x]]; };

    for (auto &[l, r, id] : qry)
    {
        if (block <= bi(l))
        {
            block = bi(l) + 1;
            while (left < bl(block))
                del(left++);
            while (right < br(block - 1))
                ins(++right);
            while (right > br(block - 1))
                del(right--);
            cur = 0;
        }

        if (bi(l) == bi(r))
        {
            ll res = 0;
            for (int i = l; i <= r; ++i)
                res = max(res, arr[i] * ++cnt[arr[i]]);
            for (int i = l; i <= r; ++i)
                --cnt[arr[i]];
            ans[id] = res;
        }

        else
        {
            while (right < r)
                ins(++right);
            back = cur;

            while (left > l)
                ins(--left);

            ans[id] = cur;
            while (left < bl(block))
                del(left++);

            cur = back;
        }
    }

    for (auto &p : ans)
        cout << p << endl;
}
