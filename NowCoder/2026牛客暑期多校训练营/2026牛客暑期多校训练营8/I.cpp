#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    ll n, m;
    cin >> n >> m;
    vl arr(2 * n);
    for (auto &p : arr)
        cin >> p;
    ll cnt = 0;
    arr[1] += m;
    cnt += arr[1] > arr[0];
    double t;
    for (int i = 2; i < 2 * n; i += 2)
    {
        t = m;
        if (arr[i] > arr[i + 1])
            swap(arr[i], arr[i + 1]);

        if (arr[i + 1] > arr[0])
            ++cnt;
        else if (arr[i + 1] + t > arr[0])
            ++cnt, t -= max(0.0, arr[0] - arr[i + 1] + 0.5);

        if (arr[i] > arr[0])
            ++cnt;
        else if (arr[i] + t > arr[0])
            ++cnt;
    }

    int cnt1 = 0;
    arr[1] -= m;
    arr[0] += m;
    cnt1 += arr[1] > arr[0];
    for (int i = 2; i < 2 * n; i += 2)
    {
        t = m;
        if (arr[i] > arr[i + 1])
            swap(arr[i], arr[i + 1]);
        if (arr[i] > arr[0])
            ++cnt1, t = 0;
        if (arr[i + 1] > arr[0])
            ++cnt1, t = 0;
        if (arr[i] <= arr[0] && arr[i + 1] <= arr[0])
            if (arr[i] + arr[i + 1] + t > arr[0] * 2)
                ++cnt1;
    }

    cout << cnt1 << ' ' << cnt << endl;
}
