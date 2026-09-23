#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    rd0(arr);
    sort(arr.begin(), arr.end());

    auto check = [&](int x) -> bool {
        int last = -1e9;
        for (auto &p : arr)
        {
            if (last < p - x)
                last = p - x;
            else if (last >= p - x)
            {
                ++last;
                if (last > p + x)
                    return false;
            }
        }
        return true;
    };

    int l = -1, r = 1e6, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? r = mid : l = mid;

    cout << r << endl;
}
