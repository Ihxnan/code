#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    lll n, x;
    cin >> n >> x;
    vector<lll> arr(n);
    for (auto &p : arr)
        cin >> p;
    if (x == 1)
        return cout << accumulate(arr.begin(), arr.end(), lll(0)) % mod << endl, void();

    lll magic = 1;
    for (auto &p : arr)
        magic += p / x, p %= x;
    sort(arr.rbegin(), arr.rend());

    for (auto &p : arr)
        if (p + magic >= x)
            magic -= x - p - 1, p = 0;

    lll sum = 0;
    for (auto &p : arr)
        sum += p;

    if (sum)
        return cout << (sum + (magic ? magic - 1 : 0)) % mod << endl, void();

    while (magic >= x)
        magic = magic % x + magic / x;

    if (magic)
        --magic;

    cout << magic % mod << endl;
}
