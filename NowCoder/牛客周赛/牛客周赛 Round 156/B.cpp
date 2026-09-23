#include <ihxnan>

// int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    set<char> hash(str.begin(), str.end());
    int i, ans = 0;
    for (auto &p : hash)
    {
        string tmp;
        for (auto &q : str)
            if (p != q)
                tmp += q;

        for (i = 0; i < tmp.size() / 2; ++i)
            if (tmp[i] != tmp[tmp.size() - 1 - i])
                break;

        ans += i == tmp.size() / 2;
    }
    cout << ans;
}
