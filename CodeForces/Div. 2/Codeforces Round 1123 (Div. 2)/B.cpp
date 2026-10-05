#include <ihxnan>

int init = [] { return cin >> t, 0; }();

void solve()
{
    int n;
    cin >> n;
    map<int, int, greater<>> arr;
    for (int i = 0, t; i < n; ++i)
        cin >> t, ++arr[t];

    while (arr.size())
    {
        vi tmp;
        for (auto &[k, v] : arr)
        {
            cout << k << ' ';
            if (--v == 0)
                tmp.push_back(k);
        }
        for (auto &p : tmp)
            arr.erase(p);
    }
    cout << endl;
}
