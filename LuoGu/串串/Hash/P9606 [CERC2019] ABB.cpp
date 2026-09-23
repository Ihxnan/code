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
    string str;
    cin >> str;
    Hash hash(str);
    int ans = 0;
    for (int i = n - 1; i >= 0; --i)
        if (hash.get(i, n - 1) == hash.rget(i, n - 1))
            ans = n - i;
    cout << n - ans << endl;
}
