#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    vi arr(3);
    for (auto &p : arr)
        cin >> p;
    sort(arr.begin(), arr.end());
    int cnt = 0;
    while (arr[1] != arr[0] && arr[1] != arr[2])
    {
        ++cnt;
        --arr[2], ++arr[0];
        sort(arr.begin(), arr.end());
    }
    cout << cnt << endl;
}
