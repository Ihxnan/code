#include <ihxnan>

void solve()
{
    int n, x;
    cin >> n >> x;
    vi arr(n);
    rd0(arr);
    sort(arr.begin(), arr.end());
    set<int> hash;
    for (int i = 0; i < n; ++i)
    {
        int a = min(arr[i], arr[i] - x), b = max(arr[i], arr[i] - x);
        if (a < 0 && !hash.count(a))
            hash.insert(a);
        else if (b < 0 && !hash.count(b))
            hash.insert(b);
    }
    cout << accumulate(hash.begin(), hash.end(), 0ll);
    hash.clear();
    reverse(arr.begin(), arr.end());
    for (int i = 0; i < n; ++i)
    {
        int a = max(arr[i], arr[i] - x), b = min(arr[i], arr[i] - x);
        if (a > 0 && !hash.count(a))
            hash.insert(a);
        else if (b > 0 && !hash.count(b))
            hash.insert(b);
    }
    cout << ' ' << accumulate(hash.begin(), hash.end(), 0ll) << endl;
}
