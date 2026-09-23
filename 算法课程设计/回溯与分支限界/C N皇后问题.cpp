#include <ihxnan>

int work(int n)
{
    int res = 0;

    vi arr(n);
    iota(arr.begin(), arr.end(), 0);
    do
    {
        int i = 0;
        vi cnt1(2 * n - 1);
        for (; i < n; ++i)
            if (++cnt1[i + arr[i]] > 1)
                break;
        if (i != n)
            continue;
        vi cnt2(2 * n - 1);
        for (i = 0; i < n; ++i)
            if (++cnt2[arr[i] - i + n - 1] > 1)
                break;
        if (i != n)
            continue;

        ++res;

    } while (next_permutation(arr.begin(), arr.end()));

    return res;
}

void solve()
{
    vi ans{0};
    for (int i = 1; i <= 10; ++i)
        ans.push_back(work(i));

    int n;
    while (cin >> n, n)
        cout << ans[n] << endl;
}
