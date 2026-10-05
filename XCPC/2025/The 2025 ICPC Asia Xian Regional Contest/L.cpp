#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vl arr(n + 1), sum(n + 1);
    rd1(arr);
    sort(arr.begin(), arr.end());
    for (int i = 1; i <= n; ++i)
        sum[i] = arr[i] + sum[i - 1];
    vl ans(n + 1);
    for (int i = 3; i <= n; ++i)
        for (int j = n; j - i >= 0; --j)
            if (arr[j] < sum[j - 1] - sum[j - i])
            {
                ans[i] = sum[j] - sum[j - i];
                break;
            }
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
    cout << endl;
}
