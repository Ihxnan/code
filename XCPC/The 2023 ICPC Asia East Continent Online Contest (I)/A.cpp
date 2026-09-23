#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    string str;
    set<string> ha;
    vector<string> a;
    for (int i = 0; i < n; ++i)
    {
        cin >> str;
        if (ha.count(str) == 0)
            ha.insert(str), a.push_back(str);
    }

    set<string> hb;
    vector<string> b;
    for (int i = 0; i < m; ++i)
    {
        cin >> str;
        if (hb.count(str) == 0)
            hb.insert(str), b.push_back(str);
    }

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    set<string> hc;
    vector<string> ans;
    while (a.size() && b.size())
    {
        if (hc.count(a.back()) == 0)
            hc.insert(a.back()), ans.push_back(a.back());
        a.pop_back();
        if (hc.count(b.back()) == 0)
            hc.insert(b.back()), ans.push_back(b.back());
        b.pop_back();
    }

    while (a.size())
    {
        if (hc.count(a.back()) == 0)
            hc.insert(a.back()), ans.push_back(a.back());
        a.pop_back();
    }

    while (b.size())
    {
        if (hc.count(b.back()) == 0)
            hc.insert(b.back()), ans.push_back(b.back());
        b.pop_back();
    }

    for (auto &p : ans)
        cout << p << endl;
}
