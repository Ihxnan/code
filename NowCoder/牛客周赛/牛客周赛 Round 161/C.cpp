#include <ihxnan>

void solve()
{
    int n, k;
    cin >> n >> k;
    vi arr(n);
    rd0(arr);
    sort(arr.begin(), arr.end(), [&](int x, int y) {
        int cx = __builtin_popcount(x), cy = __builtin_popcount(y);
        if (cx != cy)
            return cx < cy;
        int lx = x & -x, ly = y & -y;
        if (lx != ly)
            return lx < ly;
        return x < y;
    });
    cout << arr[k - 1] << endl;
}
