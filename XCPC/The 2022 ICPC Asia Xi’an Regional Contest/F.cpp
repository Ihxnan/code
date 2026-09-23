#include <ihxnan>

void solve()
{
    int n, c1, c2;
    cin >> n >> c1 >> c2;

    c1 = min(c1, c2);
    c2 = min(c2, 2 * c1);

    ll ans = 0;
    string str;
    for (int i = 0; i < n; ++i)
    {
        cin >> str;
        sort(str.begin(), str.end());
        if (str[0] == str[1] || str[1] == str[2])
            ans += c1 + c2;
        else
            ans += c1 * 3;
    }

    cout << ans << endl;
}
