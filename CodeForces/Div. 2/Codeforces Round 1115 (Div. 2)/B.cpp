#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    string str;
    cin >> n >> str;
    int c0 = 0, c1 = 0;
    string ans;
    ans += str[0];
    for (int i = 1; i < n; ++i)
        if (str[i] == ans.back())
            str[i] == '0' ? ++c0 : ++c1;
        else
            ans += str[i];
    if (abs(c0 - c1) < 2)
        return cout << c0 + c1 << endl, void();
    if (abs(c0 - c1) > 3)
        return cout << -1 << endl, void();
    if (c0 - c1 == 2)
    {
        if (ans.front() == '1' || ans.back() == '1')
            cout << c0 + c1 + 1 << endl;
        else
            cout << -1 << endl;
    }
    if (c1 - c0 == 2)
    {
        if (ans.front() == '0' || ans.back() == '0')
            cout << c0 + c1 + 1 << endl;
        else
            cout << -1 << endl;
    }
    if (c0 - c1 == 3)
    {
        if (ans.size() > 2 && ans.front() == '1' && ans.back() == '1')
            cout << c0 + c1 + 2 << endl;
        else
            cout << -1 << endl;
    }
    if (c1 - c0 == 3)
    {
        if (ans.size() > 2 && ans.front() == '0' && ans.back() == '0')
            cout << c0 + c1 + 2 << endl;
        else
            cout << -1 << endl;
    }
}
