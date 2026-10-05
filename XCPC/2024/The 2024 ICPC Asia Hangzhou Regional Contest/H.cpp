#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, k;
    cin >> n >> k;
    vvi chains(k);
    for (int i = 0, l, r; i < k; ++i)
    {
        cin >> l >> r;
        for (; l <= r; ++l)
            chains[i].push_back(l);
    }
    sort(chains.begin(), chains.end(), [&](auto &a, auto &b) { return a.size() > b.size(); });
    if (k == 1)
    {
        for (auto &p : chains[0])
            cout << p - 1 << ' ';
        cout << endl;
        return;
    }

    if (chains.front().size() == 1)
        return cout << "IMPOSSIBLE" << endl, void();

    if (chains[0].size() != chains[1].size())
    {
        vi fa(n + 1);
        for (auto &p : chains[0])
            fa[p] = p - 1;
        int r = chains[0][0];
        fa[r] = 0;
        for (int i = 1; i < k; ++i)
        {
            for (auto &p : chains[i])
                fa[p] = p - 1;
            fa[chains[i][0]] = r;
        }

        for (int i = 1; i <= n; ++i)
            cout << fa[i] << ' ';
        cout << endl;
    }
    else
    {
        int idx = 0;
        int sum = chains[idx].size() - 1;
        for (int i = idx; i < k; ++i)
            if (chains[i].size() + 1 < chains[idx].size())
                sum += chains[i].size();

        if (chains[idx].size() < 3 || sum < chains[0].size())
            return cout << "IMPOSSIBLE" << endl, void();

        vi fa(n + 1);
        int r = chains[idx][0];
        for (int i = 0; i < k; ++i)
            if (i != idx && chains[i].size() >= chains[idx].size() - 1)
            {
                for (auto &p : chains[i])
                    fa[p] = p - 1;
                fa[chains[i][0]] = r;
            }
            else
            {
                for (auto &p : chains[i])
                    fa[p] = p - 1;
                fa[chains[i][0]] = chains[idx][1];
            }
        fa[r] = 0;
        for (int i = 1; i <= n; ++i)
            cout << fa[i] << ' ';
        cout << endl;
    }
}
