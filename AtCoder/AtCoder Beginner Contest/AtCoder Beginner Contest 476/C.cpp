#include <ihxnan>

void solve()
{
    int n, t;
    cin >> n >> t;
    multiset<int, greater<>> arr;
    arr.insert(t);
    cin >> t;
    arr.insert(t);
    for (int i = 2; i < n; ++i)
    {
        cin >> t, arr.insert(t);
        cout << *next(next(arr.begin())) << endl;
    }
}
