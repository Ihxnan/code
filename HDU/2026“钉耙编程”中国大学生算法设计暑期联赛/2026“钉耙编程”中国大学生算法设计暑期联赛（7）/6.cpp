#include <ihxnan>
#include <DSU>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    vvi adj(n + 1);
    vb have(n + 1);
    for (int i = 0, c, p; i < m; ++i)
    {
        cin >> c >> p;
        dsu.merge(c, p);
        adj[c].push_back(p);
        adj[p].push_back(c);
        have[c] = have[p] = true;
    }

    vi block;
    for (int i = 1; i <= n; ++i)
        if (have[i] && i == dsu.get(i))
            block.push_back(i);

    if (block.size() > 2)
        return cout << "No" << endl, void();

    vb sta(n + 1);
    vb hash(n + 1);
    vb male(n + 1), female(n + 1);

    auto dfs = [&](auto &&self, int root) -> void {
        if (male[root])
            for (auto &p : adj[root])
                female[p] = true;
        else
            for (auto &p : adj[root])
                male[p] = true;

        for (auto &p : adj[root])
            if (!sta[p])
                sta[p] = true, self(self, p);
    };

    for (int i = 1; i <= n; ++i)
        if (!hash[dsu.get(i)])
        {
            sta[dsu.get(i)] = true;
            dfs(dfs, dsu.get(i));
            hash[dsu.get(i)] = true;
        }

    int i1, i2;
    auto check = [&](vb &male, vb &female) -> bool {
        i1 = 1;
        while (i1 <= n && !male[i1])
            ++i1;

        i2 = n;
        while (i2 && !male[i2])
            --i2;

        if (i1 > i2 || i2 == n || i1 == 1)
            return false;

        for (int i = i1; i <= i2; ++i)
            if (female[i])
                return false;

        return true;
    };

    if (check(male, female))
        cout << "Yes" << endl << i1 << ' ' << i2 + 1 << endl;
    else if (check(female, male))
        cout << "Yes" << endl << i1 << ' ' << i2 + 1 << endl;
    else if (block.size() < 2)
        cout << "No" << endl;
    else
    {
        for (int i = 1; i <= n; ++i)
            if (dsu.get(i) == block[0])
                male[i] = !male[i], female[i] = !male[i];
        if (check(male, female))
            cout << "Yes" << endl << i1 << ' ' << i2 + 1 << endl;
        else if (check(female, male))
            cout << "Yes" << endl << i1 << ' ' << i2 + 1 << endl;
        else
            cout << "No" << endl;
    }
}
