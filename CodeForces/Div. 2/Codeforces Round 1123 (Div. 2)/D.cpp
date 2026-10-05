#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    vi odd, even;
    for (int i = 1, t; i <= n; ++i)
    {
        cin >> t;
        i % 2 ? odd.push_back(t) : even.push_back(t);
    }
    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());

    vi lodd, leven;
    int i1 = 1, i2 = 0;
    vi ans{odd[0]};
    while (true)
    {
        while (i2 < even.size() && even[i2] < ans.back())
            leven.push_back(even[i2++]);
        if (i2 == even.size())
            break;
        ans.push_back(even[i2++]);
        while (i1 < odd.size() && odd[i1] < ans.back())
            lodd.push_back(odd[i1++]);
        if (i1 == odd.size())
            break;
        ans.push_back(odd[i1++]);
    }

    while (i1 < odd.size())
        lodd.push_back(odd[i1++]);
    while (i2 < even.size())
        leven.push_back(even[i2++]);

    while (lodd.size() || leven.size())
    {
        if (ans.size() % 2)
            ans.push_back(leven.back()), leven.pop_back();
        else
            ans.push_back(lodd.back()), lodd.pop_back();
    }

    int ma = 0;
    for (int i = 1; i < ans.size(); ++i)
        if (ans[i] > ans[ma])
            ma = i;
    for (int i = 1; i <= ma; ++i)
        if (ans[i - 1] > ans[i])
            return cout << "NO" << endl, void();

    for (int i = ma; i < n - 1; ++i)
        if (ans[i] < ans[i + 1])
            return cout << "NO" << endl, void();

    cout << "YES" << endl;
}
