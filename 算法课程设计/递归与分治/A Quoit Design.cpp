#include <ihxnan>

#undef cin
#undef cout
void solve()
{
    int n;
    while (cin >> n, n)
    {
        vector<pair<double, double>> points(n);
        for (auto &[x, y] : points)
            cin >> x >> y;
        sort(points.begin(), points.end());

        auto dist = [&](auto &x, auto &y) -> double {
            return sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
        };

        auto dfs = [&](auto &&self, int l, int r) -> double {
            if (l >= r)
                return 1e18;
            if (l + 1 == r)
                return dist(points[l], points[r]);

            int mid = l + r >> 1;
            double x = points[mid].first;
            double res = min(self(self, l, mid), self(self, mid + 1, r));

            vector<pair<double, double>> tmp;
            for (; l <= r; ++l)
                if (abs(points[l].first - x) < res)
                    tmp.push_back(points[l]);
            sort(tmp.begin(), tmp.end(), [](auto &x, auto &y) { return x.second < y.second; });

            for (int i = 0; i < tmp.size(); ++i)
                for (int j = i + 1; j < tmp.size(); ++j)
                {
                    if (tmp[j].second - tmp[i].second >= res)
                        break;
                    res = min(res, dist(tmp[i], tmp[j]));
                }

            return res;
        };

        cout << fixed << setprecision(2) << dfs(dfs, 0, n - 1) / 2 << endl;
    }
}
