#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    if (n > 8)
        return cout << 0, void();

    string a, b, c;
    cin >> a >> b >> c;

    int ans = 0;
    set<string> hash;
    vector<string> arr{"000", "001", "010", "011", "100", "101", "110", "111"};

    auto dfs = [&](auto &&self, int pos) -> void {
        if (pos == n)
            return ++ans, void();
        for (auto &p : arr)
            if (!hash.count(p))
                if (a[pos] == p[0] || a[pos] == '?')
                    if (b[pos] == p[1] || b[pos] == '?')
                        if (c[pos] == p[2] || c[pos] == '?')
                            hash.insert(p), self(self, pos + 1), hash.erase(p);
    };

    dfs(dfs, 0);

    cout << ans << endl;
}
