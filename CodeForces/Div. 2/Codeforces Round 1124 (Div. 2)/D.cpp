#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n, q;
    cin >> n >> q;
    vi arr(n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], cnt += arr[i] % 3 == 0 || arr[i] % 5 == 0;
    cout << cnt << ' ';
    for (int i = 0, p, x; i < q; ++i)
    {
        cin >> p >> x;
        cnt += x % 3 == 0 || x % 5 == 0;
        cnt -= arr[p] % 3 == 0 || arr[p] % 5 == 0;
        arr[p] = x;
        cout << cnt << ' ';
    }
    cout << endl;
}
