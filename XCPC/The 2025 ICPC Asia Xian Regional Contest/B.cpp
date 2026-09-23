#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    bool flag = true;
    for (int i = 1; i < n; ++i)
        if (str[i] == str[i - 1])
        {
            flag = false;
            break;
        }
    if (flag)
        return cout << "Beautiful" << endl, void();

    int cntC = 0, cntW = 0, cntP = 0;
    for (auto &p : str)
        if (p == 'C')
            ++cntC;
        else if (p == cntW)
            ++cntW;
        else
            ++cntP;

    int tmp[] = {cntC, cntW, cntP};
    sort(begin(tmp), end(tmp));
    if (tmp[0] + tmp[1] + 1 < tmp[2])
        return cout << "Impossible" << endl, void();

    cout << "Possible" << endl;

    auto check = [&](int x) -> bool {
        
    };

    int l = 1, r = n + 1, mid;
    while (l + 1 < r)
        check(mid = l + r >> 1) ? r = mid : l = mid;
}
