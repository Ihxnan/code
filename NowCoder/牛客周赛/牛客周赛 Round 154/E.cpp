#include <bits/stdc++.h>
/* ──▶  INCLUDE  ◀── */
// #define MULTIT
#include <ihxnan>
/* ──▶  /INCLUDE  ◀── */

/* ╔══════════ SOLVE ══════════╗ */
void solve()
{
    int n, k, x;
    cin >> n >> k >> x;
    if (n == 1)
    {
        cout << int(x == 0) << endl;
        return;
    }
    vi arr(n);
    for (auto &p : arr)
        cin >> p;
    multiset<int> small, big;
    auto insert = [&](int x) -> void {
        if (small.empty() || x <= *--small.end())
            small.insert(x);
        else
            big.insert(x);
        while (small.size() > big.size() + 1)
            big.insert(*--small.end()), small.erase(--small.end());
        while (big.size() > small.size())
            small.insert(*big.begin()), big.erase(big.begin());
    };

    auto erase = [&](int x) -> void {
        if (small.count(x))
            small.erase(small.find(x));
        else
            big.erase(big.find(x));
        while (small.size() > big.size() + 1)
            big.insert(*--small.end()), small.erase(--small.end());
        while (big.size() > small.size())
            small.insert(*big.begin()), big.erase(big.begin());
    };

    auto get = [&] {
        if (small.size() > big.size())
            return *--small.end();
        if (*--small.end() % 2 != *big.begin() % 2)
            return 0;
        return *--small.end() + *big.begin() >> 1;
    };

    for (int i = k; i < n; ++i)
        insert(arr[i]);

    int ans = 0;
    for (int i = k; i < n; ++i)
    {
        ans += x == get();

        gdb(small);
        gdb(big);
        gdb(ans);

        erase(arr[i]);
        insert(arr[i - k]);
    }

    ans += x == get();

    cout << ans << endl;
}
/* ╚══════════ /SOLVE ══════════╝ */
