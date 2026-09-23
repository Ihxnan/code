#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    map<char, int> hash;
    for (int i = 0; i < n; ++i)
        hash[str[i]] = i;
    if (hash.size() <= 1)
        cout << -1 << endl;
    else
        cout << hash.begin()->second << ' ' << (--hash.end())->second << endl;
}
