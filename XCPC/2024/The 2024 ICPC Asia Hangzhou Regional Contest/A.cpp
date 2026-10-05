#include <ihxnan>
#include <DSU>

int init = [] { return cin >> t, 0; }();

void solve()
{
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    if (s1.size() != s2.size())
        return cout << "NO" << endl, void();
    if (s1.size() != s3.size())
        return cout << "YES" << endl, void();
    DSU dsu(128);
    for (int i = 0; i < s1.size(); ++i)
        dsu.merge(s1[i], s2[i]);
    for (auto &p : s1)
        p = dsu.get(p);
    for (auto &p : s2)
        p = dsu.get(p);
    for (auto &p : s3)
        p = dsu.get(p);
    if (s1 == s2 && s1 != s3)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
