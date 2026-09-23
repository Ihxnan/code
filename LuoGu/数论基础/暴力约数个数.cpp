#include <ihxnan>

int init = [] { return cin >> t, 0; }();

int work(int n)
{
    int res = 0;
    for (int i = 1; i <= sqrt(n); ++i)
        if (n % i == 0)
        {
            if (i * i == n)
                ++res;
            else
                res += 2;
        }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    cout << work(n) << endl;
}
