#include <ihxnan>

void solve()
{
    int n, m;
    cin >> n >> m;
    set<string> hash;
    string str;
    for (int i = 0; i < n; ++i)
    {
        cin >> str;
        hash.insert(str);
    }

    set<string> exist;
    for (int i = 0; i < m; ++i)
    {
        cin >> str;
        if (hash.count(str) == 0)
            cout << "WRONG" << endl;
        else if (exist.count(str))
            cout << "REPEAT" << endl;
        else
            cout << "OK" << endl, exist.insert(str);
    }
}
