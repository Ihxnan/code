#include <ihxnan>

#undef cin
#undef cout
void solve()
{
    vector<pii> arr(8);
    for (auto &[a, b] : arr)
        cin >> a >> b;
    vi seed(8);
    iota(seed.begin(), seed.end(), 0);

    vector<pii> vec(8);

    auto dfs = [&](auto &&self, int l, int r) -> map<int, double> {
        if (l == r)
            return map<int, double>{{l, 1}};

        int mid = l + r >> 1;

        auto left = self(self, l, mid);
        auto right = self(self, mid + 1, r);

        map<int, double> res;
        for (auto &[lk, lv] : left)
            for (auto &[rk, rv] : right)
                res[lk] += lv * rv * vec[lk].first / (vec[lk].first + vec[rk].second),
                    res[rk] += lv * rv * vec[rk].second / (vec[lk].first + vec[rk].second);

        double sum = 0;
        for (auto &[k, v] : res)
            sum += v;
        return res;
    };

    double ans = 0;

    do
    {
        for (int i = 0; i < 8; ++i)
            vec[seed[i]] = arr[i];
        double tmp = dfs(dfs, 0, 7)[seed[0]];
        if (tmp > ans)
            ans = tmp;
    } while (next_permutation(seed.begin(), seed.end()));

    cout << fixed << setprecision(20) << ans << endl;
}
