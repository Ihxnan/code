#include <ihxnan>

void solve()
{
    int n;
    string str;
    cin >> n >> str;
    map<char, int> hash;
    for (int i = 1; i <= n; ++i)
        if (++hash[str[i - 1]] == 3)
            return cout << i, void();
    cout << -1 << endl;
}
