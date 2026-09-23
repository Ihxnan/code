#include <ihxnan>

void solve()
{
    int n;
    while (cin >> n, n)
    {
        vl arr(n + 1);
        rd1(arr);
        vl dp(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j < i; ++j)
                if (arr[j] < arr[i])
                    dp[i] = max(dp[i], dp[j]);
            dp[i] += arr[i];
        }
        cout << *max_element(dp.begin(), dp.end()) << endl;
    }
}
