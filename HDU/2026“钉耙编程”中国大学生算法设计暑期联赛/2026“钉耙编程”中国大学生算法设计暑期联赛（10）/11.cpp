#include <ihxnan>

vi arr;

int init = [] {
    for (int i = 0; i <= 30 * 30 * 30; ++i)
        if (__builtin_popcount(i) * __builtin_popcount(i) * __builtin_popcount(i) == i >> 1)
            arr.push_back(i);
    return cin >> t, 0;
}();

void solve()
{
    int x;
    cin >> x;
    auto it = lower_bound(arr.begin(), arr.end(), x);
    if (it == arr.end())
        cout << -1 << endl;
    else
        cout << *it << endl;
}
