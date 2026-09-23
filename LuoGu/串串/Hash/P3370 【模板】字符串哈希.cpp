#include <ihxnan>

ul hash(string &str)
{
    ul res = 0;
    for (auto &p : str)
        res = res * 1331 + p;
    return res;
}

void solve()
{
    int n;
    cin >> n;
    string str;
    set<int> hash;
    for (int i = 0; i < n; ++i)
        cin >> str, hash.insert(::hash(str));
    cout << hash.size() << endl;
}
