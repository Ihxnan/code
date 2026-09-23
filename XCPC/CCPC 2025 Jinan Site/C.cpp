#include <ihxnan>

void solve()
{
    int m;
    cin >> m;
    vi b(m);
    for (auto &p : b)
        cin >> p;
    int n;
    cin >> n;
    for (int i = 0, k; i < n; ++i)
    {
        cin >> k;
        vvi mp(m + 1);
        for (int j = 0, t; j < k; ++j)
            if (cin >> t, t <= 10)
                mp[t].push_back(j);
        gdb(mp);
        vi idx(m + 1);
        while (idx[b[0]] < mp[b[0]].size())
        {
            bool flag = false;
            for (int j = 1; j < m; ++j)
            {
                while (idx[b[j]] < mp[b[j]].size() && mp[b[j]][idx[b[j]]] < mp[b[j - 1]][idx[b[j - 1]]])
                    ++idx[b[j]];
                if (idx[b[j]] == mp[b[j]].size())
                {
                    flag = true;
                    break;
                }
            }
            if (flag)
                break;
            for (int j = 0; j < m; ++j)
                ++idx[b[j]];
        }
        cout << idx[b[0]] << endl;
    }
}
