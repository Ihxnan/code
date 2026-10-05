#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    char ch;
    cin >> n >> ch;
    string str;
    cin >> str;
    int ans = 0;
    for (int i = 0; i < n / 2; ++i)
        if (str[i] != str[n - 1 - i])
        {
            if (str[i] != ch && str[n - 1 - i] != ch)
                ans += 2;
            else
                ++ans;
        }
    cout << ans << endl;
}
