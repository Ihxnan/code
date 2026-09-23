#include <ihxnan>

void solve()
{
    ll n, m, k;
    cin >> n >> m >> k;

    vvi in(2);
    for (int i = 0, t; i < n; ++i)
        cin >> t, in[0].push_back(t);
    for (int i = 0, t; i < m; ++i)
        cin >> t, in[1].push_back(t);

    vvi id(in);
    for (auto &p : id)
        iota(p.begin(), p.end(), 0);

    for (int i = 0; i < 2; ++i)
        sort(id[i].begin(), id[i].end(), [&](int x, int y) { return in[i][x] > in[i][y]; });

    vector<tl> ans;
    auto work = [&](ll time, int flag) -> bool {
        vi idx(2);
        vector<tl> res;
#define get(flag) in[flag][id[flag][idx[flag]]]
        vl end{n, m};
        while (idx[0] < end[0] || idx[1] < end[1])
            if (idx[flag] < end[flag])
            {
                if (get(flag) > time - k)
                    return false;
                time -= k;
                res.emplace_back(time, flag, id[flag][idx[flag]]);
                ++idx[flag];
                flag ^= 1;
            }
            else
            {
                time -= k;
                flag ^= 1;
            }
        ans = res;
        return true;
    };

    auto check = [&](ll x) -> bool { return work(x, 0) || work(x, 1); };

    ll l = 0, r = lINF, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? r = mid : l = mid;
    cout << r << endl;

    if (work(r, 0) || work(r, 1))
    {
        reverse(ans.begin(), ans.end());
        for (auto &[a, b, c] : ans)
            cout << a << ' ' << b << ' ' << c + 1 << endl;
    }
}
