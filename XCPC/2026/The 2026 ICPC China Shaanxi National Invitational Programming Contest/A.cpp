#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vl arr(n);
    ll sum = 0;
    for (auto &p : arr)
        cin >> p, sum += p;
    if (sum % n)
        return cout << -1 << endl, void();
    sum /= n;
    vl vec(n);
    for (int i = 0; i + 1 < n; ++i)
    {
        if (arr[i] > sum)
            return cout << -1 << endl, void();
        vec[i] = sum - arr[i];
        arr[i] = sum;
        arr[i + 1] -= vec[i];
    }

    vl odd{0}, even{0};
    for (int i = 0; i < n - 1; ++i)
        i & 1 ? odd.push_back(vec[i]) : even.push_back(vec[i]);

    auto work = [&](vl &arr) -> ll {
        ll res = 0;
        for (int i = 1; i < arr.size(); ++i)
            if (arr[i] > arr[i - 1])
                res += arr[i] - arr[i - 1];
        return res;
    };

    cout << work(odd) + work(even) << endl;
}
