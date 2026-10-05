#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;

    set<pii> obs;
    set<pii> safe;
    set<pii> hash;

    auto dfs = [&](auto &&self, int pos, int x, int y) -> void {
        if (pos == n)
        {
            hash.emplace(x, y);
            return;
        }

        int bx = x, by = y;
        if (str[pos] == 'L')
            --x;
        else if (str[pos] == 'R')
            ++x;
        else if (str[pos] == 'U')
            ++y;
        else
            --y;

        if (obs.count({x, y}))
            self(self, pos + 1, bx, by);
        else if (!safe.count({x, y}))
        {
            obs.emplace(x, y);
            self(self, pos + 1, bx, by);
            obs.erase({x, y});
        }

        if (!obs.count({x, y}))
        {
            if (safe.count({x, y}))
                self(self, pos + 1, x, y);
            else
            {
                safe.emplace(x, y);
                self(self, pos + 1, x, y);
                safe.erase({x, y});
            }
        }
    };

    safe.emplace(0, 0);
    dfs(dfs, 0, 0, 0);

    cout << hash.size() << endl;
    for (auto &[x, y] : hash)
        cout << x << ' ' << y << endl;
}
