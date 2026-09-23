#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    rd0(arr);
    int cnt1 = 0;
    for (auto &p : arr)
        cnt1 += p;
    cout << (cnt1 >= n - cnt1 ? "Bessie" : "Elsie") << endl;
}
