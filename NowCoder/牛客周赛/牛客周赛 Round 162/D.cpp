#include <ihxnan>

void solve()
{
    int n;
    char c0;
    cin >> n >> c0;
    lll cnt = 0;
    char ch;
    for (int i = 0; i < n; ++i)
    {
        cin >> ch;
        if (ch == c0)
            cnt = 2 * cnt + 2;
        else
            cnt *= 2;
    }
    cout << cnt << endl;
}
