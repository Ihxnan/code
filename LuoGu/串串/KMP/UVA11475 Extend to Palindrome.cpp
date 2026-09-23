#include <ihxnan>
#include <KMP>

void solve()
{
    string str;
    while (cin >> str)
    {
        auto tmp = str;
        reverse(tmp.begin(), tmp.end());
        string s = '^' + tmp + '^' + str;
        auto fail = get_fail(s);
        int len = fail.back();
        cout << str << tmp.substr(len, str.size() - len) << endl;
    }
}
