#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vi arr(n + 1);
    rd1(arr);
    for (int l, r, c; cin >> l >> r >> c;)
    {
        int res = 0;
        for (int i = l; i <= r; ++i)
            res += arr[i] == c, arr[i] = c;
        cout << res << endl;
    }
}
