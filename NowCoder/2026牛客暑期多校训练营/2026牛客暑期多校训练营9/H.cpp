#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    int odd = 0, even = 0, cnt = 0;
    for (auto &p : arr)
        cin >> p, p & 1 ? ++cnt, odd = max(odd, p) : even = max(even, p);
    cnt %= 2;
    cout << max(odd + cnt >> 1, even >> 1) << endl;
}
