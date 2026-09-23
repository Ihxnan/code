#include <ihxnan>

int init = [] { return cin >> t, 0; }();

struct Hash {
    ul base;
    vector<ul> pow, h;
    Hash(const string &str) : base(13331)
    {
        int n = str.size();
        pow.resize(n + 1);
        h.resize(n + 1);
        pow[0] = 1;
        for (int i = 0; i < n; ++i)
        {
            pow[i + 1] = pow[i] * base;
            h[i + 1] = h[i] * base + str[i];
        }
    }
    ul get(int l, int r)
    {
        return h[r + 1] - h[l] * pow[r - l + 1];
    }
};

void solve()
{
    string s1, s2;
    cin >> s1 >> s2;

    int ans = 0;
    Hash h1(s1), h2(s2);

    auto check = [&](int left, int idx, int x) -> bool { return h1.get(left, left + x) == h2.get(idx, idx + x); };

    auto lower = [&](int left, int right, int idx) -> int {
        int l = -1, r = right - left + 1, mid;
        while (l + 1 < r)
            check(left, idx, mid = l + r >> 1) ? l = mid : r = mid;
        return idx + r;
    };

    auto func = [&](int l, int r) -> bool {
        int idx = 0, cnt = 0;
        while ((idx = lower(l + idx, r, idx) + 1) <= s2.size())
            if (++cnt > 3)
                return false;
        return true;
    };

    for (int l = 0, r = s2.size() - 1; r < s1.size(); ++l, ++r)
        ans += func(l, r);

    cout << ans << endl;
}
