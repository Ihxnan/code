#include <ihxnan>

int init = [] { return cin >> t, 0; }();

ll n, m, k, r;

vl operator*(const vvl &mat, vl &vec)
{
    vl ans(vec.size());
    for (int i = 0; i < 1 << n; ++i)
        for (int j = 0; j < 1 << n; ++j)
            ans[i] = max(ans[i], mat[i][j] + vec[j]);
    return ans;
}

vvl operator*(vvl &m1, vvl &m2)
{
    vvl ans(1 << n, vl(1 << n));
    for (int i = 0; i < 1 << n; ++i)
        for (int j = 0; j < 1 << n; ++j)
            for (int k = 0; k < 1 << n; ++k)
                ans[i][k] = max(ans[i][k], m1[i][j] + m2[j][k]);
    return ans;
}

vvl qmi(vvl &mat, int b)
{
    vvl res(1 << n, vl(1 << n));
    for (; b; b >>= 1, mat = mat * mat)
        if (b & 1)
            res = res * mat;
    return res;
}

void solve()
{
    cin >> n >> m >> k >> r;
    vector<pii> arr(n);
    for (auto &[a, c] : arr)
        cin >> a >> c;
    vl vec(1 << n);

    for (int i = 0; i < 1 << n; ++i)
    {
        ll damage = 0, ap = 0;
        for (int j = 0; j < n; ++j)
            if (i >> j & 1)
                damage += arr[j].first, ap += arr[j].second;
        if (ap <= m)
            vec[i] = damage;
    }

    vvl mat(1 << n, vl(1 << n));
    for (int i = 0; i < 1 << n; ++i)
        for (int j = 0; j < 1 << n; ++j)
        {
            ll damage = 0, ap = 0;
            for (int l = 0; l < n; ++l)
                if (i >> l & 1)
                    damage += arr[l].first, ap += arr[l].second + (j >> l & 1) * k;
            if (ap <= m)
                mat[i][j] = damage;
        }

    auto ans = qmi(mat, r - 1) * vec;
    cout << *max_element(ans.begin(), ans.end()) << endl;
}
