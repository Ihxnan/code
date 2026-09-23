#include <ihxnan>

void solve()
{
    int n;
    cin >> n;
    int a = 0, b = 0, c = 0;
    vi arr(n);
    for (auto &p : arr)
    {
        cin >> p;
        int tmp = 1000 - p % 1000;
        a += tmp % 10;
        tmp /= 10;
        b += tmp % 10;
        tmp /= 10;
        c += tmp % 10;
    }
    cout << a << ' ' << b << ' ' << c << endl;
}
