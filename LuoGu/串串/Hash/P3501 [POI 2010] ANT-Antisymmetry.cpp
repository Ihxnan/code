#include <ihxnan>

struct Hash {
    ul base;
    vector<ul> pow, h, rh;
    Hash(const string &str) : base(13331)
    {
        int n = str.size();
        pow.resize(n + 1);
        h.resize(n + 1);
        rh.resize(n + 1);
        pow[0] = 1;
        for (int i = 0; i < n; ++i)
        {
            pow[i + 1] = pow[i] * base;
            h[i + 1] = h[i] * base + str[i];
        }
        for (int i = n - 1; i >= 0; --i)
            rh[i] = rh[i + 1] * base + str[i];
    }

    ul get(int l, int r)
    {
        return h[r + 1] - h[l] * pow[r - l + 1];
    }

    ul rget(int l, int r)
    {
        return rh[l] - rh[r + 1] * pow[r - l + 1];
    }
};

void solve()
{
    int n;
    cin >> n;
    string s1;
    cin >> s1;
    string s2;
    for (auto &p : s1)
        s2 += p ^ 1;
    Hash h1(s1), h2(s2);

    auto check = [&](int x, int id) -> bool { return h1.get(id - x + 1, id) == h2.rget(id + 1, id + x); };

    ll ans = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        int len = min(i + 1, n - 1 - i);
        int l = 0, r = len + 1, mid;
        while (l + 1 < r)
            check(mid = l + r >> 1, i) ? l = mid : r = mid;
        ans += l;
    }
    cout << ans << endl;
}
