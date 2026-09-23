#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    set<int> hash;
    for (int i = 0, t; i < n; ++i)
    {
        cin >> t, hash.insert(t);
        if (hash.size() > 3)
            return cout << "NO", void();
    }
    cout << "YES";
}
