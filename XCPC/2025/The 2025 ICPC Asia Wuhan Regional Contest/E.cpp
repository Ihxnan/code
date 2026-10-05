#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi a(n), b(n);
    rd0(a);
    rd0(b);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a == b)
        return cout << "Yes" << endl, void();

    bool flag1 = false, flag2 = false;
    for (int i = 1; i < n; ++i)
        if (a[i] == a[i - 1] + 1)
        {
            flag1 = true;
            break;
        }
    for (int i = 1; i < n; ++i)
        if (b[i] == b[i - 1] + 1)
        {
            flag2 = true;
            break;
        }

    if (!flag1 || !flag2)
        return cout << "No" << endl, void();

    int suma = 0, sumb = 0;
    for (auto &p : a)
        suma += p % 2;
    for (auto &p : b)
        sumb += p % 2;

    if (suma == sumb)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}
