#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    for (auto &p : arr)
        cin >> p;
    sort(arr.begin(), arr.end());
    int s1 = 0;
    for (auto &p : arr)
        s1 >= p ? ++s1 : --s1;
    reverse(arr.begin(), arr.end());
    int s2 = 0;
    for (auto &p : arr)
        s2 >= p ? ++s2 : --s2;
    cout << s1 << ' ' << s2 << endl;
}
