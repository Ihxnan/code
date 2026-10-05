#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    int ma = 0;
    vi arr(n + 1);
    unordered_map<int, vi> mp;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
        if (mp[arr[i]].empty())
            mp[arr[i]].push_back(0);
        mp[arr[i]].push_back(i), ma = max(ma, arr[i]);
    }

    if (ma == 1)
        return cout << -1 << endl, void();

    for (auto &[k, v] : mp)
        v.push_back(n + 1);

    vector<pii> qry;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j < mp[i].size(); ++j)
        {
            int l = mp[i][j - 1] + 1, r = mp[i][j] - 1;
            if (l < r)
                qry.emplace_back(l, r);
        }
    qry.emplace_back(1, n);

    int blen = sqrt(n);
    int bnum = (n + blen - 1) / blen;

    sort(qry.begin(), qry.end(), [&](auto &x, auto &y) {
        auto &[l1, r1] = x;
        auto &[l2, r2] = y;
        if (bi(l1) != bi(l2))
            return l1 < l2;
        return bi(l1) & 1 ? r1 > r2 : r1 < r2;
    });

    int cur = 0;
    vi tag(bnum);
    vi cnt(m + 1);
    int left = 1, right = 0;

    auto ins = [&](int x) -> void {
        if (++cnt[arr[x]] == 1)
        {
            ++cur;
            if (arr[x] <= n)
                ++tag[bi(arr[x])];
        }
    };

    auto del = [&](int x) -> void {
        if (!--cnt[arr[x]])
        {
            --cur;
            if (arr[x] <= n)
                --tag[bi(arr[x])];
        }
    };

    int ans = 0;
    for (auto &[l, r] : qry)
    {
        while (left < l)
            del(left++);
        while (left > l)
            ins(--left);
        while (right < r)
            ins(++right);
        while (right > r)
            del(right--);

        int mex = 0;
        while (mex < bnum && tag[mex] == br(mex) - bl(mex) + 1)
            ++mex;
        mex = bl(mex);
        while (cnt[mex])
            ++mex;

        ans = max(ans, cur - mex);
    }

    cout << ans << endl;
}
