#include <ihxnan>

void solve()
{
    int n;
    string s, t;
    cin >> n >> s >> t;
    for (int i = 0; i < n; ++i)
        if (t[i] != '*' && t[i] != s[i])
            return cout << "No" << endl, void();
    cout << "Yes" << endl;
}
